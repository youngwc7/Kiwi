#!/bin/bash
set -e

if [ "$1" == "clean" ]; then
    rm -rf build
    rm -f Kiwi
    echo "Clean complete!"
    exit 0
fi

cmake -S . -B build
cmake --build build
mv build/Kiwi .
 
echo "Build complete! Run with: ./Kiwi"
 
