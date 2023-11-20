#ifndef CPPFUSE_TFINDPATHEXCEPTION_HPP
#define CPPFUSE_TFINDPATHEXCEPTION_HPP

#include <CppFuse/Errors/NNFSExceptionType.hpp>

#include <exception>
#include <filesystem>

namespace fs = std::filesystem;

namespace cppfuse {

class TFSException : public std::exception {
    public:
    TFSException(fs::path::iterator begin, fs::path::iterator end, NFSExceptionType type);
    TFSException(const fs::path& path, NFSExceptionType type);
    TFSException(const std::string_view& path, NFSExceptionType type);
    virtual const char* what() const noexcept override;
    [[nodiscard]] NFSExceptionType Type() const;

    protected:
    void UpdateMessage(const std::string_view& path, NFSExceptionType type);

    protected:
    NFSExceptionType m_xType = NFSExceptionType::NotDirectory;
    std::string m_sMessage;
};

}

#endif //CPPFUSE_TFINDPATHEXCEPTION_HPP
