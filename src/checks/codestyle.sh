#!/bin/bash

file="report.txt"

cd src/cat
make clang_check 2> ${file}
status=$( cat ${file} | wc -l )

if [[ ${status} != 0 ]]; then
  cat ${file}
  rm -f ${file}
  exit 1
else
  cd ../grep
  make clang_check 2> ${file}
  status=$( cat ${file} | wc -l )
  if [[ ${status} != 0 ]]; then
    cat ${file}
    rm -f ${file}
    exit 1
  fi
fi
echo "clang-format SUCCESS"
rm -f ${file}
