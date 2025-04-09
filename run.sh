#!/bin/bash

name=$1

shift

outFolder="Output/"
arguments=""

for arg in "$@"; do
  if [[ $arg == -debug ]] ; then
    outFolder="Output/Debug/"
  elif [[ $arg == -release ]] ; then
    outFolder="Output/Release/"
  elif [[ $arg == -sanitizer ]] ; then
    arguments=" -fsanitize=address,undefined,alignment"
  fi
done

if [[ $name == *.cpp ]] ; then
  g++ -g -o ${outFolder}output $name  $(pkg-config --cflags --libs lua) -I$(pwd) $arguments && ./${outFolder}output
elif [[ $name == *.c ]] ; then
  gcc -g  -o ${outFolder}output $name  $(pkg-config --cflags --libs lua) -I$(pwd) $arguments && ./${outFolder}output
fi

