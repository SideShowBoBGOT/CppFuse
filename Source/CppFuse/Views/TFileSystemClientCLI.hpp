#ifndef CPPFUSE_TFILESYSTEMCLIENTCLI_HPP
#define CPPFUSE_TFILESYSTEMCLIENTCLI_HPP

#include <CLI/CLI.hpp>

namespace fs = std::filesystem;

namespace cppfuse {

class TFileSystemClientCLI : public CLI::App {
    public:
    TFileSystemClientCLI();

    public:
    template<unsigned long BufferSize>
    static void FindByName(const fs::path& pipePath, const std::string& fileName, std::array<char, BufferSize>& buffer) {
        {
            auto fOut = std::ofstream(pipePath);
            if(!fOut.is_open()) {
                throw std::invalid_argument(s_sError.data());
            }
            fOut << fileName;
        }
        {
            auto fIn = std::ifstream(pipePath);
            if(!fIn.is_open()) {
                throw std::invalid_argument(s_sError.data());
            }
            fIn.read(buffer.data(), buffer.size());
        }
    }

    protected:
    void Process() const;

    protected:
    fs::path m_xPipePath;
    std::string m_sFileName;
    static constexpr std::string_view s_sError = "Can not open the pipe for writing";
};

}

#endif //CPPFUSE_TFILESYSTEMCLIENTCLI_HPP
