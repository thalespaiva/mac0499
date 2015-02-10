#!/bin/bash

#
#			avwatts.sh
#
# Script simples para medir a potência média consumida por um canal ($CHANNEL)
# durante a execução de um comando ($1). Supõe-se que há um servidor do MW100
# no ip ($MW100IP) na porta ($MW100PORT). A amostragem da potência é feita a
# uma taxa de 1/($SLEEPTIME) por segundo.

CHANNEL=009
MW100IP=200.18.98.206
MW100PORT=34318
SLEEPTIME=0.5

POWER_REGEX="$CHANNEL.*W *\+[0]*([1-9][0-9]*)"

if (($# != 1)); then
    echo "[-] Usage: $0 command "
    exit 1
fi

user_command=$1

$user_command & pid=$!

(( sum_of_powers = 0 ))
(( n = 0 ))
while kill -0 $pid 2> /dev/null; do
    sleep $SLEEPTIME
    power_out=`echo "FD0,$CHANNEL,$CHANNEL" | nc $MW100IP $MW100PORT`
    [[ $power_out =~ $POWER_REGEX ]]
    power_value="${BASH_REMATCH[1]}"
    #echo "[+] $power_value"
    (( sum_of_powers = sum_of_powers + power_value ))
    (( n++ ));
done

average=`echo "scale=2; $sum_of_powers/$n" | bc`
#echo "[*] Sum =  $sum_of_powers"
echo "[+] Number of samples        : $n"
echo "[+] Average power consumption: $average"

