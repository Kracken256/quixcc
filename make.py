#!/usr/bin/env python3

import os
import sys

cwd = os.getcwd()


if not os.path.exists(os.path.join(cwd, 'libquixcc')):
    print("Please run this script from the root of the repository.")
    sys.exit(1)

# Check if Docker is installed
if os.system('docker --version') != 0:
    print("Docker is not installed.")
    sys.exit(1)

print("Building Docker containers...")

# Build the debug env container
if os.system('docker build -t quixcc-debug:latest -f env/Debug.Dockerfile .') != 0:
    print("Debug build failed.")
    sys.exit(1)

# Build the release env container
if os.system('docker build -t quixcc-release:latest -f env/Release.Dockerfile .') != 0:
    print("Release build failed.")
    sys.exit(1)

if '--release' in sys.argv:
    print("Building release...")
    if os.system('docker run -v {0}:/app --rm -it quixcc-release:latest'.format(cwd)) != 0:
        print("Release build failed.")
        sys.exit(1)
    print("Release build complete.")
    sys.exit(0)

if '--debug' in sys.argv:
    print("Building debug...")
    if os.system('docker run -v {0}:/app --rm -it quixcc-debug:latest'.format(cwd)) != 0:
        print("Debug build failed.")
        sys.exit(1)
    print("Debug build complete.")
    sys.exit(0)
