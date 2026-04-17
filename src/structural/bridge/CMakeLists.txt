cmake_minimum_required (VERSION 3.23)

add_executable (Bridge 
	"src/main.cpp"
	"src/public/interface.cpp"
	"src/public/interface.h"
	"src/private/implementation.cpp"
	"src/private/implementation.h"
	"src/public/implementation_factory.cpp"
	"src/public/implementation_factory.h"
)

set_property(TARGET Bridge PROPERTY CXX_STANDARD 23)
