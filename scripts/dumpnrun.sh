

shared_file=$1
shift

str_command=$@

powerdump $total_time >> $shared_file & pid_pd=$!
echo "[*] Recording in $shared_file "
sleep $time_to_run
echo "[*] Running $str_command ..."
echo "#" >> $shared_file & eval "$str_command > /dev/null" & pid_cmd=$!
wait $pid_cmd
echo "#" >> $shared_file
echo "[+] Command finished."
wait $pid_pd
echo "[+] powerdump finished."
