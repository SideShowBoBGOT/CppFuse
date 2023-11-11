#ifndef CPPFUSE_TFINDPATHEXCEPTION_HPP
#define CPPFUSE_TFINDPATHEXCEPTION_HPP

#include <CppFuse/Errors/NNFSExceptionType.hpp>

#include <exception>
#include <filesystem>

namespace cppfuse {

namespace fs = std::filesystem;

class TFSException : public std::exception {
    public:
    TFSException(fs::path::iterator begin, fs::path::iterator end, NFSExceptionType type);

    TFSException(const fs::path& path, NFSExceptionType type);
    virtual const char* what() const noexcept override;
    [[nodiscard]] NFSExceptionType Type() const;

    protected:
    void UpdateMessage(const fs::path& path, NFSExceptionType type);

    protected:
    NFSExceptionType m_xType = NFSExceptionType::NotDirectory;
    std::string m_sMessage;
};

}

#endif //CPPFUSE_TFINDPATHEXCEPTION_HPP
