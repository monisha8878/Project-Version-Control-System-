#!/bin/bash
g++ -std=c++17 -o filemanager mainfunction4.cpp 

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful. Running program..."
./filemanager
