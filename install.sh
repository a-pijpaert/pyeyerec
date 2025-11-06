#!/bin/bash
# Install pyeyerec module to the active Python environment

set -e

# Get the Python site-packages directory
SITE_PACKAGES=$(python3 -c "import site; print(site.getsitepackages()[0])")

echo "Installing pyeyerec to: $SITE_PACKAGES"

# Check if the module is built
MODULE_PATH="build/python/pyeyerec*.so"
if ! ls $MODULE_PATH 1> /dev/null 2>&1; then
    echo "Error: Module not built. Please run 'make pyeyerec' in the build directory first."
    exit 1
fi

# Copy the module
echo "Copying module..."
cp -v $MODULE_PATH "$SITE_PACKAGES/"

echo "Installation complete!"
echo "You can now use: import pyeyerec"
