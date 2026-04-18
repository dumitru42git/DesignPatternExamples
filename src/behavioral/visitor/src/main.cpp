#include "node.h"
#include "operand.h"
#include "operator.h"
#include "operators/binary_plus.h"
#include "operators/unary_minus.h"

int main()
{
    std::println("---Visitor Pattern---");

    std::unique_ptr<Node> sum1 = std::make_unique<BinaryPlusOperator>(std::make_unique<Value<int>>(3), //
                                                                      std::make_unique<Value<int>>(7));
    sum1->execute()->print();

    std::unique_ptr<Node> sum2 = std::make_unique<BinaryPlusOperator>(std::make_unique<Value<double>>(3.9), //
                                                                      std::make_unique<Value<int>>(6));
    sum2->execute()->print();

    std::unique_ptr<Node> negSum2 = std::make_unique<UnaryMinusOperator>(std::move(sum2));
    negSum2->execute()->print();

    std::unique_ptr<Node> finalSum = std::make_unique<BinaryPlusOperator>(std::move(negSum2), //
                                                                          std::move(sum1));
    finalSum->execute()->print();

    return 0;
}
