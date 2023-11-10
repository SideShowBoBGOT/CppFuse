#include <CppFuse/Errors/TFSException.hpp>
#include <magic_enum.hpp>

namespace cppfuse {

cppfuse::TFSException::TFSException(AStdPathIt begin, AStdPathIt end,
    NFSExceptionType type) : m_xType{type} {
    auto path = std::filesystem::path();
    for(auto it = begin; it != end; ++it) path.append(it->c_str());
    UpdateMessage(path.c_str(), type);
}
const char* TFSException::what() const noexcept { return m_sMessage.c_str(); }
NFSExceptionType TFSException::Type() const { return m_xType; }

TFSException::TFSException(const char* path, NFSExceptionType type) {
    UpdateMessage(path, type);
}

void TFSException::UpdateMessage(const char* path, NFSExceptionType type) {
    m_sMessage = static_cast<std::string>(magic_enum::enum_name(type)) + ": " + path;
}

}



