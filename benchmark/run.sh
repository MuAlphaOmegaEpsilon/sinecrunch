#!/bin/sh
set -euf

# Navigate to the benchmark folder
cd "$(dirname "$0")"

### COLORING SCHEME ###
ORANGE=$(tput setaf 3)
NOCOLOR=$(tput sgr0)

if [ -d bin ]; then 
	cd bin
	./BM_sinecrunch --benchmark_counters_tabular=true
else
	printf "%sNO BUILD FOLDER FOUND, PLEASE RUN ./setup.sh FIRST%s" "${ORANGE}" "${NOCOLOR}" 
fi
