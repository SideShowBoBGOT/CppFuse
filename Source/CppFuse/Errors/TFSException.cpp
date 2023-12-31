#include <CppFuse/Errors/TFSException.hpp>
#include <magic_enum.hpp>

namespace cppfuse {

cppfuse::TFSException::TFSException(fs::path::iterator begin, fs::path::iterator end, NFSExceptionType type)
    : m_xType{type} {

    auto path = std::filesystem::path();
    for(auto it = begin; it != end; ++it) path.append(it->c_str());
    UpdateMessage(path.c_str(), type);
}
const char* TFSException::what() const noexcept { return m_sMessage.c_str(); }
NFSExceptionType TFSException::Type() const { return m_xType; }

TFSException::TFSException(const fs::path& path, NFSExceptionType type) {
    UpdateMessage(path.c_str(), type);
}

TFSException::TFSException(const std::string_view& path, NFSExceptionType type) {
    UpdateMessage(path, type);
}

void TFSException::UpdateMessage(const std::string_view& path, NFSExceptionType type) {
    m_sMessage = static_cast<std::string>(magic_enum::enum_name(type)) + ": " + path.data();
}

}



