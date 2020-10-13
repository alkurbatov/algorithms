# algorithms

Algorithms development and testing playground based on one of Coursera courses.

## Requirements
* OS X (not tested on other platforms, although may work).
* A compiler with C++17 support.
* boost (>= 1.71.0).
* cmake (>= 3.18).
* gtest (>= 1.10.0).

## Build instructions
```bash
# Create build directory.
$ mkdir build && cd build

# Generate Makefiles.
# Use 'cmake -DCMAKE_BUILD_TYPE=Debug ../' for additional run options and debuginfo.
$ cmake ../

# Build the project.
$ VERBOSE=1 cmake --build . --parallel

# Run a solution, e.g.:
$ ./bin/data_structures/check_brackets

# Run tests for a solution (available only in the Debug mode), e.g.:
$ ./bin/data_structures/check_brackets test
```

## License

Copyright (c) 2020 Alexander Kurbatov

Licensed under the [GPLv3 license](LICENSE).
