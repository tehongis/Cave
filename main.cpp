// Code by Tero Hongisto.
// Release under MIT license.

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <Box2D/Box2D.h>

#define TICK_INTERVAL    50
#define TWO_M_PI           3.14159265358979323846*2  /* pi */

using namespace std;


static const char *nameMusic = "music/Stardrive.mp3";
static const char *nameBackground = "graphics/Aurora.jpg";
static const char *nameBox = "graphics/RTS_Crate.png";
static const char *nameShip = "graphics/Ship_A.png";

static Uint32 next_time;
static const Uint8 *keys;
//The gWindow gRenderer
static SDL_Renderer* gRenderer = NULL;
static SDL_Texture *textureBackground = NULL;
static SDL_Texture *textureShip = NULL;
static SDL_Texture *textureBox = NULL;

static double angle = 0.0;
static Uint32 time_left(void)
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
	}
};



static SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

int main() {

	SDL_Window *gWindow = NULL;
	SDL_Event event;

	bool RUNNING = false;
 	
// start SDL with video and audio support
if(SDL_Init( SDL_INIT_VIDEO |  SDL_INIT_AUDIO ) == -1) {
    printf("SDL_Init: %s\n", SDL_GetError());
    exit(1);
}

    Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);

	gWindow = SDL_CreateWindow("Cave",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_OPENGL);
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

	textureBackground = loadTexture(nameBackground);
	textureShip = loadTexture(nameShip);
	textureBox = loadTexture(nameBox);

    // Check that the gWindow was successfully created
    if (gWindow == NULL) {
        // In the case that the gWindow could not be made...
        printf("Could not create gWindow: %s\n", SDL_GetError());
        return 1;
    }
    Mix_Music *music = Mix_LoadMUS(nameMusic);
 
		next_time = SDL_GetTicks() + TICK_INTERVAL;

	   Mix_PlayMusic(music, 1);

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

		//Render background
		SDL_RenderCopy(gRenderer, textureBackground, NULL, NULL);
		//Set rendering space and render to screen
		int x = 30;
		int y = 40;
		int mWidth = 64;
		int mHeight = 64;

    	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
		//Render ship to screen
	    SDL_RenderCopyEx( gRenderer, textureShip, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE );

	      //SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
	        SDL_RenderPresent(gRenderer);
					SDL_Delay(time_left());
	        next_time += TICK_INTERVAL;
		
		angle = angle + 1;
		if (angle > 360.0) {
			angle = angle - 360.0;
		}
	}

		// Destroy texture
		SDL_DestroyTexture(textureBackground);
		textureBackground = NULL;
		SDL_DestroyTexture(textureShip);
		textureShip = NULL;
		SDL_DestroyTexture(textureBox);
		textureBox = NULL;

    // Close and destroy the gWindow
    SDL_DestroyWindow(gWindow);

    // Clean up
    SDL_Quit();

	return EXIT_SUCCESS;
}
