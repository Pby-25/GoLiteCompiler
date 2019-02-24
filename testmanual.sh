#!/bin/bash
./build.sh
for file in "programs/1-scan+parse/valid"/*
do
  echo -e "\n\n\n-------------------------------------"
  echo "$file"
  echo -e "\nORIGINAL-------------------------------------\n"
  cat $file
  parse="$(./src/minic parse < "$file")"
  echo "$parse"
  # pretty="$(./src/minic pretty < "$file")"
  # symbol="$(./src/minic symbol < "$file")"
  # codegen="$(./src/minic codegen < "$file")"
  # echo -e "\nPRETTY-------------------------------------\n"
  # echo "$pretty"
  # echo -e "\nSYMBOL-------------------------------------\n"
  # echo "$symbol"
  # echo -e "\ncodegen-------------------------------------\n\n\n\n"
  # echo "$codegen"
done