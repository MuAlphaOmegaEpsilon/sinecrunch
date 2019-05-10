#!/usr/bin/env bash
set -euo pipefail
# Navigate to the project root folder
cd "$(dirname "${BASH_SOURCE[0]}")/.." 

### COLORING SCHEME ###
ORANGE='\033[0;33m'
RC='\033[0m' # Remove color

echo -e "${ORANGE}Downloading Google Benchmark submodule$RC"
git submodule update --init --recursive

echo -e "${ORANGE}Running CMake$RC"
if [ -d build ]; then 
		rm -r build 
fi
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cd ../scripts
./build_bench.sh
echo -e "${ORANGE}Setup done$RC"
