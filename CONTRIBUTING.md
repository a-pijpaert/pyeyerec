# Contributing to pyeyerec

Thank you for your interest in contributing to the Python bindings for eyerec!

## Important Note

This repository is a **fork** that adds Python bindings to the original [tcsantini/eyerec](https://github.com/tcsantini/eyerec) C++ library. 

- **Core algorithms (PuRe, PuReST):** Please submit issues/PRs related to the algorithms themselves to the [original repository](https://github.com/tcsantini/eyerec)
- **Python bindings:** Issues and PRs related to the Python interface, build system, or documentation should be submitted here

## How to Contribute

### Reporting Bugs

If you find a bug in the Python bindings:

1. Check if it's already reported in [Issues](../../issues)
2. Create a new issue with:
   - Python version (`python --version`)
   - OS and version
   - Steps to reproduce
   - Expected vs actual behavior
   - Minimal code example

### Suggesting Enhancements

For Python binding improvements:
- Better numpy/OpenCV integration
- Additional parameter support
- Documentation improvements
- Build system improvements

### Pull Requests

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly
5. Commit with clear messages
6. Push to your fork
7. Open a Pull Request

### Development Setup

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/eyerec.git
cd eyerec

# Install in development mode
pip install -e .

# After C++ changes, rebuild:
cd build
make pyeyerec
```

### Code Style

**Python:**
- Follow PEP 8
- Use meaningful variable names
- Add docstrings to functions

**C++ (pybind11 bindings):**
- Follow the existing style in `cpp/python/py_pure.cpp`
- Add comments for complex conversions
- Handle errors gracefully

### Testing

Before submitting:

```bash
# Test import
python -c "import pyeyerec; print('OK')"

# Test with example
python examples/track_pupil.py purest /path/to/test/video.mp4
```

### Documentation

- Update README.md if adding features
- Update INSTALL.md if changing build process
- Add examples for new functionality

## Questions?

Open an issue with the "question" label.

## License

By contributing, you agree that your contributions will be licensed under the same license as this project (see LICENSE.md).

## Attribution

Remember to maintain proper attribution to the original authors (Thiago Santini et al.) in all contributions. See [CREDITS.md](CREDITS.md).
