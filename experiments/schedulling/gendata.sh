SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"


EERUN=$SRC_DIR/eerun/bin/eerun
datafile=$SRC_DIR/data/`date +%F_%T`.dat
cat /dev/null > $datafile

processes_file=$1
shift
max_process_n=`cat $processes_file | wc -l`

echo "[*] max no. of processes : $max_process_n"

for i in $(eval echo {1..$max_process_n}); do
    echo "[*] $i "
    echo "#$i" >> $datafile
    #energy_analyser d 10 $EERUN $i $max_process_n $str_command >> $datafile
    fast_analyser 28.4400 50 cat $processes_file \| parallel -j $i >> $datafile
done
