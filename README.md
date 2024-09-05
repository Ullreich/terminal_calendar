building:
1. run `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build` in the root directory of the repo (the -DCMAKE_EXPORT_COMPILE_COMMANDS is useful for vim development so the treesitter knows where to find the header files)
2. run `cd build` to switch to the build-directory
3. run `make` to make the executable
