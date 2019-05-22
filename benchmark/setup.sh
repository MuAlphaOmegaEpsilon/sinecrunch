#!/bin/sh
set -euf

# Navigate to the benchmark folder
cd "$(dirname "$0")"

### COLORING SCHEME ###
ORANGE=$(tput setaf 3)
NOCOLOR=$(tput sgr0)

printf "%sDOWNLOADING SUBMODULES%s\\n" "${ORANGE}" "${NOCOLOR}"
git submodule update --init --recursive

printf "\\n%sRUNNING CMAKE%s\\n" "${ORANGE}" "${NOCOLOR}"
if [ -d bin ]; then 
	rm -r bin 
fi
mkdir bin
cd bin
cmake .. -DCMAKE_BUILD_TYPE=Release
../build.sh
printf "\\n%sSETUP DONE%s\\n" "${ORANGE}" "${NOCOLOR}"
