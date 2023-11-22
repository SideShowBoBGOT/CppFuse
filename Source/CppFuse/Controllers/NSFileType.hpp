#ifndef CPPFUSE_NSFILETYPE_HPP
#define CPPFUSE_NSFILETYPE_HPP

#include <CppFuse/Models/NNFileType.hpp>
#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse::NSFileType {

constexpr NFileType Get(const ASharedFileVariant& var) {
    return std::visit([](const auto& file) { return Get(file); }, var);
}
constexpr NFileType Get(const CSharedRwFileObject auto& var) {
    return std::remove_reference_t<decltype(var)>::element_type::InnerType::FileType;
}
constexpr NFileType Get(const CGuardFileObject auto& var) {
    return std::remove_reference_t<decltype(var)>::InnerType::FileType;
}

}

#endif //CPPFUSE_NSFILETYPE_HPP
