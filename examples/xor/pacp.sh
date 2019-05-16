#!/bin/bash
set +ex;

cd ../..
eval $(ssh-agent -s);
ssh-add ~/.ssh/devel2-tfcpp;
pacp;
cd examples/xor;

#eof