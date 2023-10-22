#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> i = std::make_shared<int>(1);

    return 0;
}
