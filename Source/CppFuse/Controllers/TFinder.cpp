#include <CppFuse/Controllers/TFinder.hpp>
#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>
#include <algorithm>
#include <array>

//#include <iostream>

namespace cppfuse {

static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

ASharedFileVariant TFinder::Find(const AStdPath& path) {
    return RecursiveFindStepOne(path, path.begin(), TFileSystem::RootDir());
}

ASharedFileVariant TFinder::RecursiveFindStepOne(const AStdPath& path, AStdPathIt it, const ASharedRwLock<TDirectory>& dir) {
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

ASharedFileVariant TFinder::RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedRwLock<TDirectory>& obj) {
    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    return RecursiveFindStepOne(path, ++it, obj);
}

ASharedFileVariant TFinder::RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedFileVariant& obj) {
    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    if(const auto dir = std::get_if<ASharedRwLock<TDirectory>>(&obj)) {
        return RecursiveFindStepOne(path, ++it, *dir);
    }
   throw TFSException(path.begin(), it, NFSExceptionType::NotDirectory);
}

ASharedRwLock<TDirectory> TFinder::FindDir(const AStdPath& path) {
    return FindGeneral<TDirectory, NFSExceptionType::NotDirectory>(path);
}

ASharedRwLock<TLink> TFinder::FindLink(const std::filesystem::path& path) {
    return FindGeneral<TLink, NFSExceptionType::NotLink>(path);
}

ASharedRwLock<TFile> TFinder::FindFile(const std::filesystem::path& path) {
    return FindGeneral<TFile, NFSExceptionType::NotFile>(path);
}

}