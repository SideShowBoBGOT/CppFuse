#include <CppFuse/Controllers/TFinder.hpp>
#include <CppFuse/Controllers/TFileSystem.hpp>
#include "CppFuse/Models/Objects/SDirectory.hpp"
#include "CppFuse/Models/Objects/SLink.hpp"
#include "CppFuse/Models/Objects/SFile.hpp"
#include <algorithm>
#include <array>

namespace cppfuse {

static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

AFSExpected<ASharedFileVariant> TFinder::Find(const AStdPath& path) {
    return RecursiveFindStepOne(path, path.begin(), TFileSystem::RootDir());
}

AFSExpected<ASharedFileVariant> TFinder::RecursiveFindStepOne(const AStdPath& path, AStdPathIt it, const ASharedRwLock<SDirectory>& dir) {
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
        return MakeFSException(path.begin(), it, NFSExceptionType::FileNotExist);
    }
    const auto& fileObjects = dirRead->Objects;
    const auto childIt = std::ranges::find_if(fileObjects,
        [&itName](const auto& f) {
            return std::visit(TGetInfoName{}, f) == itName;
        });
    if(childIt == fileObjects.end()) {
        return MakeFSException(path.begin(), it, NFSExceptionType::FileNotExist);
    }
    return RecursiveFindStepTwo(path, it, *childIt);
}

AFSExpected<ASharedFileVariant> TFinder::RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedRwLock<SDirectory>& obj) {
    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    return RecursiveFindStepOne(path, ++it, obj);
}

AFSExpected<ASharedFileVariant> TFinder::RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedFileVariant& obj) {
    if(std::distance(it, path.end()) == 1) {
        return obj;
    }
    if(const auto dir = std::get_if<ASharedRwLock<SDirectory>>(&obj)) {
        return RecursiveFindStepOne(path, ++it, *dir);
    }
    return MakeFSException(path.begin(), it, NFSExceptionType::NotDirectory);
}

AFSExpected<ASharedRwLock<SDirectory>> TFinder::FindDir(const AStdPath& path) {
    return FindGeneral<SDirectory, NFSExceptionType::NotDirectory>(path);
}

AFSExpected<ASharedRwLock<SLink>> TFinder::FindLink(const std::filesystem::path& path) {
    return FindGeneral<SLink, NFSExceptionType::NotLink>(path);
}

AFSExpected<ASharedRwLock<SFile>> TFinder::FindFile(const std::filesystem::path& path) {
    return FindGeneral<SFile, NFSExceptionType::NotFile>(path);
}

}