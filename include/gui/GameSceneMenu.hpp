#pragma once
#include <SDL2/SDL.h>

#include <gui/GameScene.hpp>
#include <gui/LTexture.hpp>

class GameSceneMenu : public GameScene {
 private:
  LTexture fontTexture;

  bool init();

 protected:
  GameScenes currentScene = GAME_SCENE_MENU;

 public:
  GameSceneMenu(SceneContext *sceneContext) : GameScene(sceneContext) {
    init();
  }
  ~GameSceneMenu();
  void render();
  void handleKeyPress(SDL_Event *e);
};
