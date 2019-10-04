# Tests for flag-set-cpp

Building tests:

    apt install build-essential pkg-config cmake libgtest-dev
    sudo bash -c 'cd /usr/src/googletest && cmake . && cmake --build . --target install'

    cd build
    cmake .. # optionally with -DCMAKE_BUILD_TYPE=Debug
    cmake --build . # optionally with VERBOSE=1

Running tests, inside `build` directory:

    ctest # optionally with -V
