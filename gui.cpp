// SDL-based graphical plotter application that plots an expression.
// William Immendorf - 2016

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "varequation.hpp"

const int screen_width = 800;
const int screen_height = 600;

const int x_scale = 20;
const int y_scale = 20;

SDL_Window* window = nullptr;
SDL_GLContext gl_context;

// Initialize SDL
bool init();

// Initalize GL subsystem
bool initGL();

// Render grid to screen
void renderGrid();

// Render line, given a VariableEquation
void renderLine(EquParser::VariableEquation equation);

// Close SDL and free memory
void close();

bool init()
{
	bool success = true;

	// Attempt to initialize SDL, log error on failure
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Oops, something happened with SDL
		std::cerr << "Cannot initalize SDL. Reason: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		// Use OpenGL 2.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

		// We've made it this far, so let's create the main window
		window = SDL_CreateWindow("Graphic Plotter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			// No window, so log the reason why and get out of here
			std::cerr << "Cannot create window. Reason: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Now create the OpenGL context
			gl_context = SDL_GL_CreateContext(window);
			if (gl_context == nullptr)
			{
				std::cerr << "Unable to initalize OpenGL context! Reason: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				// Enable Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					std::clog << "Warning: Vsync not enabled. Reason: " << SDL_GetError() << std::endl;
				}

				// Now actually initialize GL
				if (!initGL())
				{
					success = false;
				}
			}
		}
	}
	return success;
}

bool initGL()
{
	// Set up orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, screen_width, 0.0, screen_height, 1.0, -1.0);

	// Set up modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set clear color to pure white
	glClearColor(1.f, 1.f, 1.f, 1.f);

	// Check for any errors
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot initalize OpenGL. Reason: " << gluErrorString(error);
		return false;
	}

	return true;
}

void renderGrid()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Reset and select modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move created objects to center of screen
	glTranslatef(screen_width / 2.f, screen_height / 2.f, 0.f);
	
	// Set drawing color
	glColor3f(0.f, 0.f, 0.f);

	// Render origin lines
	glLineWidth(4);
	glBegin(GL_LINES);
		glVertex2f(0, -(screen_height / 2.f));
		glVertex2f(0, (screen_height / 2.f));
		glVertex2f(-(screen_width / 2.f), 0);
		glVertex2f((screen_width / 2.f), 0);
	glEnd();

	// Render guide points
	glPointSize(3);
	int y_start = -(screen_height / 2) + (screen_height / y_scale);
	int x_start = -(screen_width / 2) + (screen_width / x_scale);
	glBegin(GL_POINTS);
		for (int y = y_start; y < (screen_height / 2); y += (screen_height / y_scale))
		{
			for (int x = x_start; x < (screen_width / 2); x += (screen_width / x_scale))
				glVertex2f(x, y);
		}
	glEnd();
}

void renderLine(EquParser::VariableEquation equation)
{
	int pixels_to_x = (screen_width / x_scale); 

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
		for (int x = -(x_scale / 2); x <= (x_scale / 2); ++x)
		{
			for (int offset = x * pixels_to_x; offset < (pixels_to_x * (x + 1)); offset++)
			{
				equation.x(x + (offset / (double) (pixels_to_x)));
				glVertex2f(-(screen_width / 2) + (x * pixels_to_x) + offset, (float) (equation.evaluate() * (screen_height / y_scale) - (screen_height / 2)));
			}
		}
	glEnd();
}

void close()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int main(int argc, char* argv[])
{
	std::string expression;
	using EquParser::VariableEquation;

	std::cout << "Enter an expression: ";
	std::getline(std::cin, expression);
	VariableEquation equation(expression);
	std::cout << equation << std::endl;

	if (init())
	{
	  std::cout << "Plotting graphical equation, hit ESC or close window to continue" << std::endl;
		bool quit = false;

		SDL_Event e;

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					quit = true;
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
				}
			}
			renderGrid();
			renderLine(equation);
			SDL_GL_SwapWindow(window);
		}
	}
	
	close();
}
