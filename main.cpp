#include <CppFuse/Views/TFileSystemCLI.hpp>

int main(int argc, char *argv[]) {
    auto cli = cppfuse::TFileSystemCLI("CppFuse");
    CLI11_PARSE(cli, argc, argv);
    return 0;
}