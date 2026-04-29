cmake_minimum_required (VERSION 3.23)

add_executable (TemplateMethod
	"src/main.cpp"
	"src/template_method.h"
)

set_property(TARGET TemplateMethod PROPERTY CXX_STANDARD 23)
