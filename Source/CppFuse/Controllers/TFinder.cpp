#include <CppFuse/Controllers/TFinder.hpp>
#include <CppFuse/Controllers/TFileSystem.hpp>
#include <algorithm>
#include <array>

namespace cppfuse {

static constexpr std::string_view s_sEmptyName = "";
static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

//AFSExpected<ASharedFileVariant> TFinder::Find(const AStdPath& path) {
//    return RecursiveFindStepOne(path, path.begin(), TFileSystem::RootDir());
//}
//
//AFSExpected<ASharedFileVariant> TFinder::RecursiveFindStepOne(const AStdPath& path, const AStdPathIt& it, const ASharedRwLock<TDirectory>& dir) {
//    const auto dirRead = dir->Read();
//    const auto ownName = std::string_view(dirRead->Name());
//    const auto itName = std::string_view(it->c_str());
//    const auto selfNames = std::array{s_sSelfName, s_sEmptyName, ownName};
//
//    if(std::ranges::contains(selfNames, itName)) {
//        return RecursiveFindStepTwo(path, it, dir);
//    }
//    const auto& fileObjects = dirRead->FileObjects();
//    const auto childIt = std::ranges::find_if(fileObjects,
//        [&itName](const auto& f) {
//            return std::visit([&itName](const auto& f) {
//                return f->Read()->Name() == itName;
//            }, f);
//        });
//    if(childIt == fileObjects.end()) {
//        return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::FileNotExist));
//    }
//    return RecursiveFindStepTwo(path, it, *childIt);
//}
//
//AFSExpected<ASharedFileVariant> TFinder::RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it, const ASharedFileVariant& obj) {
//    if(std::distance(it, path.end()) == 1) {
//        return obj;
//    }
//    if(const auto dir = std::get_if<ASharedRwLock<TDirectory>>(&obj)) {
//        return RecursiveFindStepOne(path, ++it, *dir);
//    }
//    return std::unexpected(TFSException(path.begin(), it, NFSExceptionType::NotDirectory));
//}
//
//AFSExpected<ASharedRwLock<TDirectory>> TFinder::FindDir(const AStdPath& path) {
//    return FindGeneral<TDirectory, NFSExceptionType::NotDirectory>(path);
//}
//
//AFSExpected<ASharedRwLock<TLink>> TFinder::FindLink(const std::filesystem::path& path) {
//    return FindGeneral<TLink, NFSExceptionType::NotLink>(path);
//}
//
//AFSExpected<ASharedRwLock<TFile>> TFinder::FindFile(const std::filesystem::path& path) {
//    return FindGeneral<TFile, NFSExceptionType::NotFile>(path);
//}

}