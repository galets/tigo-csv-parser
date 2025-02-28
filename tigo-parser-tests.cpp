void test_generic() {
    std::string header = "DATETIME,TimeStamp,GMT,LMU_A1_Vin,LMU_A1_Iin,LMU_A1_Temp,LMU_A1_Pwm,LMU_A1_Status,LMU_A1_Flags,LMU_A1_RSSI,LMU_A1_BRSSI,LMU_A1_ID,LMU_A1_Vout,LMU_A1_Details,LMU_A10_Vin,LMU_A10_Iin,LMU_A10_Temp,LMU_A10_Pwm,LMU_A10_Status,LMU_A10_Flags,LMU_A10_RSSI,LMU_A10_BRSSI,LMU_A10_ID,LMU_A10_Vout,LMU_A10_Details,LMU_A2_Vin,LMU_A2_Iin,LMU_A2_Temp,LMU_A2_Pwm,LMU_A2_Status,LMU_A2_Flags,LMU_A2_RSSI,LMU_A2_BRSSI,LMU_A2_ID,LMU_A2_Vout,LMU_A2_Details,LMU_A3_Vin,LMU_A3_Iin,LMU_A3_Temp,LMU_A3_Pwm,LMU_A3_Status,LMU_A3_Flags,LMU_A3_RSSI,LMU_A3_BRSSI,LMU_A3_ID,LMU_A3_Vout,LMU_A3_Details,LMU_A4_Vin,LMU_A4_Iin,LMU_A4_Temp,LMU_A4_Pwm,LMU_A4_Status,LMU_A4_Flags,LMU_A4_RSSI,LMU_A4_BRSSI,LMU_A4_ID,LMU_A4_Vout,LMU_A4_Details,LMU_A5_Vin,LMU_A5_Iin,LMU_A5_Temp,LMU_A5_Pwm,LMU_A5_Status,LMU_A5_Flags,LMU_A5_RSSI,LMU_A5_BRSSI,LMU_A5_ID,LMU_A5_Vout,LMU_A5_Details,LMU_A6_Vin,LMU_A6_Iin,LMU_A6_Temp,LMU_A6_Pwm,LMU_A6_Status,LMU_A6_Flags,LMU_A6_RSSI,LMU_A6_BRSSI,LMU_A6_ID,LMU_A6_Vout,LMU_A6_Details,LMU_A7_Vin,LMU_A7_Iin,LMU_A7_Temp,LMU_A7_Pwm,LMU_A7_Status,LMU_A7_Flags,LMU_A7_RSSI,LMU_A7_BRSSI,LMU_A7_ID,LMU_A7_Vout,LMU_A7_Details,LMU_A8_Vin,LMU_A8_Iin,LMU_A8_Temp,LMU_A8_Pwm,LMU_A8_Status,LMU_A8_Flags,LMU_A8_RSSI,LMU_A8_BRSSI,LMU_A8_ID,LMU_A8_Vout,LMU_A8_Details,LMU_A9_Vin,LMU_A9_Iin,LMU_A9_Temp,LMU_A9_Pwm,LMU_A9_Status,LMU_A9_Flags,LMU_A9_RSSI,LMU_A9_BRSSI,LMU_A9_ID,LMU_A9_Vout,LMU_A9_Details,LMU_B1_Vin,LMU_B1_Iin,LMU_B1_Temp,LMU_B1_Pwm,LMU_B1_Status,LMU_B1_Flags,LMU_B1_RSSI,LMU_B1_BRSSI,LMU_B1_ID,LMU_B1_Vout,LMU_B1_Details,LMU_B10_Vin,LMU_B10_Iin,LMU_B10_Temp,LMU_B10_Pwm,LMU_B10_Status,LMU_B10_Flags,LMU_B10_RSSI,LMU_B10_BRSSI,LMU_B10_ID,LMU_B10_Vout,LMU_B10_Details,LMU_B2_Vin,LMU_B2_Iin,LMU_B2_Temp,LMU_B2_Pwm,LMU_B2_Status,LMU_B2_Flags,LMU_B2_RSSI,LMU_B2_BRSSI,LMU_B2_ID,LMU_B2_Vout,LMU_B2_Details,LMU_B3_Vin,LMU_B3_Iin,LMU_B3_Temp,LMU_B3_Pwm,LMU_B3_Status,LMU_B3_Flags,LMU_B3_RSSI,LMU_B3_BRSSI,LMU_B3_ID,LMU_B3_Vout,LMU_B3_Details,LMU_B4_Vin,LMU_B4_Iin,LMU_B4_Temp,LMU_B4_Pwm,LMU_B4_Status,LMU_B4_Flags,LMU_B4_RSSI,LMU_B4_BRSSI,LMU_B4_ID,LMU_B4_Vout,LMU_B4_Details,LMU_B5_Vin,LMU_B5_Iin,LMU_B5_Temp,LMU_B5_Pwm,LMU_B5_Status,LMU_B5_Flags,LMU_B5_RSSI,LMU_B5_BRSSI,LMU_B5_ID,LMU_B5_Vout,LMU_B5_Details,LMU_B6_Vin,LMU_B6_Iin,LMU_B6_Temp,LMU_B6_Pwm,LMU_B6_Status,LMU_B6_Flags,LMU_B6_RSSI,LMU_B6_BRSSI,LMU_B6_ID,LMU_B6_Vout,LMU_B6_Details,LMU_B7_Vin,LMU_B7_Iin,LMU_B7_Temp,LMU_B7_Pwm,LMU_B7_Status,LMU_B7_Flags,LMU_B7_RSSI,LMU_B7_BRSSI,LMU_B7_ID,LMU_B7_Vout,LMU_B7_Details,LMU_B8_Vin,LMU_B8_Iin,LMU_B8_Temp,LMU_B8_Pwm,LMU_B8_Status,LMU_B8_Flags,LMU_B8_RSSI,LMU_B8_BRSSI,LMU_B8_ID,LMU_B8_Vout,LMU_B8_Details,LMU_B9_Vin,LMU_B9_Iin,LMU_B9_Temp,LMU_B9_Pwm,LMU_B9_Status,LMU_B9_Flags,LMU_B9_RSSI,LMU_B9_BRSSI,LMU_B9_ID,LMU_B9_Vout,LMU_B9_Details,LMU_C1_Vin,LMU_C1_Iin,LMU_C1_Temp,LMU_C1_Pwm,LMU_C1_Status,LMU_C1_Flags,LMU_C1_RSSI,LMU_C1_BRSSI,LMU_C1_ID,LMU_C1_Vout,LMU_C1_Details,LMU_C10_Vin,LMU_C10_Iin,LMU_C10_Temp,LMU_C10_Pwm,LMU_C10_Status,LMU_C10_Flags,LMU_C10_RSSI,LMU_C10_BRSSI,LMU_C10_ID,LMU_C10_Vout,LMU_C10_Details,LMU_C2_Vin,LMU_C2_Iin,LMU_C2_Temp,LMU_C2_Pwm,LMU_C2_Status,LMU_C2_Flags,LMU_C2_RSSI,LMU_C2_BRSSI,LMU_C2_ID,LMU_C2_Vout,LMU_C2_Details,LMU_C3_Vin,LMU_C3_Iin,LMU_C3_Temp,LMU_C3_Pwm,LMU_C3_Status,LMU_C3_Flags,LMU_C3_RSSI,LMU_C3_BRSSI,LMU_C3_ID,LMU_C3_Vout,LMU_C3_Details,LMU_C4_Vin,LMU_C4_Iin,LMU_C4_Temp,LMU_C4_Pwm,LMU_C4_Status,LMU_C4_Flags,LMU_C4_RSSI,LMU_C4_BRSSI,LMU_C4_ID,LMU_C4_Vout,LMU_C4_Details,LMU_C5_Vin,LMU_C5_Iin,LMU_C5_Temp,LMU_C5_Pwm,LMU_C5_Status,LMU_C5_Flags,LMU_C5_RSSI,LMU_C5_BRSSI,LMU_C5_ID,LMU_C5_Vout,LMU_C5_Details,LMU_C6_Vin,LMU_C6_Iin,LMU_C6_Temp,LMU_C6_Pwm,LMU_C6_Status,LMU_C6_Flags,LMU_C6_RSSI,LMU_C6_BRSSI,LMU_C6_ID,LMU_C6_Vout,LMU_C6_Details,LMU_C7_Vin,LMU_C7_Iin,LMU_C7_Temp,LMU_C7_Pwm,LMU_C7_Status,LMU_C7_Flags,LMU_C7_RSSI,LMU_C7_BRSSI,LMU_C7_ID,LMU_C7_Vout,LMU_C7_Details,LMU_C8_Vin,LMU_C8_Iin,LMU_C8_Temp,LMU_C8_Pwm,LMU_C8_Status,LMU_C8_Flags,LMU_C8_RSSI,LMU_C8_BRSSI,LMU_C8_ID,LMU_C8_Vout,LMU_C8_Details,LMU_C9_Vin,LMU_C9_Iin,LMU_C9_Temp,LMU_C9_Pwm,LMU_C9_Status,LMU_C9_Flags,LMU_C9_RSSI,LMU_C9_BRSSI,LMU_C9_ID,LMU_C9_Vout,LMU_C9_Details";
    CsvParser parser(header);

    std::string data_line = "2025/01/29 15:34:32.968,1738182872.968457,-18000,29.15,0.1875,6.1,150,68,80,84,111,21,16.9,131,35.15,0.14,5.5,112,68,80,108,132,41,15.1,132,,,,,,,,,,,,,,,,,,,,,,,34.55,0.1825,2.7,147,68,80,90,117,43,19.6,131,32.95,0.17,7.1,131,68,80,84,111,39,16.6,132,32.25,0.1625,4.9,133,68,80,123,147,34,16.4,131,35.6,0.18,4.7,141,68,80,84,105,33,19.3,131,33.3,0.27,5.6,218,100,80,84,108,29,27.9,,,,,,,,,,,,,,,,,,,,,,,,33.15,0.2125,5,173,68,80,111,135,20,22.1,132,32.3,0.3125,,255,68,80,54,78,23,32.1,129,32.05,0.325,5.5,255,100,80,72,96,24,31.7,,33.15,0.1775,2.8,150,68,80,135,156,44,19.1,131,31.75,0.17,1.8,139,68,80,99,126,45,16.9,131,33.95,0.2,6,163,68,80,132,156,22,21.6,132,32.5,0.3325,1.6,255,98,80,144,168,31,32.3,,34.45,0.205,3.9,170,68,80,123,144,40,22.4,132,32.7,0.1975,5.2,162,68,80,114,141,25,20.3,131,33.25,0.275,3.5,232,68,80,159,183,19,29.9,132,33.15,0.1975,5.4,174,100,80,114,135,16,22.3,,33.7,0.2975,3.7,255,68,80,153,177,36,33.5,129,32.65,0.2525,2.9,221,68,80,108,132,35,27.7,132,35.4,0.2,3.8,168,68,80,120,144,37,23,132,36.2,0.1125,3.3,97,68,80,108,135,17,13.5,132,33.55,0.2975,0.9,255,68,80,228,255,32,33.3,129,33.4,0.3,4.3,255,100,80,168,189,28,33.2,,33.25,0.295,4.7,255,100,80,141,168,42,33,,32.95,0.295,2.8,255,68,80,126,147,30,32.6,131";
    LmuData data = parser.parse(data_line);

    for (const auto& pair : data.lmuMap) {
        const LmuFields& fields = pair.second;
        std::cout << "LMU ID: " << pair.first << ", power: " << fields.getPower() << std::endl;
    }
}

void test_input(const std::string& path) {
    std::ifstream file;
    file.open(path);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + path);
        return;
    }

    std::string line;
    if (!getline(file, line)) {
        throw std::runtime_error("Error reading header");
    }
    CsvParser parser(line);

    while (getline(file, line)) {
        auto data = parser.parse(line);
        for (const auto& pair : data.lmuMap) {
            const LmuFields& fields = pair.second;
            std::cout << pair.first << ":" << fields.getPower() << " ";
        }
        std::cout << std::endl;
    }

    file.close();
}

void test_scan(const std::string& path) {
    auto lmus = scanLmus(path);
    for (const auto& p : lmus) {
        std::cout << p.first << ":" << p.second.getPower();
        std::cout << std::endl;
    }
}

void test_mqtt() {
    std::map<std::string, LmuFields> lmus{
        {"A1", LmuFields{.Vin = 33, .Iin = 1.22}},
        {"A2", LmuFields{.Vin = 32, .Iin = 1.22}},
        {"B1", LmuFields{.Vin = 38, .Iin = 1.22}},
    };
    publish(lmus);
}

void test_scan_publish(const std::string& path) {
    auto lmus = scanLmus(path);
    publish(lmus);
}

int main() {
    //test_generic();
    //test_input("test-inputs/daqs.2025-01-30_11-04-27-831.csv");
    //test_scan("test-inputs/daqs.2025-01-30_11-04-27-831.csv");
    //test_mqtt();
    //test_scan_publish("test-inputs/daqs.2025-01-30_11-04-27-831.csv");
    return 0;
}
