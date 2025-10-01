#!/usr/bin/env bash

set -e # Exit on error
echo "Cleaning project..."
set -x # Track commands
make clean -f MakefileLinux
