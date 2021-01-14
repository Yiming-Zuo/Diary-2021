#!/bin/bash

curdate=$(date +%m.%d)
git add -A
git commit -m $curdate
git push