#include "TReadDirectory.hpp"
#include "TGetFileParameter.hpp"
#include <CppFuse/Errors/TFSException.hpp>
#include "TFindFile.hpp"

namespace cppfuse {

TReadDirectory::TReadDirectory(const fs::path& path, void* buffer, fuse_fill_dir_t filler)
    : m_pPath{path}, m_pBuffer{buffer}, m_xFiller{filler} {}

void TReadDirectory::operator()() {
    const auto res = TFindFile::Find(m_pPath);
    return std::visit([this](const auto& obj) { return DoReadDir(obj); }, res);
}

void TReadDirectory::DoReadDir(const ASharedRwLock<TDirectory>& var) {
    FillerDirectory(var);
}

void TReadDirectory::DoReadDir(const ASharedRwLock<TRegularFile>& var) {
    throw TFSException(m_pPath, NFSExceptionType::NotDirectory);
}

void TReadDirectory::DoReadDir(const ASharedRwLock<TLink>& var) {
    const auto varRead = var->Read();
    const auto dir = TFindFile::FindDir(varRead->LinkTo);
    FillerDirectory(dir);
}

void TReadDirectory::FillerBuffer(const std::string_view& name) {
    m_xFiller(m_pBuffer, name.data(), NULL, 0, fuse_fill_dir_flags::FUSE_FILL_DIR_PLUS);
}

void TReadDirectory::FillerDirectory(const ASharedRwLock<TDirectory>& dir) {
    const auto dirRead = dir->Read();
    for(const auto& var : dirRead->Objects) {
        const auto name = TGetInfoName{}(var);
        FillerBuffer(name);
    }
}

}