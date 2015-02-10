#!/bin/bash

if (($# != 1)); then
    echo "[-] Usage: $0 command "
    exit 1
fi

SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
user_command=$1

#POWER_REGEX="$CHANNEL.*W *\+[0]*([1-9][0-9]*)"
#[+] Average power consumption: 1039.20
POWER_REGEX="\[\+\] Average power consumption: (.+)"

#echo "SRC_DIR = $SRC_DIR"
time1=$(($(date +%s%6N)))
power_out=`$SRC_DIR/avwatts.sh $user_command`
time2=$(($(date +%s%6N)))
elapsed_time=$(( ($time2 - $time1) ))

#echo $power_out
[[ $power_out =~ $POWER_REGEX ]]
av_power_value="${BASH_REMATCH[1]}"

total_energy=`echo "scale=2; $av_power_value * $elapsed_time / 1000000" | bc`
pretty_time=`echo "scale=4; $elapsed_time / 1000000" | bc`
#echo "[+] Elapsed time         : $pretty_time seconds"
#echo "[+] Total energy consumed: $total_energy Joules"
echo $total_energy