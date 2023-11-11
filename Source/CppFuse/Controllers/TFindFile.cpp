#include <CppFuse/Controllers/TFindFile.hpp>
#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Errors/TFSException.hpp>
#include "TGetFileParameter.hpp"
#include <algorithm>
#include <array>

namespace cppfuse {

static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

template<typename T, auto FSExceptionValue>
ASharedRwLock<T> FindGeneral(const std::filesystem::path& path) {
    const auto obj = TFindFile::Find(path);
    if(const auto t = std::get_if<ASharedRwLock<T>>(&obj)) {
        return *t;
    }
    throw TFSException(path.begin(), path.end(), FSExceptionValue);
}

ASharedFileVariant TFindFile::Find(const std::filesystem::path& path) {
    return RecursiveFindStepOne(path, path.begin(), TFileSystem::RootDir());
}

ASharedRwLock<TDirectory> TFindFile::FindDir(const std::filesystem::path& path) {
    return FindGeneral<TDirectory, NFSExceptionType::NotDirectory>(path);
}

ASharedRwLock<TLink> TFindFile::FindLink(const std::filesystem::path& path) {
    return FindGeneral<TLink, NFSExceptionType::NotLink>(path);
}

ASharedRwLock<TRegularFile> TFindFile::FindFile(const std::filesystem::path& path) {
    return FindGeneral<TRegularFile, NFSExceptionType::NotFile>(path);
}

ASharedFileVariant TFindFile::RecursiveFindStepOne(const std::filesystem::path& path,
    std::filesystem::path::iterator it, const ASharedRwLock<TDirectory>& dir) {

    const auto dirRead = dir->Read();
    const auto itName = std::string_view(it->c_str());
    const auto ownName = std::string_view(TGetInfoName{}(dirRead));
    if(itName == s_sSelfName or itName == ownName) {
        return RecursiveFindStepTwo(path, it, dir);
    }
    if(itName == s_sParentName) {
        if(const auto parent = TGetInfoParent{}(dirRead).lock()) {
            return RecursiveFindStepTwo(path, it, parent);
        }
        throw TFSException(path.begin(), it, NFSExceptionType::FileNotExist);
    }
    const auto& fileObjects = dirRead->Objects;
    const auto childIt = std::ranges::find_if(fileObjects,
        [&itName](const auto& f) {
            return std::visit(TGetInfoName{}, f) == itName;
        });
    if(childIt == fileObjects.end()) {
        throw TFSException(path.begin(), it, NFSExceptionType::FileNotExist);
    }
    return RecursiveFindStepTwo(path, it, *childIt);
}

ASharedFileVariant TFindFile::RecursiveFindStepTwo(const std::filesystem::path& path,
    std::filesystem::path::iterator it, const ASharedRwLock<TDirectory>& obj) {

    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    return RecursiveFindStepOne(path, ++it, obj);
}

ASharedFileVariant TFindFile::RecursiveFindStepTwo(const std::filesystem::path& path,
    std::filesystem::path::iterator it, const ASharedFileVariant& obj) {

    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    if(const auto dir = std::get_if<ASharedRwLock<TDirectory>>(&obj)) {
        return RecursiveFindStepOne(path, ++it, *dir);
    }
   throw TFSException(path.begin(), it, NFSExceptionType::NotDirectory);
}

}