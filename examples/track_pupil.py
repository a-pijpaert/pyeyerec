#!/usr/bin/env python3
"""
Pupil detection and tracking - matches the C++ track-pupil example
Usage: python track_pupil.py <algorithm-name> <path-to-video>
       algorithm-name: pure or purest
"""

import sys

# Try to import pyeyerec (should work if installed via pip)
try:
    import pyeyerec
except ImportError:
    # If not installed, try to find it in the build directory
    import os
    sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build', 'python'))
    import pyeyerec

import time
import cv2


def draw_overlay(bgr, pupil, min_confidence=0.66):
    """Draw pupil overlay on frame"""
    if pupil['confidence'] > min_confidence:
        g = int(255 * (pupil['confidence'] - min_confidence) / (1 - min_confidence))
        r = 255 - g
        
        center = (int(pupil['center_x']), int(pupil['center_y']))
        axes = (int(pupil['width']/2), int(pupil['height']/2))
        
        cv2.ellipse(bgr, center, axes, pupil['angle'], 0, 360, (0, g, r), 2)


def print_usage_and_exit():
    """Print usage information and exit"""
    print("Usage:", file=sys.stderr)
    print(f"  {sys.argv[0]} <algorithm-name> <path-to-video>", file=sys.stderr)
    print("  algorithm-name: pure or purest", file=sys.stderr)
    sys.exit(1)


def main():
    if len(sys.argv) < 3:
        print_usage_and_exit()
    
    algorithm = sys.argv[1].lower()
    video_file = sys.argv[2]
    
    # Pick algorithm
    if algorithm == "pure":
        tracker = pyeyerec.PuRe()
        use_tracking = False
    elif algorithm == "purest":
        tracker = pyeyerec.PuReST()
        use_tracking = True
    else:
        print(f"Unknown algorithm: {sys.argv[1]}", file=sys.stderr)
        print("Expected one of [ pure, purest ]", file=sys.stderr)
        print_usage_and_exit()
    
    print(f"Using: {tracker.description()}", file=sys.stderr)
    
    # Open video
    cap = cv2.VideoCapture(video_file)
    if not cap.isOpened():
        print(f"Could not open {video_file}", file=sys.stderr)
        print_usage_and_exit()
    
    # Print CSV header
    print("x, y, width, height, angle, confidence, runtime_ms,")
    
    # Iterate over frames
    while True:
        ret, bgr = cap.read()
        if not ret or bgr is None or bgr.size == 0:
            break
        
        timestamp = cap.get(cv2.CAP_PROP_POS_MSEC)
        
        # Prepare images
        if len(bgr.shape) == 3 and bgr.shape[2] == 3:
            gray = cv2.cvtColor(bgr, cv2.COLOR_BGR2GRAY)
        else:
            gray = bgr
            bgr = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
        
        # Detect/track pupil and measure runtime
        start_time = time.perf_counter()
        if use_tracking:
            pupil = tracker.detect_and_track(gray, timestamp)
        else:
            pupil = tracker.detect(gray)
        runtime_ms = (time.perf_counter() - start_time) * 1000.0
        
        # Print results to stdout (CSV format)
        print(f"{pupil['center_x']}, {pupil['center_y']}, {pupil['width']}, "
              f"{pupil['height']}, {pupil['angle']}, {pupil['confidence']}, {runtime_ms:.6f},")
        
        # Draw overlay
        draw_overlay(bgr, pupil)
        
        # Show frame
        cv2.imshow('dbg', bgr)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break
    
    cap.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
