SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

datafile=$SRC_DIR/data/`date +%F_%T`.dat
cat /dev/null > $datafile

BUCKETBENCH="$SRC_DIR/bin/bucketbench"
QUICKBENCH="$SRC_DIR/bin/quickbench"

array_size=0
seed=0
for i in {1..20}; do
    (( array_size = $array_size + 10000000 ));
    (( seed = $seed + 13 ))
    echo "[*] $array_size "

    echo "#heapbench_$array_size "
    echo "#heapbench_$array_size " >> $datafile
    $HEAPBENCH 30 $array_size $seed 28.4400 >> $datafile

    echo "#mergebench_$array_size "
    echo "#mergebench_$array_size " >> $datafile
    $MERGEBENCH  30 $array_size $seed 28.4400 >> $datafile

    echo "#quickbench_$array_size "
    echo "#quickbench_$array_size " >> $datafile
    $QUICKBENCH  30 $array_size $seed 28.4400 >> $datafile

    echo "#bucketbench0.5_$array_size "
    echo "#bucketbench0.5_$array_size " >> $datafile
    $BUCKETBENCH05 30 $array_size $seed 28.4400 >> $datafile

    echo "#bucketbench1.0_$array_size "
    echo "#bucketbench1.0_$array_size " >> $datafile
    $BUCKETBENCH10 30 $array_size $seed 28.4400 >> $datafile

    echo "#bucketbench1.5_$array_size "
    echo "#bucketbench1.5_$array_size " >> $datafile
    $BUCKETBENCH15 30 $array_size $seed 28.4400 >> $datafile
done
