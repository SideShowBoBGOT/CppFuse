#include <CppFuse/Controllers/TFileSystem.hpp>

int main(int argc, char *argv[]) {
    return cppfuse::TFileSystem::Init(argc, argv);
}