cmake_minimum_required(VERSION 3.15)
project(qcc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find C++20 source files
file(GLOB_RECURSE QUIXCC_CXX_SOURCES "src/*.cc")

add_executable(qcc ${QUIXCC_CXX_SOURCES})
target_include_directories(qcc PRIVATE "src" ${CMAKE_CURRENT_SOURCE_DIR}/../libquixcc/include)

if (CMAKE_BUILD_TYPE STREQUAL "Release") 
    target_compile_options(qcc PRIVATE -g -Wall -Wextra -Wpedantic -Werror -O3 -flto)
    target_link_options(qcc PRIVATE -flto)
    add_custom_command(TARGET qcc POST_BUILD COMMAND strip $<TARGET_FILE:qcc>)
else()
    target_compile_options(qcc PRIVATE -g -Wall -Wextra -Wpedantic -Werror)
endif()
target_link_directories(qcc PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../libquixcc)
target_link_libraries(qcc PRIVATE libquixcc ${LLVM_LIBS} ${LLVM_LD_FLAGS} ${LLVM_CXX_FLAGS} -lstdc++fs)
add_dependencies(qcc libquixcc)

