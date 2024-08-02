#!/bin/bash
i=1
echo $1;
while [ $i -le $1 ]
do
    i=$((i+1));
    echo $RANDOM;
done
