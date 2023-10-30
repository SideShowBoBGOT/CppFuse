#include <CppFuse/Errors/TFSException.hpp>
#include <magic_enum.hpp>

namespace cppfuse {

cppfuse::TFSException::TFSException(TStdPathIt begin, TStdPathIt end,
    NFSExceptionType type) : m_xType{type} {
    auto path = std::filesystem::path();
    for(auto it = begin; it != end; ++it) path.append(it->c_str());
    m_sMessage = static_cast<std::string>(magic_enum::enum_name(type)) + ": " + path.c_str();
}
const char* TFSException::what() const noexcept { return m_sMessage.c_str(); }
NFSExceptionType TFSException::Type() const { return m_xType; }

}



