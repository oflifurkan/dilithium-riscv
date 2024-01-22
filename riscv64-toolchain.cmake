# Set the system name to ensure CMake uses cross-compiling mode
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv)

# Specify the cross-compiler
set(CMAKE_C_COMPILER "/opt/riscv/bin/riscv64-unknown-elf-gcc")
set(CMAKE_CXX_COMPILER "/opt/riscv/bin/riscv64-unknown-elf-g++")

# Specify the root directory for the target environment (if you have one)
set(CMAKE_FIND_ROOT_PATH "/opt/riscv/")

# Use the system root to search for programs, libraries, and headers
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

