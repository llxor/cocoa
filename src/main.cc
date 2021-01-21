#include <SDL2/SDL.h>

int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;

  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return 1;
  }

  // Create the window where we will draw.
  window = SDL_CreateWindow(NULL, 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

  // We must call SDL_CreateRenderer in order for draw calls to affect this
  // window.
  renderer = SDL_CreateRenderer(window, -1, 0);

  // Select the color for drawing. It is set to #b19bd9 here.
  SDL_SetRenderDrawColor(renderer, 0xb1, 0x9b, 0xd9, 0xff);

  // Clear the entire screen to our selected color.
  SDL_RenderClear(renderer);

  // Up until now everything was drawn behind the scenes.
  // This will show the new, red contents of the window.
  SDL_RenderPresent(renderer);

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN) {
        quit = true;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        quit = true;
      }
    }
  }

  // Always be sure to clean up
  SDL_Quit();
  return 0;
}
