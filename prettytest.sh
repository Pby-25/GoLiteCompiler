#!/bin/bash
./build.sh
for file in "programs/1-scan+parse/valid"/*
do
  first="$(./src/minic pretty < "$file")"
  second="$(./run.sh pretty "$file" | ./src/minic pretty)"
  echo "$file"
  # echo "$second"
  diff <( echo "$first" ) <( echo "$second" )
  
done
make clean -C ./src