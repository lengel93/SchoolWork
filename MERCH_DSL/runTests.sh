#!/bin/bash
clear
echo "What tests do you want to perform?"
i=1
for dir in $(ls test_programs)
do
  echo "$i) $dir"
  i=$(($i + 1))
done
echo -ne "What is your choice: "
read choice
i=1
for dir in $(ls test_programs)
do
  if [ $i -eq $choice ]
  then
    echo -ne "Testing $dir\n\n"
    for test in $(ls test_programs/$dir)    
    do
      echo -ne "\n_______________________________\nTesting $test\n_______________________________\n"
      cat test_programs/$dir/$test | python testingMain.py
    done
    i=100
   fi
  i=$(($i + 1))
done
