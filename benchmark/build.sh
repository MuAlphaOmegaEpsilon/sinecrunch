#!/bin/sh
set -euf

# Navigate to the benchmark folder
cd "$(dirname "$0")"

### COLORING SCHEME ###
ORANGE=$(tput setaf 3)
NOCOLOR=$(tput sgr0)

if [ -d bin ]; then 
	cd bin
	printf "\\n%sBUILDING BINARY%s\\n" "${ORANGE}" "${NOCOLOR}"
	cmake --build --parallel .
else
	printf "\\n%sNo build folder found, aborting%s\\n" "${ORANGE}" "${NOCOLOR}"
fi
