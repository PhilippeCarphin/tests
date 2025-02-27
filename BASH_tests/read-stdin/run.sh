
this_dir=$(cd -P $(dirname $0) ; pwd)

# Whitespace is there on purpose
content="first line
   hello asdf   
  
bye bye   
"

echo "${content}" | ${this_dir}/read.sh cat ${this_dir}/cat-output.txt
echo "${content}" | ${this_dir}/read.sh read ${this_dir}/read-output.txt

diff cat-output.txt read-output.txt
