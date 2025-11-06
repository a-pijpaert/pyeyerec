# EyeRec <img src="https://raw.githubusercontent.com/tcsantini/eyerec/master/resources/icons/eyerec.svg" height=35>

[![Python 3.6+](https://img.shields.io/badge/python-3.6+-blue.svg)](https://www.python.org/downloads/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE.md)
[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.cppreference.com/w/cpp/11)

Modular components for real-time mobile eye tracking.

> **Python Bindings:** This is a fork of the original [tcsantini/eyerec](https://github.com/tcsantini/eyerec) repository with added Python bindings via pybind11. The original C++ library was developed by Thiago Santini and colleagues. This fork adds Python accessibility while maintaining the original C++ implementation.
>
> **Original Repository:** https://github.com/tcsantini/eyerec (C++ only)

## Table of Contents

- [Quick Start - Python](#quick-start---python)
- [Quick Start - C++](#quick-start---c)
- [Available Methods](#available-methods)
- [To-be-Added Methods](#to-be-added-methods)
- [Citation](#citation)

## Quick Start - Python

### Installation

**Requirements:**
- Python 3.6+
- CMake 3.10+
- OpenCV (will be installed automatically via pip)
- C++ compiler with C++11 support

**Install from your fork with Python bindings:**

```bash
# Install dependencies
pip install numpy opencv-python pybind11

# Install eyerec from your repository (replace with your GitHub username)
pip install git+https://github.com/YOUR_USERNAME/eyerec.git

# Or if you've forked it to a different location
pip install git+https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git
```

**Or clone and install locally:**

```bash
git clone https://github.com/YOUR_USERNAME/eyerec.git
cd eyerec
pip install .
```

**Note:** The original tcsantini/eyerec repository does not include Python bindings. Make sure to use a fork that includes the pybind11 bindings (like this one).

### Python Usage

**PuRe - Pupil Detection:**

```python
import cv2
import pyeyerec

# Create detector
detector = pyeyerec.PuRe()

# Load image
frame = cv2.imread('eye_image.png', cv2.IMREAD_GRAYSCALE)

# Detect pupil
result = detector.detect(frame)

if result['valid']:
    print(f"Pupil center: ({result['center_x']}, {result['center_y']})")
    print(f"Confidence: {result['confidence']}")
```

**PuReST - Pupil Tracking (for video):**

```python
import cv2
import pyeyerec

# Create tracker
tracker = pyeyerec.PuReST()

# Process video
cap = cv2.VideoCapture('eye_video.mp4')
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
    
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    timestamp = cap.get(cv2.CAP_PROP_POS_MSEC)
    
    result = tracker.detect_and_track(gray, timestamp)
    
    if result['valid']:
        # Draw result
        center = (int(result['center_x']), int(result['center_y']))
        axes = (int(result['width']/2), int(result['height']/2))
        cv2.ellipse(frame, center, axes, result['angle'], 0, 360, (0, 255, 0), 2)
    
    cv2.imshow('Tracking', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
```

**With custom parameters:**

```python
params = {
    'roi': (100, 100, 400, 300),      # Region of interest (x, y, width, height)
    'min_pupil_diameter': 30.0,       # Minimum pupil size in pixels
    'max_pupil_diameter': 150.0,      # Maximum pupil size in pixels
}

result = detector.detect_with_params(frame, params)
```

## Quick Start - C++

### Building from Source

1. Install dependencies:

```bash
# Ubuntu/Debian:
sudo apt install cmake libopencv-dev build-essential

# macOS:
brew install cmake opencv
```

2. Build and install:

```bash
mkdir build
cd build
cmake ..
make install -j$(nproc)
```

### C++ Usage

**Track pupil in video:**

```bash
./build/cpp/examples/track-pupil pure video.mp4     # Using PuRe
./build/cpp/examples/track-pupil purest video.mp4   # Using PuReST
```

**Using in your CMake project:**

```cmake
find_package(eyerec REQUIRED)
add_executable(your-app main.cpp)
target_link_libraries(your-app eyerec::eyerec)
```

```cpp
#include <eyerec/PuRe.hpp>
#include <opencv2/opencv.hpp>

int main() {
    PuRe detector;
    cv::Mat frame = cv::imread("eye.png", cv::IMREAD_GRAYSCALE);
    
    DetectionParameters params;
    Pupil pupil = detector.detect(frame, params);
    
    if (pupil.valid()) {
        std::cout << "Center: " << pupil.center << std::endl;
        std::cout << "Confidence: " << pupil.confidence << std::endl;
    }
    
    return 0;
}
```

## Available Methods

### Pupil Detection

* **[PuRe](https://www.sciencedirect.com/science/article/abs/pii/S1077314218300146)** - Fast and robust pupil detection
  - Real-time performance
  - Works with challenging conditions (reflections, occlusions)
  - No training required

### Pupil Tracking

* **[PuReST](https://dl.acm.org/doi/10.1145/3204493.3204578)** - Pupil tracking with temporal information
  - Faster than pure detection
  - More stable results over time
  - Automatically falls back to detection when needed

## To-be-added Methods

### Calibration Methods

* (TODO) [CalibMe](https://dl.acm.org/doi/10.1145/3025453.3025950)

### Gaze Estimation Methods

* (TODO) [Grip](https://dl.acm.org/doi/abs/10.1145/3314111.3319835)

## Citation

If you use this library in your research, please cite the original papers:

```bibtex
@article{santini2018pure,
  title={PuRe: Robust pupil detection for real-time pervasive eye tracking},
  author={Santini, Thiago and Fuhl, Wolfgang and Kasneci, Enkelejda},
  journal={Computer Vision and Image Understanding},
  volume={170},
  pages={40--50},
  year={2018},
  publisher={Elsevier}
}

@inproceedings{santini2018purest,
  title={PuReST: Robust pupil tracking for real-time pervasive eye tracking},
  author={Santini, Thiago and Fuhl, Wolfgang and Geisler, David and Kasneci, Enkelejda},
  booktitle={Symposium on Eye Tracking Research and Applications},
  pages={1--5},
  year={2018},
  organization={ACM}
}
```

**Original C++ Implementation:** [tcsantini/eyerec](https://github.com/tcsantini/eyerec)

**Python Bindings:** Added via pybind11 (this fork)

## Acknowledgments

This Python binding is built on top of the excellent work by Thiago Santini, Wolfgang Fuhl, David Geisler, and Enkelejda Kasneci. The core algorithms (PuRe and PuReST) remain unchanged from the original implementation. This fork only adds Python accessibility through pybind11 bindings.

## I Don't Really Want to Compile Stuff

What you are probably looking for then is
[EyeRecToo](https://www.hci.uni-tuebingen.de/research/Projects/eyerectoo.html),
a Windows application that provides:
* real-time slippage-robust mobile eye tracking
* multiple pupil detection and tracking methods
* multiple gaze estimation methods
* high-usability gaze calibration
* recording of eye-tracking videos and data
* fiduciary marker detection
* support for multiple head-mounted eye trackers, including the popular [Pupil Core hardware](https://pupil-labs.com/products/core/).

## License

See [LICENSE.md](LICENSE.md) for details.
