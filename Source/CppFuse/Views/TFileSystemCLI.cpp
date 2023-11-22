#include <CppFuse/Views/TFileSystemCLI.hpp>
#include <CppFuse/Controllers/TFileSystem.hpp>

namespace cppfuse {

TFileSystemCLI::TFileSystemCLI() : CLI::App("CppFuse") {
    const auto fg = add_flag("--foreground-process,-f", "Keep as foreground process");
    add_flag("--no-threads,-n", "Disable multiple threads support");
    add_flag("--debug,-d", "Show debug messages")->needs(fg);
    add_option("--mount-point,-m", "Mount point")
        ->required(true)->check(CLI::ExistingDirectory);
    add_option("--pipe-point,-p", TFileSystem::FifoPath, "Pipe point")
        ->required(true)->check(CLI::ExistingFile);
    parse_complete_callback([this]() {
        std::vector<const char*> args = {fs::current_path().c_str()};
        if(get_option("--foreground-process")->as<bool>()) {
            args.push_back("-f");
        }
        if(get_option("--debug")->as<bool>()) {
            args.push_back("-d");
        }
        if(get_option("--no-threads")->as<bool>()) {
            args.push_back("-s");
        }
        args.push_back(get_option("--mount-point")->as<fs::path>().c_str());
        cppfuse::TFileSystem::Init(static_cast<int>(args.size()), const_cast<char**>(args.data()));
    });
}

}
