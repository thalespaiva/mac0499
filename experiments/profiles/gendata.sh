
d=`date +%F_%T`

mem_datafile=./mem_bound/data/$d.dat
cpu_datafile=./cpu_bound/data/$d.dat
io_datafile=./io_bound/data/$d.dat

cat /dev/null > $mem_datafile
cat /dev/null > $cpu_datafile
cat /dev/null > $io_datafile

tottime=$1

powerdump $tottime $mem_datafile &
for i in {1..8}; do
   sleep 10
   sysbench --num-threads=$i --test=memory --memory-block-size=2G run >> log
done

powerdump $tottime $cpu_datafile &
for i in {1..8}; do
   sleep 10
   sysbench –test=cpu –cpu-max-prime=20000 run >> log
done

powerdump $tottime $io_datafile &
for i in {1..8}; do
   sleep 10
   sysbench –test=fileio –file-total-size=24G -file-test-mode=rndrw –max-time=50 –max-requests=0 run >> log
done
