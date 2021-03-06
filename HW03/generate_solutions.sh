#!/bin/sh

HW=03
PROGRAM=./b0b36prp-hw$HW-genref

mkdir -p files
for i in `seq 1 4`
do
   PROBLEM=files/test$i
   echo "Generate random input '$PROBLEM.in'"
   $PROGRAM -generate > $PROBLEM.in 2>/dev/null
   echo "Solve '$PROBLEM.in' and store the reference solution to '$PROBLEM.out'"
   $PROGRAM < $PROBLEM.in > $PROBLEM.out 2>$PROBLEM.err
done

echo "\nGenerate and solve optional assignments"

for i in `seq 1 4`
do
   PROBLEM=files/test-opt$i
   echo "Generate random input '$PROBLEM.in'"
   $PROGRAM -generate -optional > $PROBLEM.in 2>/dev/null
   echo "Solve '$PROBLEM.in' and store the reference solution to '$PROBLEM.out'"
   $PROGRAM < $PROBLEM.in > $PROBLEM.out 2>$PROBLEM.err
done

