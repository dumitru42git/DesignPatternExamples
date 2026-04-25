cmake_minimum_required (VERSION 3.23)

add_executable (Memento
	"src/main.cpp"
	"src/private/implementation.cpp"
	"src/private/implementation.h"
	"src/public/implementation.cpp"
	"src/public/implementation.h"
	"src/public/interface.cpp"
	"src/public/interface.h"
)

set_property(TARGET Memento PROPERTY CXX_STANDARD 23)
