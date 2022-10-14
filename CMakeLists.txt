cmake_minimum_required(VERSION 3.24)

# set the project name, version and language.
project(example VERSION 1.0.0 LANGUAGES CXX)

# you can set this two variables to require c++20.
# Change 20 to 17 to require c++17. You get the idea.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# add the library path to the search list so that find_package works.
# using semicolon to append to the end of the list.
# the library path is the "extern" folder designated in the common repository readme. Go check that out.
# $ENV{} uses the environment variable define in the system.
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};$ENV{SKSE64LIB_ROOT}")

# skse64 uses the MT(multithreaded static) runtime library, so we'll have to force it.
# otherwise, building dlls defaults to the MD (multithreaded dynamic) library, causing mismatch errors.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "")

# config our version header as taught in the cmake tutorial.
# This makes version number set in CMakeLists.txt visible in our program.
configure_file("cmake/version.hpp.in" "src/version.hpp" @ONLY)

# tell cmake that we are building a dll, named as our project name (example) with one .cpp source file.
add_library(
    "${PROJECT_NAME}"
    SHARED
    "src/main.cpp"
)

# add our version.hpp header location to the include directory, so that we can include it by just saying:
# #include "version.hpp"
target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/src")

# add the include path and .lib file location of skse64 for successful builds.
target_include_directories("${PROJECT_NAME}" PUBLIC "$ENV{SKSE64LIB_ROOT}/include")
target_link_directories("${PROJECT_NAME}" PUBLIC "$ENV{SKSE64LIB_ROOT}/lib")

# don't forget to add the library files.
find_package(common REQUIRED)
find_package(skse64_common REQUIRED)
find_package(xbyak REQUIRED)
find_package(skse64 REQUIRED)
target_link_libraries("${PROJECT_NAME}"
	PUBLIC common
	PUBLIC skse64
)

# after compilation, we copy the dll file to the plugins directory of skse in skyrim's data folder.
add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "$ENV{SKYRIM_SKSE64_PLUGIN_DIR}"
	VERBATIM
)