# Installation Guide

Complete installation instructions for eyerec Python bindings on various systems.

## Table of Contents

- [Quick Install](#quick-install)
- [System-Specific Instructions](#system-specific-instructions)
  - [Ubuntu/Debian](#ubuntudebian)
  - [macOS](#macos)
  - [Windows](#windows)
- [Verification](#verification)
- [Troubleshooting](#troubleshooting)

## Quick Install

**Important:** The original tcsantini/eyerec repository does not include Python bindings. You need to use a fork that includes the pybind11 Python bindings.

If you already have CMake, a C++ compiler, and Python development headers installed:

```bash
pip install git+https://github.com/a-pijpaert/eyerec.git
```

Or from source:

```bash
# Clone your fork (not the original tcsantini repo)
git clone https://github.com/a-pijpaert/eyerec.git
cd eyerec
pip install .
```

## System-Specific Instructions

### Ubuntu/Debian

```bash
# Install system dependencies
sudo apt update
sudo apt install -y python3-dev python3-pip cmake g++ libopencv-dev

# Install Python dependencies
pip3 install numpy opencv-python pybind11

# Install eyerec from YOUR fork (replace a-pijpaert with your GitHub username)
pip3 install git+https://github.com/a-pijpaert/eyerec.git

# Or from source:
git clone https://github.com/a-pijpaert/eyerec.git
cd eyerec
pip3 install .
```

**For older Ubuntu versions (< 20.04):**

If CMake is too old:

```bash
pip3 install cmake  # Install newer CMake via pip
```

### macOS

**Using Homebrew:**

```bash
# Install system dependencies
brew install cmake opencv python3

# Install Python dependencies
pip3 install numpy opencv-python pybind11

# Install eyerec from YOUR fork
pip3 install git+https://github.com/a-pijpaert/eyerec.git

# Or from source:
git clone https://github.com/a-pijpaert/eyerec.git
cd eyerec
pip3 install .
```

**Using MacPorts:**

```bash
sudo port install cmake opencv python310
pip3 install numpy opencv-python pybind11
pip3 install git+https://github.com/a-pijpaert/eyerec.git
```

### Windows

**Prerequisites:**
- [Visual Studio 2019 or later](https://visualstudio.microsoft.com/downloads/) with C++ support
- [CMake](https://cmake.org/download/) (3.10 or later)
- [Python 3.6+](https://www.python.org/downloads/)

**Installation:**

```powershell
# Install Python dependencies
pip install numpy opencv-python pybind11

# Install eyerec from YOUR fork
pip install git+https://github.com/a-pijpaert/eyerec.git

# Or from source:
git clone https://github.com/a-pijpaert/eyerec.git
cd eyerec
pip install .
```

**Note:** Make sure CMake and Visual Studio's C++ compiler are in your PATH.

## Using Virtual Environments

It's recommended to use a virtual environment:

```bash
# Create virtual environment
python3 -m venv eyerec_env

# Activate it
source eyerec_env/bin/activate  # Linux/macOS
# or
eyerec_env\Scripts\activate     # Windows

# Install eyerec from your fork
pip install git+https://github.com/a-pijpaert/eyerec.git
```

## Verification

Test that the installation works:

```bash
python3 -c "import pyeyerec; print('Success!'); print(pyeyerec.PuRe().description())"
```

Expected output:
```
Success!
PuRe (santini2018pure)
```

Run the example:

```bash
# Download or use your own eye tracking video
python3 -m pyeyerec.examples.track_pupil purest path/to/video.mp4
```

## Troubleshooting

### "CMake not found"

Install CMake:

```bash
# Ubuntu/Debian
sudo apt install cmake

# macOS
brew install cmake

# Or via pip (any system)
pip install cmake
```

### "pybind11 not found"

```bash
pip install pybind11
```

### "OpenCV not found" during build

The pip package `opencv-python` should be sufficient, but if you need the development libraries:

```bash
# Ubuntu/Debian
sudo apt install libopencv-dev

# macOS
brew install opencv

# Windows
# Use opencv-python from pip (already included)
```

### "Python.h not found"

Install Python development headers:

```bash
# Ubuntu/Debian
sudo apt install python3-dev

# macOS (usually included with Python from Homebrew)
brew install python3

# Windows
# Reinstall Python and make sure to check "Install development files"
```

### Build fails on Windows

Make sure you have:
1. Visual Studio with C++ tools installed
2. CMake in PATH
3. Run from "Developer Command Prompt for VS" or "x64 Native Tools Command Prompt"

### "ImportError: No module named pyeyerec" after installation

Check that you're using the same Python:

```bash
which python3  # Should match the pip you used
pip3 show pyeyerec  # Verify it's installed
```

### Import works but crashes

Make sure your OpenCV versions match:

```bash
# Check versions
python3 -c "import cv2; print(cv2.__version__)"
```

If there's a mismatch, try reinstalling:

```bash
pip uninstall opencv-python opencv-contrib-python
pip install opencv-python
pip install --no-cache-dir --force-reinstall pyeyerec
```

### Building from source without pip

If you want to build manually:

```bash
git clone https://github.com/a-pijpaert/eyerec.git
cd eyerec
mkdir build && cd build

# Configure
cmake -DBUILD_PYTHON_BINDINGS=ON \
      -Dpybind11_DIR=$(python3 -m pybind11 --cmakedir) \
      ..

# Build
make pyeyerec -j$(nproc)

# The module will be in build/python/
# Add to Python path:
export PYTHONPATH=$(pwd)/python:$PYTHONPATH
```

## Getting Help

If you encounter issues not covered here:

1. Check the [GitHub Issues](https://github.com/a-pijpaert/eyerec/issues)
2. Provide your system info:
   ```bash
   python3 --version
   cmake --version
   pip show pyeyerec
   pip show opencv-python
   ```
