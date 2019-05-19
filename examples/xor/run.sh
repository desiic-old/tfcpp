#!/bin/bash
##!
#\file
#\brief Make and build the programme
##
set +ex;

#PROGRAMME ENTRY POINT==========================================================
if [[ $BASH_SOURCE != $0 ]]; then
  echo "Don't source this file, bash it.";
  return;
fi

#prevent running on wrong directory
if ! [[ -f prog.hpp ]]; then
  echo "Please run this programme in directory of prog.hpp";
  exit;
fi

#build
rm -rf build;
mkdir build;
cd build;
cmake ..;

echo -e "\n================================================================================";
echo "Building project...";
make;

#run
echo -e "\n================================================================================";
./prog;
cd ..;

#eof