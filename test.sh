#!/bin/bash

FILES=./tests/*

for f in $FILES
do
  echo "Testing $f"
  ./plpgsqllint.app --filename $f
done
