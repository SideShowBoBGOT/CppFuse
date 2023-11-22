#include <CppFuse/Views/TFileSystemClientCLI.hpp>

namespace cppfuse {

static constexpr unsigned long s_uBufferSize = 1000;

TFileSystemClientCLI::TFileSystemClientCLI() : CLI::App("FindByName") {
    add_option("--pipe-point,-p", m_xPipePath, "Pipe point")
        ->required(true)->check(CLI::ExistingFile);
    add_option("--file-name,-f", m_sFileName, "File name")
        ->required(true);
    parse_complete_callback([this]() { Process(); });
}

void TFileSystemClientCLI::Process() const {
    auto buffer = std::array<char, s_uBufferSize>();
    TFileSystemClientCLI::FindByName(m_xPipePath, m_sFileName, buffer);
    std::cout << buffer.data();
}

}


