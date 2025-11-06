# Quick Local Installation

Als je de module lokaal wilt gebruiken zonder deze op GitHub te zetten:

## Optie 1: Installeer met pip (Aanbevolen)

```bash
cd /home/arthur/Projects/eyerec
pip install .
```

Nu kun je het overal gebruiken:
```python
import pyeyerec
```

## Optie 2: Editable install (voor ontwikkeling)

Als je nog aan de code werkt:

```bash
cd /home/arthur/Projects/eyerec
pip install -e .
```

Na wijzigingen aan de C++ code, rebuild:
```bash
cd build
make pyeyerec
```

## Optie 3: Handmatige build (geen pip)

```bash
cd /home/arthur/Projects/eyerec
mkdir -p build && cd build

cmake -DBUILD_PYTHON_BINDINGS=ON \
      -Dpybind11_DIR=$(python3 -m pybind11 --cmakedir) \
      ..

make pyeyerec -j$(nproc)

# Gebruik door PYTHONPATH te zetten:
export PYTHONPATH=/home/arthur/Projects/eyerec/build/python:$PYTHONPATH
```

Dan in je scripts:
```python
import pyeyerec  # Vindt het via PYTHONPATH
```

## Voor gebruik in een ander project

### Als je eyerec hebt geïnstalleerd met pip:
```python
# Gewoon importeren, werkt overal
import pyeyerec
```

### Als je PYTHONPATH gebruikt:
Voeg toe aan je `~/.bashrc`:
```bash
export PYTHONPATH=/home/arthur/Projects/eyerec/build/python:$PYTHONPATH
```

Of in je Python script:
```python
import sys
sys.path.insert(0, '/home/arthur/Projects/eyerec/build/python')
import pyeyerec
```

## Deïnstalleren

```bash
pip uninstall pyeyerec
```
