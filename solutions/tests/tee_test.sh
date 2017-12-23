#!/bin/sh

cd testspace
rm *
cat ../../tee.c | ../../tee f1 f2 > out
diff ../../tee.c f1 && diff ../../tee.c f2 && diff ../../tee.c out

if [ $? -ne 0 ]
then
  echo "[FAIL] tee test"
  exit 1
else
  echo "[PASS] tee test"
fi

rm *
