#!/bin/sh

for filename in $1/*
do
  hqx -s $2 $filename "$3/$(basename -- "$filename")"
done;