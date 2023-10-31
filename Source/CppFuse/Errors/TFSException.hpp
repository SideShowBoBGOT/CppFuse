#ifndef CPPFUSE_TFINDPATHEXCEPTION_HPP
#define CPPFUSE_TFINDPATHEXCEPTION_HPP

#include <CppFuse/Errors/NNFSExceptionType.hpp>

#include <exception>
#include <filesystem>
#include <expected>

namespace cppfuse {

class TFSException;

template<typename ReturnType>
using AFSExpected = std::expected<ReturnType, TFSException>;

using AStdPath = std::filesystem::path;
using AStdPathIt = std::filesystem::path::iterator;

class TFSException : public std::exception {
    public:
    TFSException(AStdPathIt begin, AStdPathIt end, NFSExceptionType type);
    virtual const char* what() const noexcept override;
    [[nodiscard]] virtual NFSExceptionType Type() const;

    protected:
    NFSExceptionType m_xType = NFSExceptionType::NotDirectory;
    std::string m_sMessage;
};

}

#endif //CPPFUSE_TFINDPATHEXCEPTION_HPP
