cmake_minimum_required (VERSION 3.23)

add_executable (Observer
	"src/main.cpp"
	"src/subject.cpp"
	"src/subject.h"
	"src/subject.inl"
	"src/observer.cpp"
	"src/observer.h"
	"src/subjects/subject_print.cpp"
	"src/subjects/subject_print.h"
	"src/subjects/subject_string.cpp"
	"src/subjects/subject_string.h"
	"src/subjects/subject_value.cpp"
	"src/subjects/subject_value.h"
	"src/observers/observer_sum.h"
	"src/observers/observer_sum.cpp"
	"src/observers/observer_append.cpp"
	"src/observers/observer_append.h"
)

set_property(TARGET Observer PROPERTY CXX_STANDARD 23)
