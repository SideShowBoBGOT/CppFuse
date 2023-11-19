#ifndef CPPFUSE_TFILESYSTEMCLI_HPP
#define CPPFUSE_TFILESYSTEMCLI_HPP

#include <CLI/CLI.hpp>

namespace cppfuse {

class TFileSystemCLI : public CLI::App {
    public:
    TFileSystemCLI(const std::string& name);
};

}

#endif //CPPFUSE_TFILESYSTEMCLI_HPP
