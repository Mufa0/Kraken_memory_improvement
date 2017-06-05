#!/bin/bash

sqlite3 $1 .schema > schema.sql
sqlite3 $1 .dump > dump.sql
make -f Makefile

split -l$((`wc -l < dump.sql`/$2)) dump.sql ./Splitted/dump.split --additional-suffix=".sql" -da 4

cd Splitted;


for i in $(ls);do
  echo $i
  
  if head -n 2 $i | grep -Fxq "BEGIN TRANSACTION;"
    then
      echo "Containing BEGIN TRANSACTION"
    else
      echo "Putting BEGIN TRANSACTION"
      sed -i '1 s/^/BEGIN TRANSACTION;\n/' $i
  fi
  if tail -n 2 $i | grep "COMMIT;"
    then
      echo "Containing COMMIT"
    else
      echo "Putting commit;"
      echo "COMMIT;" >> $i
  fi
done;
