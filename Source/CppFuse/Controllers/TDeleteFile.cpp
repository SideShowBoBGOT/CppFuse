#include <CppFuse/Controllers/TDeleteFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>
#include <CppFuse/Controllers/TFindFile.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include <algorithm>

namespace cppfuse {

void TDeleteFile::operator()(const fs::path& path) {
    const auto fileName = path.filename();
    const auto parentDir = TFindFile::FindDir(path.parent_path());
    auto parentDirWrite = parentDir->Write();
    auto& files = parentDirWrite->Files;
    const auto it = std::find_if(files.begin(), files.end(),
        [&fileName](const auto& f) {
            return TGetInfoName{}(f) == fileName;
        }
    );
    if(it == files.end()) {
        throw TFSException(path, NFSExceptionType::FileNotExist);
    }
    if(const auto childDirPtr = std::get_if<ASharedRwLock<TDirectory>>(&*it)) {
        DeleteDir(*childDirPtr);
    }
    files.erase(it);
}

void TDeleteFile::DeleteDir(const ASharedRwLock<TDirectory>& dir) {
    auto dirWrite = dir->Write();
    auto& files = dirWrite->Files;
    for(auto i = unsigned(0); i < files.size(); ++i) {
        if(const auto childDirPtr = std::get_if<ASharedRwLock<TDirectory>>(&files[i])) {
            DeleteDir(*childDirPtr);
        }
        files.erase(files.begin() + i);
        --i;
    }
}

}
