## Preconditions

### Packages

- gcc - compiler
- cmake - build environment
- catch2 - testing framework



build the project
```bash
rm -rf build
cmake -B build
cmake --build build
```

run the tests
```bash
cd build && ctest --output-on-failure
```