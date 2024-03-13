#!/bin/bash

main() {
  file="log.txt"
  cd src/cat
  rm -f ./log.txt
  make test
  if [[ -f ${file} ]]; then
    rm -f ./log.txt
    echo "cat tests failure"
    exit 1
  else
    cd ../grep
    make test
    if [[ -f ${file} ]]; then
      rm -f ./log.txt
      echo "grep tests failure"
      exit 1
    fi
  fi
}

main