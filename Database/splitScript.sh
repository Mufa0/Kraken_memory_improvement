#!/bin/bash

if  [ -f "schema.sql" ]; then
  rm schema.sql
fi
if [ -f "dump.sql" ]; then
  rm dump.sql
fi

sqlite3 $1 .schema > schema.sql
sqlite3 $1 .dump > dump.sql
make -f Makefile

rm Splitted/* 2> /dev/null
sleep 5
split -l$((`wc -l < dump.sql`/$2)) dump.sql ./Splitted/dump.split --additional-suffix=".sql" -da 4


cd Splitted;

for i in $(ls);do

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


rm ../Databases/* 2> /dev/null
sleep 5
cd ../Databases
counter=1
for i in $(ls ../Splitted);do
  fName="db$counter.db"
  sqlite3 $fName < ../schema.sql
  sqlite3 $fName < ../Splitted/$i 2> /dev/null
  counter=$((counter+1))
done;
