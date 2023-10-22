#include <gsl/gsl>
#include <memory>

int main() {
    gsl::not_null<std::shared_ptr<int>> i = std::make_shared<int>(1);

    return 0;
}
