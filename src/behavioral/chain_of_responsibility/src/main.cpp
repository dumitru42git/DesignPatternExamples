#include "chain.h"
#include "chains/chain_print_data.h"
#include "chains/chain_print_request.h"
#include "chains/chain_reset.h"
#include "chains/chain_reset_to_data.h"
#include "request.h"

#include <memory>
#include <print>

int main()
{
    std::println("---Chain Of Responsibility Pattern---");
    std::println();

    Object object(42);
    object.print();
    std::println();

    Request resetRequest{.data = 1, .type = Request::RESET};
    Request printRequest{.data = 21, .type = Request::PRINT};

    {
        std::println("Chain <- ChainResetToData <- ChainPrintRequest");
        std::unique_ptr<Chain> chainResetToData  = std::make_unique<ChainResetToData>(nullptr, object);
        std::unique_ptr<Chain> chainPrintRequest = std::make_unique<ChainPrintRequest>(chainResetToData.get());
        Chain*                 chainEntry        = chainPrintRequest.get();

        chainEntry->handle(resetRequest);
        chainEntry->handle(printRequest);
        std::println();
    }
    {
        std::println("Chain <- ChainReset <- ChainPrintData");
        std::unique_ptr<Chain> chainReset     = std::make_unique<ChainReset>(nullptr, object);
        std::unique_ptr<Chain> chainPrintData = std::make_unique<ChainPrintData>(chainReset.get(), object);
        Chain*                 chainEntry     = chainPrintData.get();

        chainEntry->handle(printRequest);
        chainEntry->handle(resetRequest);
        chainEntry->handle(printRequest);
        std::println();
    }
    {
        std::println("Chain <- ChainPrintRequest");
        std::unique_ptr<Chain> chainReset = std::make_unique<ChainPrintRequest>(nullptr);
        Chain*                 chainEntry = chainReset.get();

        chainEntry->handle(resetRequest);
        std::println();
    }

    return 0;
}
