cmake_minimum_required(VERSION 3.14)
project(HW_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        /usr/local/Cellar/openblas/0.3.5/include
)

option(GLM_TEST_ENABLE_SIMD_SSE4_2 "Enable SSE 4.2 optimizations" OFF)
add_definitions(-DGLM_FORCE_INTRINSICS)

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(-msse4.2)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    add_compile_options(/QxSSE4.2)
elseif((CMAKE_CXX_COMPILER_ID MATCHES "MSVC") AND NOT CMAKE_CL_64)
    add_compile_options(/arch:SSE2) # VC doesn't support SSE4.2
endif()
message(STATUS "GLM: SSE4.2 instruction set")



add_executable(HW_1 main.cpp Task1.h Task1.cpp Task2.h Task2.cpp Task3.h Task3.cpp)