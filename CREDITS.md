# Credits and Attribution

## Original Work

The core algorithms and C++ implementation of **eyerec** were developed by:

- **Thiago Santini** - Original author and algorithm designer
- **Wolfgang Fuhl** - Co-author
- **David Geisler** - Co-author (PuReST)
- **Enkelejda Kasneci** - Co-author

**Original Repository:** https://github.com/tcsantini/eyerec

## Publications

The algorithms implemented in this library are described in the following peer-reviewed publications:

### PuRe Algorithm

```bibtex
@article{santini2018pure,
  title={PuRe: Robust pupil detection for real-time pervasive eye tracking},
  author={Santini, Thiago and Fuhl, Wolfgang and Kasneci, Enkelejda},
  journal={Computer Vision and Image Understanding},
  volume={170},
  pages={40--50},
  year={2018},
  publisher={Elsevier},
  doi={10.1016/j.cviu.2018.02.002}
}
```

**Paper:** https://www.sciencedirect.com/science/article/abs/pii/S1077314218300146

### PuReST Algorithm

```bibtex
@inproceedings{santini2018purest,
  title={PuReST: Robust pupil tracking for real-time pervasive eye tracking},
  author={Santini, Thiago and Fuhl, Wolfgang and Geisler, David and Kasneci, Enkelejda},
  booktitle={Proceedings of the 2018 ACM Symposium on Eye Tracking Research \& Applications},
  pages={1--5},
  year={2018},
  organization={ACM},
  doi={10.1145/3204493.3204578}
}
```

**Paper:** https://dl.acm.org/doi/10.1145/3204493.3204578

## Python Bindings

The Python bindings via pybind11 were added as an extension to the original C++ library. These bindings:

- Provide Python access to the PuRe and PuReST algorithms
- Maintain the original C++ implementation without modifications
- Add convenient NumPy array to OpenCV Mat conversions
- Include parameter handling for Python dictionaries

**Python Bindings Contributors:**
- Arthur Pijpaert (initial implementation)
- [Add other contributors here]

## Dependencies

This project builds upon:

- **OpenCV** - Computer vision library
- **pybind11** - Python/C++ binding library
- **CMake** - Build system

## License

The original eyerec library and this fork are distributed under the terms specified in [LICENSE.md](LICENSE.md).

## Citation

If you use this library in your research, please cite the original papers (see above) and acknowledge the original authors. If you specifically use the Python bindings in a way that's central to your work, you may also mention this fork.

## Related Projects

- **EyeRecToo:** A Windows application built on eyerec - https://www.hci.uni-tuebingen.de/research/Projects/eyerectoo.html
- **Original eyerec (C++ only):** https://github.com/tcsantini/eyerec

## Acknowledgments

Special thanks to Thiago Santini and colleagues for making their eye tracking research available as open source software, enabling the broader research community to build upon their work.
