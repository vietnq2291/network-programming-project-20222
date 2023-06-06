# network-programming-project-20222

Follow these steps to compile the code using `CMakeLists.txt` of client or server:

1. Create a build directory inside server or client directory and navigate to it:

```
mkdir build
cd build
```

2. Run CMake to generate the build files:

```
cmake ..
```

This will generate the necessary build files for your platform.

3. Build the project:

```
cmake --build .
```

This will compile the source files and create the final executable.

After these steps, you should have an executable file in the `build` directory that you can run (`messaging-client` and `messaging-server`).