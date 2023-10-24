#ifndef CPPFUSE_TFINDPATHEXCEPTION_HPP
#define CPPFUSE_TFINDPATHEXCEPTION_HPP

#include "NNFSExceptionType.hpp"

#include <exception>
#include <filesystem>
#include <expected>

namespace cppfuse {

class TFSException;

template<typename ReturnType>
using TFSExpected = std::expected<ReturnType, TFSException>;

class TFSException : public std::exception {
    public:
    TFSException(std::filesystem::path::iterator begin, std::filesystem::path::iterator end, NFSExceptionType type);
    virtual const char* what() const noexcept override;
    [[nodiscard]] virtual NFSExceptionType Type() const;

    protected:
    NFSExceptionType m_xType = NFSExceptionType::NotDirectory;
    std::string m_sMessage;
};

}

#endif //CPPFUSE_TFINDPATHEXCEPTION_HPP
