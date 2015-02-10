#!/bin/bash

#
#                               powerdump
#
# Script simples para mostrar os valores de potência consumida por uma máquina
# através de um sistema Yokogawa MW100. A duração da medição é de ($1) segundo.
#
# Supõe que o medidor de potência associado à máquina está conectado no canal
# ($CHANNEL) do servidor de dados. Este servidor tem IP ($MW100IP) e possui um
# serviço de Telnet na porta ($MW100PORT). A amostragem é feia a uma taxa de 
# aproximadamente 1/($SLEEPTIME) por segundo.

CHANNEL=009
MW100IP=200.18.98.206
MW100PORT=34318
SLEEPTIME=0.5

POWER_REGEX="$CHANNEL.*W *\+[0]*([1-9][0-9]*)"

if (($# != 1)); then
    echo "[-] Usage: $0 <time>"
    exit 1
fi

sleep $1 & pid=$!

time_init="$(($(date +%s%N)/1000000))"

while kill -0 $pid 2> /dev/null; do
    sleep "$SLEEPTIME"
    power_out=`echo "FD0,$CHANNEL,$CHANNEL" | nc $MW100IP $MW100PORT`
    [[ $power_out =~ $POWER_REGEX ]]
    power_value="${BASH_REMATCH[1]}"
    i=$((${#power_value}-1))
    power_value="${power_value:0:$i}"."${power_value:$i:1}"
    time=$(($(date +%s%N)/1000000 - $time_init ))
    formtime=`echo "scale=2; $time/1000" | bc`
    echo "$formtime,$power_value"
done
