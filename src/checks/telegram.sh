#!/bin/bash

if [[ $CI_JOB_STATUS == 'failed' ]]; then
  CI_JOB_STATUS="FAILED"
else
  CI_JOB_STATUS="SUCCESS"
fi

readonly TOKEN="7155512534:AAHkufYfyqkljgr2pSTPenWf9x-4api5bP0"
readonly ID="858123281"
TEXT="Job name: $CI_JOB_NAME Status: $CI_JOB_STATUS Project: $CI_PROJECT_NAME"
curl --data chat_id=${ID} --data-urlencode "text=${TEXT}" "https://api.telegram.org/bot${TOKEN}/sendMessage?parse_mode=HTML"
