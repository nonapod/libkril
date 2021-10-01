cmake_minimum_required(VERSION 3.3)
project(libkril)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCE_FILES src/krilya_make_key.c src/Krilya_Key.h src/Krilya_Type.h)
add_executable(krl-key ${SOURCE_FILES})
set(SOURCE_FILES src/krilya_encode.c src/Krilya_Key.h src/Krilya_Type.h)
add_executable(krl-encode ${SOURCE_FILES})
