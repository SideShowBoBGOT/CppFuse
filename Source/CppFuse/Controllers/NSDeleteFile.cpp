#include <CppFuse/Controllers/NSDeleteFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include <algorithm>

namespace cppfuse::NSDeleteFile {

void DeleteChildrenInDirectory(const ASharedRwLock<TDirectory>& dir, const fs::path& dirPath);

static void DeleteWithIterator( std::vector<ASharedFileVariant>& parentFiles,
                                std::vector<ASharedFileVariant>::iterator it, const fs::path& itPath) {

    if(const auto childDirPtr = std::get_if<ASharedRwLock<TDirectory>>(&*it)) {
        DeleteChildrenInDirectory(*childDirPtr, itPath);
    }
    NSFindFile::RemoveFromNameHash(itPath);
    parentFiles.erase(it);
}

void DeleteChildrenInDirectory(const ASharedRwLock<TDirectory>& dir, const fs::path& dirPath) {
    auto dirWrite = dir->Write();
    auto& files = dirWrite->Files;
    for(auto i = unsigned(0); i < files.size(); ++i) {
        const auto it = files.begin() + i;
        DeleteWithIterator(files, it, dirPath / TGetInfoName{}(*it));
        --i;
    }
}

void Delete(const fs::path& path) {
    const auto fileName = path.filename();
    const auto parentDir = NSFindFile::FindDir(path.parent_path());
    auto parentDirWrite = parentDir->Write();
    auto& parentFiles = parentDirWrite->Files;
    const auto it = std::find_if(parentFiles.begin(), parentFiles.end(),
        [&fileName](const auto& f) {
            return TGetInfoName{}(f) == fileName;
        }
    );
    if(it == parentFiles.end()) {
        throw TFSException(path, NFSExceptionType::FileNotExist);
    }
    DeleteWithIterator(parentFiles, it, path);
}

}
