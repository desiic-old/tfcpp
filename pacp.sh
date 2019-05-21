#!/bin/bash
set +ex;

#PROGRAMME ENTRY POINT==========================================================
if [[ $BASH_SOURCE != $0 ]]; then
  echo "Don't source this file, bash it.";
  return;
fi

eval $(ssh-agent -s);
ssh-add ~/.ssh/devel2-tfcpp;
git pull && git add -A && git commit -a -m Msg && git push;
sudo pkill -f ssh-agent;

#eof