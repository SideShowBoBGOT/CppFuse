#ifndef CPPFUSE_TGETFILETYPE_HPP
#define CPPFUSE_TGETFILETYPE_HPP

#include "CppFuse/Models/NNFileType.hpp"
#include "CppFuse/Models/TFileObjects.hpp"

namespace cppfuse {

class TGetFileType {
    public:
    constexpr TGetFileType()=default;

    public:
    constexpr NFileType operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }
    constexpr NFileType operator()(const CSharedRwFileObject auto& var) {
        return std::remove_reference_t<decltype(var)>::element_type::InnerType::FileType;
    }
    constexpr NFileType operator()(const CGuardFileObject auto& var) {
        return std::remove_reference_t<decltype(var)>::InnerType::FileType;
    }
};

}

#endif //CPPFUSE_TGETFILETYPE_HPP
