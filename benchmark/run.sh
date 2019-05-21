#!/usr/bin/env bash
set -euo pipefail
# Navigate to the project root folder
cd "$(dirname "${BASH_SOURCE[0]}")/.." 

### COLORING SCHEME ###
ORANGE='\033[0;33m'
RC='\033[0m' # Remove color

if [ -d build ]; then 
	cd build
	./sinecrunch --benchmark_counters_tabular=true
else
	echo -e "${ORANGE}No build folder found, aborting$RC"
fi
