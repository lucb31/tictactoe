# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(
    ttt_library 
    engine/Board.cpp 
    engine/player/AIPlayer.cpp 
    engine/player/RealPlayer.cpp 
    gui/GameUI.cpp 
    gui/GameScene.cpp 
    gui/GameSceneBoard.cpp 
    gui/GameSceneMenu.cpp 
    gui/GameSceneGameOver.cpp 
    gui/SceneManager.cpp 
    ${HEADER_LIST}
)

# We need this directory, and users of our library will need it too
target_include_directories(ttt_library PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(ttt_library PUBLIC cxx_std_11)

# Include SDL2: 
# Todo: Move to GameUI makefile
find_package(SDL2 REQUIRED)
include_directories(ttt_library ${SDL2_INCLUDE_DIRS})
target_link_libraries(ttt_library ${SDL2_LIBRARIES})

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

