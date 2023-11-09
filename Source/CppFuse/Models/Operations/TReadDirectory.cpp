#include <CppFuse/Models/Operations/TReadDirectory.hpp>
#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>
#include <CppFuse/Models/Objects/SDirectory.hpp>
#include <CppFuse/Models/Objects/SLink.hpp>
#include <CppFuse/Controllers/TFinder.hpp>

namespace cppfuse {

AFSExpected<std::monostate> TReadDirectory::Do(const char* path, void* buffer, fuse_fill_dir_t filler) {
    return TReadDirectory{path, buffer, filler}();
}

TReadDirectory::TReadDirectory(const char* path, void* buffer, fuse_fill_dir_t filler)
    : m_Path{path}, m_Buffer{buffer}, m_Filler{filler} {}

AFSExpected<std::monostate> TReadDirectory::operator()() {
    const auto dirPath = std::filesystem::path(m_Path);
    const auto& result = TFinder::Find(dirPath);
    if(!result) return std::unexpected(std::move(result).error());
    return this->operator()(result.value());
}

AFSExpected<std::monostate> TReadDirectory::operator()(const ASharedFileVariant& var) { return std::visit(*this, var); }

AFSExpected<std::monostate> TReadDirectory::operator()(const ASharedRwLock<TDirectory>& var) {
    FillerDirectory(var);
    return std::monostate{};
}

AFSExpected<std::monostate> TReadDirectory::operator()(const ASharedRwLock<SFile>& var) {

}

AFSExpected<std::monostate> TReadDirectory::operator()(const ASharedRwLock<SLink>& var) {
    const auto varRead = var->Read();
    const auto dirRes = TFinder::FindDir(varRead->LinkTo);
    if(!dirRes) return std::unexpected(std::move(dirRes).error());
    FillerDirectory(dirRes.value());
    return std::monostate{};
}

void TReadDirectory::FillerBuffer(const std::string_view& name) {
    m_Filler(m_Buffer, name.data(), NULL, 0, fuse_fill_dir_flags::FUSE_FILL_DIR_PLUS);
}

void TReadDirectory::FillerDirectory(const ASharedRwLock<TDirectory>& dir) {
    const auto dirRead = dir->Read();
    for(const auto& var : dirRead->Objects) {
        const auto name = std::visit(TGetInfoName{}, var);
        FillerBuffer(name);
    }
}



}