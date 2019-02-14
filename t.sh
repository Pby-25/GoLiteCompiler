#!/bin/bash
./build.sh
for file in "programs/2-typecheck/valid"/*
do
  first="$(~cs520/minic typecheck < "$file")"
  echo "$file"
  echo "$first"
done

for file in "programs/2-typecheck/invalid"/*
do
  first="$(~cs520/minic typecheck < "$file")"
  echo "$file"
  echo "$first"
done