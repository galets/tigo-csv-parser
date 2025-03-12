#include <sys/file.h>
#include <async_mqtt5.hpp>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct CmdLineParams {
    std::string mqtt_server;
    int mqtt_port = 1883;
    std::string mqtt_client_name = "tigo-data-uploader";
    std::string mqtt_user;
    std::string mqtt_password;
    std::string mqtt_topic = "tigo/cca";
};

CmdLineParams params;

struct LmuFields {
    double Vin;
    double Iin;
    double Temp;
    double Pwm;
    std::string Status;
    std::string Flags;
    int RSSI;
    int BRSSI;
    std::string ID;
    double Vout;
    std::string Details;

    double getPower() const {
        if (std::isnan(Vin) || std::isnan(Vout) || std::isnan(Iin)) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        // This formula doesn't look right, but it seems to work
        return (Vin+Vout) * Iin;
    }
};

struct LmuData {
    std::string datetime;
    std::string timestamp;
    std::string gmt;
    std::map<std::string, LmuFields> lmuMap;
};

struct FieldMap {
    typedef std::function<void(LmuData&, const std::string&)> SetterFunc;
    std::vector<SetterFunc> setters;
};

double parseDouble(const std::string& text) {
    try {
        return std::stod(text);
    }
    catch (...) {
        return std::numeric_limits<double>::quiet_NaN();
    }
}

int parseInt(const std::string& text) {
    try {
        return std::stoi(text);
    }
    catch (...) {
        return 0;
    }
}

FieldMap parseHeader(const std::string& header) {
    // Splitting the header string by commas
    std::vector<std::string> fields;
    std::stringstream ss(header);
    std::string field;
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }

    const std::regex pattern("^LMU_(\\w+)_(\\w+)$");
    std::smatch match;

    FieldMap fm;
    fm.setters.resize(fields.size());
    for (size_t i = 0; i < fields.size(); ++i) {
        if (fields[i] == "DATETIME") {
            fm.setters[i] = [i](LmuData& lmu, const std::string& text) {
                lmu.datetime = text;
            };
        }
        else if (fields[i] == "TimeStamp") {
            fm.setters[i] = [i](LmuData& lmu, const std::string& text) {
                lmu.timestamp = text;
            };
        }
        else if (fields[i] == "GMT") {
            fm.setters[i] = [i](LmuData& lmu, const std::string& text) {
                lmu.gmt = text;
            };
        }
        else if (std::regex_match(fields[i], match, pattern)) {
            const std::string lmuId = match[1].str();
            const std::string fieldName = match[2].str();
            fm.setters[i] = [i, lmuId, fieldName](LmuData& lmu, const std::string& fieldValue) {
                // if (!lmu.lmuMap.contains(lmuId)) {
                //     lmu.lmuMap[lmuId] = FieldMap();
                // }
                auto& fields = lmu.lmuMap[lmuId];

                if (fieldName == "Vin") {
                    fields.Vin = parseDouble(fieldValue);
                }
                else if (fieldName == "Iin") {
                    fields.Iin = parseDouble(fieldValue);
                }
                else if (fieldName == "Temp") {
                    fields.Temp = parseDouble(fieldValue);
                }
                else if (fieldName == "Pwm") {
                    fields.Pwm = parseDouble(fieldValue);
                }
                else if (fieldName == "Status") {
                    fields.Status = fieldValue;
                }
                else if (fieldName == "Flags") {
                    fields.Flags = fieldValue;
                }
                else if (fieldName == "RSSI") {
                    fields.RSSI = parseInt(fieldValue);
                }
                else if (fieldName == "BRSSI") {
                    fields.BRSSI = parseInt(fieldValue);
                }
                else if (fieldName == "ID") {
                    fields.ID = fieldValue;
                }
                else if (fieldName == "Vout") {
                    fields.Vout = parseDouble(fieldValue);
                }
                else if (fieldName == "Details") {
                    fields.Details = fieldValue;
                }
                else {
                    // Handle unknown field names
                    //throw std::runtime_error("Unknown field name: " + fieldName);
                }
            };
        }
        else {
        }
    }

    return fm;
}


LmuData parseData(const std::string& data_line, const FieldMap& field_map) {
    LmuData lmu_data;

    // Splitting the data line by commas
    std::vector<std::string> fields;
    std::stringstream ss(data_line);
    std::string text;

    size_t index = 0;
    while (index < field_map.setters.size() && std::getline(ss, text, ',')) {
        if (field_map.setters[index]) {
            field_map.setters[index](lmu_data, text);
        }
        ++index;
    }

    return lmu_data;
}


class CsvParser {
private:
    FieldMap field_map;

public:
    CsvParser(const std::string& header) :
        field_map(parseHeader(header)) {
    }

    LmuData parse(const std::string& data_line) {
        return ::parseData(data_line, field_map);
    }
};

std::map<std::string, LmuFields> scanLmus(const std::string& path) {
    const std::streampos DESIRED_OFFSET = 1024 * 24;

    std::ifstream file;
    file.open(path);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + path);
    }

    std::string line;
    if (!getline(file, line)) {
        throw std::runtime_error("Error reading header");
    }
    CsvParser parser(line);

    auto pos = file.tellg();
    file.seekg(0, file.end);
    auto length = file.tellg();

    if (pos + DESIRED_OFFSET > length) {
        file.seekg(pos, file.beg);
    }
    else {
        file.seekg(length - DESIRED_OFFSET, file.beg);
        getline(file, line);
    }

    if (!file.good()) {
        throw std::runtime_error("File I/O error");
    }

    std::map<std::string, LmuFields> result;
    while (getline(file, line)) {
        auto data = parser.parse(line);
        for (const auto& pair : data.lmuMap) {
            auto p = pair.second.getPower();
            if (!std::isnan(p)) {
                result[pair.first] = pair.second;
            }
        }
    }

    file.close();
    return result;
}

void publish(const std::map<std::string, LmuFields>& lmus) {
    boost::asio::io_context ioc;
    async_mqtt5::mqtt_client<boost::asio::ip::tcp::socket, std::monostate, async_mqtt5::logger> client(ioc);
    client.brokers(params.mqtt_server, params.mqtt_port)
        .credentials(params.mqtt_client_name, params.mqtt_user, params.mqtt_password)
        .async_run(boost::asio::detached);

    for (const auto& p : lmus) {
        async_mqtt5::publish_props pprops;
        pprops[async_mqtt5::prop::message_expiry_interval] = 600u;

        std::ostringstream out;
        out.precision(1);
        out << std::fixed << p.second.getPower();

        client.async_publish<async_mqtt5::qos_e::at_most_once>(params.mqtt_topic + "/" + p.first, out.str(), async_mqtt5::retain_e::no, pprops,
            [&client](async_mqtt5::error_code ec) {
                if (ec.failed()) {
                    std::cout << "MQTT publish failed: " << ec.message() << std::endl;
                }
                client.async_disconnect(boost::asio::detached);
            }
        );
    }

    ioc.run();
}

pid_t find_process_by_executable(const std::string& executable_path) {
    const std::string proc_dir = "/proc";

    for (const auto& entry : fs::directory_iterator(proc_dir)) {
        try {
            if (entry.is_directory() && std::regex_match(entry.path().filename().string(), std::regex("\\d+"))) {
                std::string exe_link = entry.path().string() + "/exe";
                std::filesystem::path exe_path = fs::read_symlink(exe_link);
                if (exe_path == executable_path) {
                    return std::stoi(entry.path().filename().string());
                }
            }
        }
        catch (const std::exception& e) {
            continue;
        }
    }

    throw std::runtime_error("Process not found: " + executable_path);
}

std::string find_open_file_by_pattern(pid_t pid, const std::regex& file_pattern) {
    std::string fd_path = "/proc/" + std::to_string(pid) + "/fd";

    for (const auto& entry : fs::directory_iterator(fd_path)) {
        try {
            std::filesystem::path file_path = fs::read_symlink(entry.path());
            if (std::regex_match(file_path.string(), file_pattern)) {
                return file_path.string();
            }
        }
        catch (const std::exception& e) {
            // Ignore errors for inaccessible file descriptors
            continue;
        }
    }

    throw std::runtime_error("Could not find file by given pattern");
}

void clean_previous_instances() {
    const auto my_pid = std::to_string(getpid());
    const auto my_exe = std::filesystem::canonical("/proc/self/exe");
    const std::string proc_dir = "/proc";

    for (const auto& entry : fs::directory_iterator(proc_dir)) {
        try {
            if (entry.is_directory() && std::regex_match(entry.path().filename().string(), std::regex("\\d+"))) {
                if (entry.path().filename().string() == my_pid) {
                    continue;
                }
                std::string exe_link = entry.path().string() + "/exe";
                std::filesystem::path exe_path = fs::read_symlink(exe_link);
                if (exe_path == my_exe) {
                    pid_t pid = std::atoi(entry.path().filename().string().c_str());
                    std::cout << "Killing process with PID: " << pid << std::endl;
                    if (kill(pid, SIGTERM) != 0) {
                        kill(pid, SIGKILL);
                    }
                }
            }
        }
        catch (const std::exception& e) {
            continue;
        }
    }
}

CmdLineParams parse_cmdline(int argc, char* argv[]) {
    CmdLineParams params;
    std::vector<std::string> args(argv, argv + argc);

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--mqtt_server" || args[i] == "-s") {
            if (i + 1 < args.size()) {
                params.mqtt_server = args[++i];
            } else {
                throw std::runtime_error("Error: --mqtt_server/ -s requires a value.");
            }
        } else if (args[i] == "--mqtt_port" || args[i] == "-p") {
            if (i + 1 < args.size()) {
                try {
                    params.mqtt_port = std::stoi(args[++i]);
                } catch (const std::exception& e) {
                    throw std::runtime_error("Error: --mqtt_port/ -p must be an integer.");
                }
            } else {
                throw std::runtime_error("Error: --mqtt_port/ -p requires a value.");
            }
        } else if (args[i] == "--mqtt_client_name" || args[i] == "-c") {
            if (i + 1 < args.size()) {
                params.mqtt_client_name = args[++i];
            } else {
                throw std::runtime_error("Error: --mqtt_client_name/ -c requires a value.");
            }
         }else if (args[i] == "--mqtt_user" || args[i] == "-u") {
            if (i + 1 < args.size()) {
                params.mqtt_user = args[++i];
            } else {
                throw std::runtime_error("Error: --mqtt_user/ -u requires a value.");
            }
        } else if (args[i] == "--mqtt_password" || args[i] == "-w") {
            if (i + 1 < args.size()) {
                params.mqtt_password = args[++i];
            } else {
                throw std::runtime_error("Error: --mqtt_password/ -w requires a value.");
            }
        } else if (args[i] == "--mqtt_topic" || args[i] == "-t") {
            if (i + 1 < args.size()) {
                params.mqtt_topic = args[++i];
            } else {
                throw std::runtime_error("Error: --mqtt_topic/ -t requires a value.");
            }
        } else if (args[i] == "--help" || args[i] == "-h") {
              std::cout << "Usage: " << args[0] << " [options]" << std::endl;
              std::cout << "Options:" << std::endl;
              std::cout << "  -s, --mqtt_server <server>     MQTT server address (required)" << std::endl;
              std::cout << "  -p, --mqtt_port <port>         MQTT server port (default: 1883)" << std::endl;
              std::cout << "  -c, --mqtt_client_name <name>  MQTT client name (default: tigo-data-uploader)" << std::endl;
              std::cout << "  -u, --mqtt_user <user>         MQTT username (required)" << std::endl;
              std::cout << "  -w, --mqtt_password <password> MQTT password (required)" << std::endl;
              std::cout << "  -t, --mqtt_topic <topic>       MQTT topic (default: tigo/cca)" << std::endl;
              std::cout << "  -h, --help                     Show this help message" << std::endl;
              exit(0);
        } else {
            throw std::runtime_error("Error: Unknown command-line argument: " + args[i]);
        }
    }

    if (params.mqtt_server.empty()) {
         throw std::runtime_error("Error: --mqtt_server is required.");
    }
    
    return params;
}

#ifdef BUILD_TESTS
#include "tigo-parser-tests.cpp"
#else

int main(int argc, char* argv[]) {
    const std::string target_executable = "/mnt/ffs/mgmtu/bin/shdatalogd";
    std::regex file_pattern("/mnt/ffs/data/daqs/daqs\\.[^.]+\\.csv");

    try {
        clean_previous_instances();

        params = parse_cmdline(argc, argv);

        pid_t pid = find_process_by_executable(target_executable);
        std::string path = find_open_file_by_pattern(pid, file_pattern);
        auto lmus = scanLmus(path);
        publish(lmus);

        std::cerr << "Statistics found and published successfully" << std::endl;
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }


}
#endif
