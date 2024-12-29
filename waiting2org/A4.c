./allthree < 001.in 1> 001.out 2> 001.err
./allthree < 001.in 1> 001.log 2>1
./allthree < 001.in >& 001.log

echo $?

(./althree < tests/002.in) >& althree.log

echo "1" && echo "2"

echo "1" || echo "2"

( ./althree < tests/002.in || false) >& allthree.log

/bin/bash -c "./althree < tests.002.in" >& allthree.log

for i in tests/*.in; do
                echo $i;
 done

echo ${a}b

; - последование, синт элемент, перенос строки 

PATH=$PATH:$(pwd)

seq 1 2 10

folder="myfolder"
mkdir -p $folder && cd $folder && for i in $(seq 1 1 10); do echo $i; echo "$i" > ${i}.in; done && cd -;


export folder

source first.sh

env border=10 1.sh

echo "param 0 is: $0"
echo "param 1 is: $1"

getopts

while getopts b:f: flag
do
    case ${flag} in
        b) border=${OPTARG};;
        f) folder=${OPTARG};;
    esac
done

i=1;
j=$#; //args n
while [ $i -le $j] 
do
    echo "Param $i: $1"
    i=$((i + 1));
    shift 1;
done

"$b" -> val
'$b' -> $b

awk 
sed
find
xargs
sort 
uniq

functions 
