cmake_minimum_required (VERSION 3.23)

add_executable (Interpreter "src/main.cpp" "src/context.h" "src/node.h" "src/nodes/value.h" "src/context.cpp" "src/nodes/variable.h" "src/nodes/binary_plus.h" "src/nodes/binary_operation.h" "src/nodes/unary_operation.h" "src/nodes/unary_minus.h")
set_property(TARGET Interpreter PROPERTY CXX_STANDARD 23)
