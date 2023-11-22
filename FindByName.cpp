#include <CppFuse/Views/TFileSystemClientCLI.hpp>

int main(int argc, char *argv[]) {
    auto cli = cppfuse::TFileSystemClientCLI("FindByName");
    CLI11_PARSE(cli, argc, argv);
    return 0;
}