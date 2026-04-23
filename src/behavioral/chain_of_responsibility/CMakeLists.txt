cmake_minimum_required (VERSION 3.23)

add_executable (ChainOfResponsibility
	"src/main.cpp"
	"src/request.h"
	"src/chain.h"
	"src/object.h"
	"src/chains/chain_print_request.h"
	"src/chains/chain_reset.h"
	"src/chains/chain_reset_to_data.h"
	"src/chains/chain_print_data.h"
)

set_property(TARGET ChainOfResponsibility PROPERTY CXX_STANDARD 23)
