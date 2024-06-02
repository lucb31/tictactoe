#include <stdlib.h>

#include <gui/GameSceneBoard.hpp>
#include <gui/GameSceneGameOver.hpp>
#include <gui/GameSceneMenu.hpp>
#include <gui/SceneManager.hpp>
#include <iostream>

void SceneManager::render(SDL_Renderer *renderer, const int &screenWidth,
                          const int &screenHeight) {
  if (activeScene == NULL) {
    std::__throw_runtime_error("No active scene!");
  }
  activeScene->renderFrame(renderer, screenWidth, screenHeight);

  // Listen for scene switches
  if (activeScene->getNextScene() != GAME_SCENE_UNDEF) {
    switchScene(activeScene->getNextScene());
  }
}

void SceneManager::switchScene(GameScenes targetScene) {
  // Dont need to switch if already active
  if (activeSceneEnum == targetScene) {
    return;
  }
  std::cout << "Trying to switch to scene " << targetScene << "\n";

  // TODO Destroy current scene

  switch (targetScene) {
    case GAME_SCENE_MENU:
      activeScene = new GameSceneMenu();
      /* code */
      break;
    case GAME_SCENE_BOARD:
      activeScene = new GameSceneBoard();
      break;
    case GAME_SCENE_GAME_OVER:
      activeScene = new GameSceneGameOver();
      break;

    default:
      std::__throw_runtime_error("Trying to switch to unknown scene!");
      break;
  }
  activeSceneEnum = targetScene;
  std::cout << "Switched to scene " << activeSceneEnum << "\n";
}