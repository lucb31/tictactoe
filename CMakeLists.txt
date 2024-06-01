cmake_minimum_required(VERSION 3.14...3.22)
# Project configuration
project(
    tictactoe 
    VERSION 0.1.0 
    LANGUAGES CXX
)

# Include guards
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# Lib code
add_subdirectory(src)
# Executable code
add_subdirectory(apps)