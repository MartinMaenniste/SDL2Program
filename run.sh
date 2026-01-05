#!/usr/bin/env bash

set -e # Exit on error
#set -x # Track commands

echo "Starting program"
if [[ $# -eq 0 ]]; then
	make run -f MakefileLinux
else
	make run -f MakefileLinux ARGS="$@"
fi
