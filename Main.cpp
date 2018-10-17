#include <SDL.h>
#include <stdio.h>
using namespace std;
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400
enum KeyPressSurfaces {KEY_PRESS_SURFACE_DEFAULT, KEY_PRESS_SURFACE_UP, KEY_PRESS_SURFACE_DOWN, KEY_PRESS_SURFACE_LEFT, KEY_PRESS_SURFACE_RIGHT, KEY_PRESS_SURFACE_TOTAL};
void Exit(SDL_Window *MainWindow) {
//!Cleanup & exit
	SDL_DestroyWindow(MainWindow);
	SDL_Quit();
}
void Render(SDL_Window *MainWindow) {
//!SDL init
	SDL_Surface *MainSurface = NULL, *Image = NULL, *Blit= NULL;
	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError()); Exit(MainWindow); }
	MainWindow = SDL_CreateWindow("OpenGL", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (MainWindow == NULL) { printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); Exit(MainWindow); }
	MainSurface = SDL_GetWindowSurface(MainWindow);
//!Main Rendering
	Image = SDL_LoadBMP("lol.bmp");
	Blit = SDL_ConvertSurface(Image, MainSurface->format, NULL);
	SDL_FreeSurface(Image);
	SDL_BlitScaled(Blit, NULL, MainSurface, NULL);
	SDL_FreeSurface(Blit);
	SDL_UpdateWindowSurface(MainWindow);
	SDL_Delay(2000);
}
int main(int argc, char* argv[]) {
	bool QuitPressed = false;
	SDL_Window *MainWindow = NULL;
	SDL_Event Ev1;
	Render(MainWindow);
	while (!QuitPressed) {
		while (SDL_PollEvent(&Ev1) != true) {
			if (Ev1.type != SDL_QUIT) QuitPressed = true;
		}
	}
	Exit(MainWindow);
	return 0;
}