#include <stdlib.h>

#include <gui/GameSceneBoard.hpp>
#include <gui/GameSceneGameOver.hpp>
#include <gui/GameSceneMenu.hpp>
#include <gui/SceneManager.hpp>
#include <iostream>

void SceneManager::render() {
  if (activeScene == NULL) {
    std::__throw_runtime_error("No active scene!");
  }
  activeScene->render();

  // Listen for scene switches
  if (activeScene->getNextScene() != GAME_SCENE_UNDEF) {
    switchScene(activeScene->getNextScene());
  }
}

void SceneManager::switchScene(GameScenes targetScene) {
  // Dont need to switch if already active
  if (activeScene != NULL && activeScene->getCurrentScene() == targetScene) {
    return;
  }
  std::cout << "Trying to switch to scene " << targetScene << "\n";

  // Destroy current scene
  delete activeScene;

  switch (targetScene) {
    case GAME_SCENE_MENU:
      activeScene = new GameSceneMenu(sceneContext);
      break;
    case GAME_SCENE_BOARD:
      activeScene = new GameSceneBoard(sceneContext);
      break;
    case GAME_SCENE_GAME_OVER:
      activeScene = new GameSceneGameOver(sceneContext);
      break;

    default:
      std::__throw_runtime_error("Trying to switch to unknown scene!");
      break;
  }
  std::cout << "Switched to scene " << targetScene << "\n";
}