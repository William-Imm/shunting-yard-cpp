// SDL-based graphical plotter application that plots an expression.
// William Immendorf - 2016

#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "color.hpp"
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

// Initalize renderer (required before running other rendering functions)
void renderInit();

// Render grid to screen
void renderGrid();

// Render line, given a VariableEquation
void renderLine(EquParser::VariableEquation & equation);

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
		std::cerr << "Cannot initalize OpenGL!" << std::endl;
		return false;
	}

	return true;
}

void renderInit()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Reset and select modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move created objects to center of screen
	glTranslatef(screen_width / 2.f, screen_height / 2.f, 0.f);
}

void renderGrid()
{
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

void renderLine(EquParser::VariableEquation & equation, const EquParser::Color color)
{
	// Set drawing color
	glColor3f(color.red, color.green, color.blue);

	int pixels_to_x = (screen_width / x_scale);

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
		for (int x = -(x_scale / 2); x <= (x_scale / 2); ++x)
		{
			for (int offset = x * pixels_to_x; offset < (pixels_to_x * (x + 2)); ++offset)
			{
				equation.x(x + offset / (double) pixels_to_x);
				glVertex2d((x * pixels_to_x) + offset, equation.evaluate() * (screen_height / (double) y_scale));
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
	using std::cout;
	using std::cin;
	using std::endl;
	using EquParser::VariableEquation;
	using EquParser::Color;

	// Grab the number of equations to plot
	int equation_count = 0;
	bool num_equations_selected = false;
	cout << "Enter how many equations to plot (0 to exit): ";
	while (!num_equations_selected)
	{
		cin >> equation_count;
		if (!cin || equation_count < 0) // check for invalid input and negative number of equations
		{
			cin.clear();
			cout << "Invalid response, enter how many equations to plot (0 to exit): ";
		}
		else if (equation_count == 0)
			std::exit(EXIT_SUCCESS);
		else
			num_equations_selected = true;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// For each equation, assign an expression and color
	std::vector<std::pair<VariableEquation, Color>> equation_color_vector;
	int num_colors = sizeof(EquParser::Colors) / sizeof(*EquParser::Colors);
	for (int i = 0; i < equation_count; ++i)
	{
		// Grab an expression and create a variable equation from it
		std::string expression;
		cout << "Enter an expression: ";
		getline(cin, expression);
		VariableEquation equation(expression);
		// List avaiable color presets, and select from user input
		cout << "Avaliable colors:" << endl;
		for (int j = 0; j < num_colors; j++)
			cout << EquParser::Colors[j].name << " (" << j << ")" << endl;
		bool color_selected = false;
		cout << "Select a color: ";
		while (!color_selected)
		{
			int color_select = 0;
			cin >> color_select;
			if (!cin || color_select < 0 || color_select > (num_colors - 1)) // check for invalid input and out of bounds color selection
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Invalid response, select a color: ";
			}
			else
			{
				equation_color_vector.push_back({equation, EquParser::Colors[color_select]});
				color_selected = true;
			}
		}
		cout << equation << endl;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// Now actually plot the equations
	if (init())
	{
		cout << "Plotting graphical equation(s), hit ESC or close window to continue" << endl;
		bool running = true;

		SDL_Event e;

		while (running)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					running = false;
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
						running = false;
				}
			}
			renderInit();
			renderGrid();
			for (auto equation_color : equation_color_vector)
				renderLine(equation_color.first, equation_color.second);
			SDL_GL_SwapWindow(window);
		}
	}

	close();
}
