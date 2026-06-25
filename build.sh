#!/bin/bash
set -e
 
cmake -S . -B build
cmake --build build
mv build/Kiwi .
 
echo "Build complete! Run with: ./Kiwi"
 
