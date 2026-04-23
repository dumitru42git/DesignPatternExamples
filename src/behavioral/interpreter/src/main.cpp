#include "context.h"
#include "node.h"
#include "nodes/binary_div.h"
#include "nodes/binary_plus.h"
#include "nodes/unary_minus.h"
#include "nodes/value.h"
#include "nodes/variable.h"

int main()
{
    std::println("---Interpreter Pattern---");

    Context ctx;
    ctx.set("a", Value(5));

    // node1
    std::unique_ptr<Node> node1   = std::make_unique<BinaryPlus>( //
        std::make_unique<Variable>("a"),
        std::make_unique<Value>(5) //
    );
    std::unique_ptr<Node> result1 = node1->evaluate(ctx);
    std::print("Expression:"), node1->print();
    std::print("Solution:  "), result1->print();
    std::println();

    // node2
    std::unique_ptr<Node> node2   = std::make_unique<BinaryPlus>( //
        std::make_unique<Variable>("b"),
        std::make_unique<Value>(5) //
    );
    std::unique_ptr<Node> result2 = node2->evaluate(ctx);
    std::print("Expression:"), node2->print();
    std::print("Solution:  "), result2->print();
    std::println();

    // node3
    std::unique_ptr<Node> node3   = std::make_unique<BinaryPlus>( //
        std::make_unique<BinaryPlus>(std::move(node1), std::move(result1)),
        std::make_unique<UnaryMinus>(std::move(result2)) //
    );
    std::unique_ptr<Node> result3 = node3->evaluate(ctx);
    std::print("Expression:"), node3->print();
    std::print("Solution:  "), result3->print();
    std::println();

    // node3
    std::print("Expression:"), result3->print();
    ctx.set("b", Value(15));
    result3 = node3->evaluate(ctx);
    std::print("Solution:  "), result3->print();
    std::println();

    // node4
    ctx.set("c", Value(5));
    ctx.set("d", Value(2.2));
    std::unique_ptr<Node> node4 = std::make_unique<BinaryPlus>( //
        std::make_unique<BinaryDiv>(                            //
            std::make_unique<Variable>("c"),
            std::make_unique<Value>(2)),
        std::make_unique<Variable>("d") //
    );
    std::unique_ptr<Node> result4 = node4->evaluate(ctx);
    std::print("Expression:"), node4->print();
    std::print("Solution:  "), result4->print();
    std::println();

    return 0;
}
