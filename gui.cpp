// SDL-based graphical plotter application that plots an expression.
// William Immendorf - 2016

#include <iostream>
#include <string>
#include <SDL.h>

#include "equation.hpp"

const int int_screen_width = 800
const int int_screen_height = 600

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool init();

void close();


bool init()
{
	bool success = true;

	// Attempt to initialize SDL, log error on failure
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Oops, something happened with SDL
		std::cout << "Cannot initalize SDL. Reason: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		// We've made it this far, so let's create the main window
		window = SDL_CreateWindow("Graphic Plotter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			// No window, so log the reason why and get out of here
			std::cout << "Cannot create window. Reason: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Now create the window's renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr)
			{
				std::cout << "Cannot create renderer. Reason: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				// Set the rendering color to opaque plain white.
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
			}
		}
	}
	return success;
}

