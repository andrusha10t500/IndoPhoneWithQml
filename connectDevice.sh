#!/bin/sh

if [ -n "$1" ]
then
  cmd=$1
fi

DEVICE_ALL=$(adb devices | awk '/device/ && $1!~/List/ {print($1)}')

function connectDevice() {
AllIPString=$(echo 192.168.0.{1..254} | xargs -n1 -P0 ping -c1 | grep "bytes from" | awk '{printf($4)}')
IFS=':' read -ra IPArray <<< "$AllIPString"

for i in ${IPArray[@]}
 do adb connect $i | awk '$1!~/failed/{print($1)}'
done

DEVICE_ALL=$(adb devices | awk '/device/ && $1!~/List/ {print($1)}')
DEVICE_FROM_WIFI=$(echo $DEVICE_FROM_USB | awk '$1~/^192.168.[0-1]*/ {print($1)}')
#потом нужно будет сделать функцию, которая автоматом выбирает шлюз, что делать в случае если комп является шлюзом?
#route -n | awk '$2~/^[1-9]/{print($2)}'

#returned=$DEVICE_FROM_WIFI

#if [ "$DEVICE_FROM_WIFI" = "" ]
# then returned=$DEVICE_ALL
#fi

echo $returned
}

if [ "$DEVICE_ALL" = "" ] 
 then 
  conDev=$(connectDevice)
  conDev=$(echo ${conDev%:*} | awk '{print($2)}')  

  if [ "$conDev" != "" ]   
   #then adb -s ${conDev%:*} shell su -c 'cat /sys/class/power_supply/battery/capacity'
   then adb -s ${conDev%:*} shell $cmd
   else echo 'your devices is not connected!'
  fi
else
  #На случай если 2 устройства
  DEVICE_ALL=$(adb devices | awk '/device/ && $1!~/List/ {print($1)}' | awk 'NR~/1/{printf($1)}')

  adb -s ${DEVICE_ALL%:*} shell $cmd
fi
if [ -f Connection_device ] && [ "$DEVICE_ALL" != "$(cat Connection_device)" ]
then
    echo $DEVICE_ALL > Connection_device
else
    touch Connection_device
    echo $DEVICE_ALL > Connection_device
fi

DEVICE_ALL=""
returned=""
AllIPString=""
DEVICE_FROM_WIFI=""
conDev=""
