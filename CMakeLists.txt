cmake_minimum_required( VERSION 3.0 )

project( tcp-server )

# set( CMAKE_CXX_STANDARD 17 )
# set( CMAKE_CXX_STANDARD_REQUIRED ON )
# set( CMAKE_CXX_EXTENSIONS OFF )
# set( CMAKE_BUILD_TYPE Release )

set( CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -march=native -mtune=native" )

SET( CMAKE_EXE_LINKER_FLAGS "-lpthread" )

add_subdirectory( server )

