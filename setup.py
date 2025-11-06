#!/usr/bin/env python3
"""
Setup script for building eyerec Python bindings
"""

import os
import sys
import subprocess
from pathlib import Path

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the extensions. "
                "Install with: pip install cmake or apt-get install cmake"
            )

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        
        # Find pybind11
        try:
            import pybind11
            pybind11_dir = pybind11.get_cmake_dir()
        except ImportError:
            raise RuntimeError(
                "pybind11 is required to build this package. "
                "Install with: pip install pybind11"
            )
        
        # Ensure we use the eyerec source directory  
        sourcedir = ext.sourcedir if ext.sourcedir else str(Path(__file__).parent.absolute())
        
        # Create extension directory if it doesn't exist
        os.makedirs(extdir, exist_ok=True)
        
        cmake_args = [
            f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}',
            f'-DPYTHON_EXECUTABLE={sys.executable}',
            f'-Dpybind11_DIR={pybind11_dir}',
            '-DBUILD_PYTHON_BINDINGS=ON',
        ]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        cmake_args += [f'-DCMAKE_BUILD_TYPE={cfg}']
        
        # Add parallel build flag
        import multiprocessing
        build_args += ['--', f'-j{multiprocessing.cpu_count()}']

        env = os.environ.copy()
        env['CXXFLAGS'] = f'{env.get("CXXFLAGS", "")} -DVERSION_INFO=\\"{self.distribution.get_version()}\\"'
        
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        
        print("=" * 60)
        print("Building eyerec Python bindings...")
        print(f"Source dir: {sourcedir}")
        print(f"Build temp: {self.build_temp}")
        print(f"Extension dir: {extdir}")
        print("=" * 60)
        
        subprocess.check_call(
            ['cmake', sourcedir] + cmake_args, 
            cwd=self.build_temp, 
            env=env
        )
        subprocess.check_call(
            ['cmake', '--build', '.', '--target', 'pyeyerec'] + build_args, 
            cwd=self.build_temp
        )
        
        # Copy the built module to the correct location
        import shutil
        import glob
        built_so = glob.glob(os.path.join(self.build_temp, 'python', 'pyeyerec*.so'))
        if built_so:
            shutil.copy(built_so[0], extdir)
            print(f"Copied {built_so[0]} to {extdir}")
        
        print("=" * 60)
        print("Build complete!")
        print("=" * 60)


# Read long description
long_description = ""
readme_file = Path(__file__).parent / 'README.md'
if readme_file.exists():
    long_description = readme_file.read_text(encoding='utf-8')

setup(
    ext_modules=[CMakeExtension('pyeyerec')],
    cmdclass={'build_ext': CMakeBuild},
    packages=[],  # No Python packages, only C++ extension
    py_modules=[],  # No Python modules
)
