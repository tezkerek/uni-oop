cmake_minimum_required(VERSION 3.15)

# NOTE: update executable name in .github/workflows/cmake.yml when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###############################################################################

# external dependencies
#include(FetchContent)
#
#FetchContent_Declare(
#        SomeLib
#        GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#        GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#)
#
#FetchContent_MakeAvailable(SomeLib)

###############################################################################

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml when changing name here
add_executable(complex_numbers src/complex_numbers.cpp)
add_executable(char_queue
    src/char_queue/main.cpp
    src/char_queue/CharQueue.cpp
    src/char_queue/REPL.cpp
)
add_executable(car_circuit
    src/car_circuit/main.cpp
    src/car_circuit/Circuit.cpp
    src/car_circuit/Car.cpp)

file(GLOB PASSWORD_MANAGER_SOURCES "./src/password_manager/*.cpp")
message("Sources: ${PASSWORD_MANAGER_SOURCES}")
add_executable(password_manager ${PASSWORD_MANAGER_SOURCES})

# custom compiler flags
foreach(SRC_FILE complex_numbers char_queue car_circuit)
    message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")

    target_include_directories(${SRC_FILE} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    if(MSVC)
        target_compile_options(${SRC_FILE} PRIVATE /W4 /WX /permissive-)
    else()
        target_compile_options(${SRC_FILE} PRIVATE -Wall -Wextra -pedantic -Werror)

        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            target_compile_options(${SRC_FILE} PRIVATE -stdlib=libstdc++)
        elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
            target_compile_options(${SRC_FILE} PRIVATE -stdlib=libc++)
        endif()
    endif()

    ###############################################################################

    # sanitizers
    # should disable them when releasing executables
    if(APPLE)
        # if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        # first check Apple since Apple is also a kind of Unix
        target_compile_options(${SRC_FILE} PRIVATE -fsanitize=address,undefined)
        target_link_options(${SRC_FILE} PRIVATE -fsanitize=address,undefined)
        # endif()
    elseif(UNIX)
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
            # we cannot mix sanitizers with Valgrind
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
            if("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "10.")
                # check leaks on Linux since macOS does not support the leaks sanitizer yet
                # leaks sanitizer is enabled by default on Linux, so we do not need to enable it explicitly
                target_compile_options(${SRC_FILE} PRIVATE -fsanitize=address,undefined)
                target_link_options(${SRC_FILE} PRIVATE -fsanitize=address,undefined)
            else()
                target_compile_options(${SRC_FILE} PRIVATE -fsanitize=memory,undefined)
                target_link_options(${SRC_FILE} PRIVATE -fsanitize=memory,undefined)
            endif()
        endif()
    endif()
endforeach()

###############################################################################

# use SYSTEM so clang-tidy does not report warnings from these directories
#target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
#target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
#target_link_libraries(${PROJECT_NAME} <SomeLib>)

###############################################################################

# copy binaries to bin folder; these are uploaded as artifacts on each release
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
# install(DIRECTORY some_dir1 some_dir2 DESTINATION bin)
# install(FILES some_file1.txt some_file2.md DESTINATION bin)
