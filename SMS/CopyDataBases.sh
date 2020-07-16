#!/bin/bash
cd ~/InfoPhone
adb shell su -c cp $(find /data/ -name contacts2.db) /storage/sdcard1/Download/SMS/
adb shell su -c cp $(find /data/ -name mmssms.db) /storage/sdcard1/Download/SMS/
adb pull /storage/sdcard1/Download/SMS .
