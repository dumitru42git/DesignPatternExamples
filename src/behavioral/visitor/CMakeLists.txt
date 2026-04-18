cmake_minimum_required (VERSION 3.23)

add_executable (Visitor "src/main.cpp" "src/node.h" "src/operand.h" "src/operator.h" "src/operators/binary_plus.h" "src/operators/unary_minus.h")
set_property(TARGET Visitor PROPERTY CXX_STANDARD 23)
