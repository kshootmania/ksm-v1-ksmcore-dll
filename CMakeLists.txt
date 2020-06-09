cmake_minimum_required(VERSION 3.8)
project(ksmcore CXX)

file(GLOB_RECURSE sources
    ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(ksmcore SHARED ${sources})
target_compile_options(ksmcore PUBLIC -O2 -Wall -fPIC)
target_compile_features(ksmcore PUBLIC cxx_std_17)
target_include_directories(ksmcore PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/ksh)
target_link_libraries(ksmcore ksh)

# Link stdc++fs to use <filesystem>
if(NOT MSVC)
    target_link_libraries(ksmcore stdc++fs)
endif(NOT MSVC)
