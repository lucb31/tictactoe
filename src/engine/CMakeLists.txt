# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/engine/*.hpp")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(
    ttt_engine 
    Board.cpp 
    player/AIPlayer.cpp 
    player/RealPlayer.cpp 
    ${HEADER_LIST}
)

# We need this directory, and users of our library will need it too
target_include_directories(ttt_engine PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(ttt_engine PUBLIC cxx_std_11)