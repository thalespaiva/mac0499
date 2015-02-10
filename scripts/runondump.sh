
msg=$1
shift
shared_file=$1
shift

str_command=$@

echo "# $msg" >> $shared_file; 
eval "$str_command";
echo "# fim $msg" >> $shared_file
