#ifndef CPPFUSE_TGETINFOTYPE_HPP
#define CPPFUSE_TGETINFOTYPE_HPP

#include <CppFuse/Models/Objects/NNFileType.hpp>
#include <CppFuse/Models/Objects/TFileObjects.hpp>

namespace cppfuse {

class TGetInfoType {
    public:
    constexpr TGetInfoType()=default;

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

#endif //CPPFUSE_TGETINFOTYPE_HPP
