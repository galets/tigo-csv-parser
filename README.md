# TIGO CCA data publisher

## Build for tigo

```bash
make arm

tigohost=tigo
cat build/armv5/tigo-parser | ssh $tigohost '
    mount -o remount,rw /
    dd of=/usr/bin/tigo-parser
    chmod +x /usr/bin/tigo-parser
    mount -o remount,ro /
'
```

## Make persistent

```bash
tigohost=tigo
ssh $tigohost
mount -o remount,rw /mnt/ffs
echo '*/5 * * * * /usr/bin/tigo-parser --mqtt_server XXX --mqtt_port 1883 --mqtt_user XXX --mqtt_password XXX --mqtt_topic XXX' |
    tee /mnt/ffs/etc/crontab
mount -o remount,ro /mnt/ffs
```