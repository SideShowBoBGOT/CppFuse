#ifndef CPPFUSE_TFINDPATHEXCEPTION_HPP
#define CPPFUSE_TFINDPATHEXCEPTION_HPP

#include <CppFuse/Errors/NNFSExceptionType.hpp>

#include <exception>
#include <filesystem>

namespace cppfuse {

using AStdPath = std::filesystem::path;
using AStdPathIt = std::filesystem::path::iterator;

class TFSException : public std::exception {
    public:
    TFSException(AStdPathIt begin, AStdPathIt end, NFSExceptionType type);
    TFSException(const char* path, NFSExceptionType type);
    virtual const char* what() const noexcept override;
    [[nodiscard]] NFSExceptionType Type() const;

    protected:
    void UpdateMessage(const char* path, NFSExceptionType type);

    protected:
    NFSExceptionType m_xType = NFSExceptionType::NotDirectory;
    std::string m_sMessage;
};

}

#endif //CPPFUSE_TFINDPATHEXCEPTION_HPP
