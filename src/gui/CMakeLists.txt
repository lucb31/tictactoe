file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/gui/*.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(
    ttt_gui 
    GameUI.cpp 
    GameSceneBoard.cpp 
    GameSceneMenu.cpp 
    GameSceneGameOver.cpp 
    ${HEADER_LIST}
)

# Include SDL2: 
# Todo: Move to GameUI makefile
find_package(SDL2 REQUIRED)
include_directories(ttt_gui ${SDL2_INCLUDE_DIRS})
target_link_libraries(ttt_gui ${SDL2_LIBRARIES})

# We need this directory, and users of our library will need it too
target_include_directories(ttt_gui PUBLIC ../include/gui)

# All users of this library will need at least C++11
target_compile_features(ttt_gui PUBLIC cxx_std_11)