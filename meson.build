project('shunting yard', 'cpp', default_options: ['cpp_std=c++11'])
sdldep = dependency('sdl2')
gldep = dependency('gl')
lib = shared_library('shunting', 'equation.cpp', 'utility.cpp', 'varequation.cpp', version: '1.0.0', soversion: '1')
executable('gui', 'gui.cpp',	dependencies: [sdldep, gldep], link_with: lib)
