cmake_minimum_required (VERSION 3.23)

add_executable (State
	"src/main.cpp"
	"src/printer.cpp"
	"src/printer.h"
	"src/state.h"
	"src/state_visitor.h"
	"src/states/state_initializing.cpp"
	"src/states/state_initializing.h"
	"src/states/state_ready.cpp"
	"src/states/state_ready.h"
	"src/states/state_finished.cpp"
	"src/states/state_finished.h"
	"src/printers/variable_printer.cpp"
	"src/printers/variable_printer.h"
	"src/printers/constant_printer.cpp"
	"src/printers/constant_printer.h"
)

set_property(TARGET State PROPERTY CXX_STANDARD 23)
