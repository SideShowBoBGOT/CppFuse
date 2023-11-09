#include <CppFuse/Models/Objects/TFileObjects.hpp>
#include <CppFuse/Models/Operations/TSetInfoParameter.hpp>

namespace cppfuse {

static void Update(rwl::TRwLockWriteGuard<TLink>& writeObj, const char* path) {
    writeObj->LinkTo = path;
}

template<typename T, typename... Args>
static ASharedRwLock<T> DoNew(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent, Args&& ... args) {
    const auto obj = MakeSharedRwLock<T>();
    {
        auto objWrite = obj->Write();
        TSetInfoName{name}(objWrite);
        TSetInfoMode{mode}(objWrite);
        TSetInfoUid{getuid()}(objWrite);
        TSetInfoGid{getgid()}(objWrite);

        if constexpr(std::is_same_v<T, TLink>) {
            Update(objWrite, args...);
        }
    }
    TSetInfoParent{parent}(obj);
    return obj;
}

ASharedRwLock<TDirectory> TDirectory::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent) {
    return DoNew<TDirectory>(name, mode, parent);
}

ASharedRwLock<TFile> TFile::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent) {
    return DoNew<TFile>(name, mode, parent);
}

ASharedRwLock<TLink> TLink::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent, const char* path) {
    return DoNew<TLink>(name, mode, parent, path);
}

}