SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ENERGY_ANALYSER=$SRC_DIR/../../../mw100_recorder/tools/energy_analyser
C_EXECS=$SRC_DIR/C/bin
PYTHON_EXECS=$SRC_DIR/Python



declare -A c_workloads=(
["dead_local_store"]= "2000000000"         #3.8
["non_short_circuit"]= "400000000"         #2.4
["parameter_by_value"]="800000000"        #3.3
["redundant_call"]=    "40000000"             #2.2
["repeated_conditionals"]="400000000"     #2.3
["self_assignement"]="1000000000"          #1.0

["wo_dead_local_store"]="2000000000"         #3.8
["wo_non_short_circuit"]="400000000"         #2.4
["wo_parameter_by_value"]="800000000"        #3.3
["wo_redundant_call"]="40000000"             #2.2
["wo_repeated_conditionals"]="400000000"     #2.3
["wo_self_assignement"]="1000000000"          #1.0
)

N_OF_ANALYSIS_ITERATIONS=50

datafile=$SRC_DIR/data/`date +%F_%T`.dat
cat /dev/null > $datafile

#for f in $PYTHON_EXECS/*; do
#    echo "[+] $f"
#    #$ENERGY_ANALYSER $N_OF_ANALYSIS_ITERATIONS $f $N_OF_PYTHON_ITERATIONS | tee --append $datafile
#    time $f $N_OF_PYTHON_ITERATIONS | tee --append $datafile
#    sleep 1
#done

cd $C_EXECS

for f in `ls `; do
    echo "[+] $f ${c_workloads["$f"]}"
    $ENERGY_ANALYSER d $N_OF_ANALYSIS_ITERATIONS ./$f ${c_workloads["$f"]} >> $datafile
    sleep 5
done
