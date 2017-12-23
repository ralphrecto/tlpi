#!/bin/sh

cd testspace
rm *

dd if=/dev/urandom bs=4096 seek=2 count=2 of=holey > /dev/null 2>&1

../../cp holey holey2
diff holey holey2 > /dev/null 2>&1

if [ $? -ne 0 ]
then
  echo "[FAIL] cp: diff failure"
  exit 1
fi

HOLEY_SIZE=$(ls -s holey | cut -d " " -f 1)
HOLEY2_SIZE=$(ls -s holey2 | cut -d " " -f 1)

if [ $HOLEY_SIZE -ne $HOLEY2_SIZE ]
then
  echo "[FAIL] cp: holes not preserved"
  exit 2
fi

echo "[PASS] cp test"
