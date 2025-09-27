#!/usr/bin/env	bash

set -e # Exit on error
set -x # Track commands

PM=""

if command -v dnf &> /dev/null; then
	PM="dnf"
elif command -v apt-get &> /dev/null; then
	PM="apt-get"
else
	echo "Error: No supported package manager found (tried dnf and apt-get)."
	exit 1
fi

checkAndInstallPackage() {
	PKG=$1

	if [[ "$PM" == "dnf" ]]; then
		if ! rpm -q "$PKG" &> /dev/null; then
			echo "Installing $PKG..."
			echo "Updating packets..."
			sudo dnf update -y
			sudo dnf install -y "$PKG"
		fi
	elif [[ "$PM" == "apt-get" ]]; then
		if ! dpkg -s "$PKG" &> /dev/null; then
			echo "Installing $PKG..."
			echo "Updating packets..."
			sudo apt-get update
			sudo apt-get install "$PKG"
		fi
	fi
}

if [[ "$PM" == "dnf" ]]; then
	checkAndInstallPackage sdl2-compat-devel
	checkAndInstallPackage SDL2_image-devel
	checkAndInstallPackage SDL2_ttf-devel
elif [[ "$PM" == "apt-get" ]]; then
	checkAndInstallPackage libsdl2-dev
        checkAndInstallPackage libsdl2-image-dev
        checkAndInstallPackage libsdl2-ttf-dev
fi

# Build the makefile objects
echo "Building project..."
make -f MakefileLinux
