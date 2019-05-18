// Code by Tero Hongisto.
// Release under MIT license.

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <Box2D/Box2D.h>

#define TICK_INTERVAL    50

using namespace std;

static Uint32 next_time;
const Uint8 *keys;

Uint32 time_left(void)
{
		Uint32 now;

		now = SDL_GetTicks();
		if(next_time <= now)
				return 0;
		else
				return next_time - now;
}

class GObject {

	double x;
	double y;

	private:	
    //Default Constructor 
    GObject(int xpos,int ypos) 
    { 
        x = static_cast<double>(xpos);  
        y = static_cast<double>(ypos);
    }

	void draw() {
		//blit to screen and x and y
	};
};

int main() {

	SDL_Window *window = NULL;
	SDL_Event event;
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = NULL;
  SDL_Renderer *renderer = NULL;

	bool RUNNING = false;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Cave",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(window, -1, 0);

	const char *filename = "graphics/JEROM_spaceships0_CC-BY-3.png";
	surface = IMG_Load( filename );
	texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == NULL) {
			printf("Could not load texture: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

		next_time = SDL_GetTicks() + TICK_INTERVAL;

		RUNNING=true;
		while(RUNNING) {

			// Get the next event

			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					RUNNING=false;
				}
			}

		keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_ESCAPE]) {
			 RUNNING=false;
    		printf("Exiting.\n");
		}

        /* Select the color for drawing. It is set to red here. */
        SDL_SetRenderDrawColor(renderer, 25, 35, 65, 255);

        /* Clear the entire screen to our selected color. */
        SDL_RenderClear(renderer);
				//Render background
				SDL_RenderCopy(renderer, texture, NULL, NULL);
				/* render the current animation step of our shape */
	      //SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
	        SDL_RenderPresent(renderer);
					SDL_Delay(time_left());
	        next_time += TICK_INTERVAL;
						}

		// Destroy texture
		SDL_DestroyTexture(texture);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

	return EXIT_SUCCESS;
}
