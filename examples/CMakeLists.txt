cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_FLAGS "-Wall -Werror -march=native -mtune=native -mfpmath=sse -mavx2 -ftree-vectorize")
set(CMAKE_C_FLAGS_RELEASE "-O3 -ftree-vectorize")

add_executable(e1 e1.c)
