#!/bin/bash
HEADER=all_tests_headers.h
echo "#ifndef __ALL_HEADERS__" > $HEADER
echo "#define __ALL_HEADERS__" >> $HEADER
for file in tests/*.h
do
    echo "#include \"$file\"" >> $HEADER
done
echo "#endif" >> $HEADER
