#!/bin/bash
./build.sh
for file in "programs/1-scan+parse/valid"/*
do
  first="$(./src/minic pretty < "$file")"
  second="$(./src/minic pretty <<< $first)"
  echo "$file"
  diff <( echo "$first" ) <( echo "$second" )
done
for file in "programs/2-typecheck/valid"/*
do
  first="$(./src/minic pretty < "$file")"
  second="$(./src/minic pretty <<< $first)"
  echo "$file"
  diff <( echo "$first" ) <( echo "$second" )
done
make clean -C ./src