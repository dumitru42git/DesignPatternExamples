#include "class.h"
#include "proxy.h"

#include <print>

#include <expected>

void call(Class& object, const int clientData)
{
    std::expected<int, ReturnError> data = object.getData(clientData);
    if (data.has_value())
        std::println("{}::getData({}) -> {}", object.className(), clientData, data.value());
    else
        std::println("{}::getData({}) -> {}", object.className(), clientData, ReturnErrorToStringView(data.error()));
}

int main()
{
    std::println("---Proxy Pattern---");

    std::unique_ptr<Class> objectUnsecure = std::make_unique<ClassUnsecure>(42);
    std::unique_ptr<Class> proxyObj       = std::make_unique<ProxySecure>( //
        *objectUnsecure,
        [](int clientData) { return clientData > 1000; } //
    );

    call(*proxyObj, 1);
    call(*proxyObj, 1001);
    call(*proxyObj, 1);
    call(*proxyObj, 1);
    call(*proxyObj, 1);
    call(*proxyObj, 1001);
    call(*objectUnsecure, 1);

    return 0;
}
