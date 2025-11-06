# Python Examples

This directory contains Python examples for using the eyerec library.

## track_pupil.py

Tracks pupil in a video file using either PuRe or PuReST algorithm.

### Usage

```bash
# Using PuRe (detection only)
python track_pupil.py pure path/to/video.mp4

# Using PuReST (tracking - faster and more stable)
python track_pupil.py purest path/to/video.mp4

# Using webcam
python track_pupil.py purest 0
```

### Output

The script outputs CSV data to stdout and displays a window with the detected pupil overlay:

```
x, y, width, height, angle, confidence, runtime_ms,
320.5, 240.3, 45.2, 43.8, 12.5, 0.89, 8.234567,
...
```

Press 'q' to quit.

### Requirements

- pyeyerec (install with `pip install pyeyerec`)
- opencv-python
- numpy

Or if running from source without installing:
```bash
cd /path/to/eyerec
mkdir build && cd build
cmake -DBUILD_PYTHON_BINDINGS=ON -Dpybind11_DIR=$(python -m pybind11 --cmakedir) ..
make pyeyerec
cd ../examples
python track_pupil.py purest /path/to/video.mp4
```
