#!/bin/sh

for filename in $1/*
do
  remap $filename $2 "$3/$(basename -- "$filename")"
done;