# CGREEDY COMPILATION GUIDE


## Requirements:

Please search online for installation instructions specific to your system for the following software:

- CMake
- GCC
- G++
- Python (ensure NumPy is installed)

## Platform-Specific Requirements:

- **Windows:**
  - Install the compiler: **MinGW Distro**
    - [Download link](https://nuwen.net/mingw.html)
    - After installation, remember to add the path to the compiler binaries to your system's PATH.

- **macOS:**
  - Use GCC from Homebrew.
    - [Download link](https://formulae.brew.sh/formula/gcc)

## Compilation Steps:

## Summary

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
make
```

## Detailed Instructions

1. **Create a build directory:**
```bash
mkdir build
cd build
```

2. **Set up compilation:**
  - For macOS, provide the g++ and gcc version installed:
```bash
CXX=g++-13 CC=gcc-13 cmake -DCMAKE_BUILD_TYPE=RELEASE ..
```
  - For other platforms:
```bash
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
```

3. **Compile:**
```bash
make
```


The `cgreedy` folder now has the dynamic library named
`libcgreedy`. `libcgreedy` is stored in the appropriate subfolder based
on the operating system and system architecture. To execute cgreedy in
Python, you only need the `cgreedy` directory.

> **Note:** This repository already contains the shared libraries for cgreedy; however, you can rebuild them if necessary.

If you wish to create a wheel package that can be installed using pip,
first install the necessary tools and then execute the packaging command:

```bash
pip install build
cd wheel_build
python -m build --wheel
```

Once executed, the wheel file will be located in the `wheel_build/dist/`
directory. You can then install it using pip.

```bash
pip install cgreedy-0.0.3-py3-none-any.whl
```

## Usage

Refer to `main_cgreedy.py` for usage instructions.

## PyPI

You can get `cgreedy` also directly from PyPI at the following URL:
[https://pypi.org/project/cgreedy/](https://pypi.org/project/cgreedy/)

Install it using pip:

```bash
pip install cgreedy
```

Happy coding!
