#!/bin/bash

dirName=$(date '+%Y-%m-%d_%H-%M-%S') 
mkdir "$dirName"

for i in $(seq 101 110); do
    mkdir "$dirName/file$i"
    echo "Python" > "$dirName/file$i/tuser501.txt"
    echo "Java" > "$dirName/file$i/tuser502.txt"
    echo "Java Script" > "$dirName/file$i/tuser503.txt"
    echo "C++" > "$dirName/file$i/tuser504.txt"
    echo "C" > "$dirName/file$i/tuser505.txt"
    echo "C#" > "$dirName/file$i/tuser506.txt"
    echo "SQL" > "$dirName/file$i/tuser507.txt"
    echo "COBOL" > "$dirName/file$i/tuser508.txt"
    echo "Kotlin" > "$dirName/file$i/tuser509.txt"
    echo "FORTRAN" > "$dirName/file$i/tuser510.txt"
done

