#include <CppFuse/Views/TFileSystemCLI.hpp>

int main(int argc, char *argv[]) {
    auto cli = cppfuse::TFileSystemCLI();
    CLI11_PARSE(cli, argc, argv);
    return 0;
}