#include "TFileObjects.hpp"
#include "CppFuse/Controllers/TSetFileParameter.hpp"

namespace cppfuse {

static void Update(rwl::TRwLockWriteGuard<TLink>& writeObj, const fs::path& path) {
    writeObj->LinkTo = path;
}

static void Update(rwl::TRwLockWriteGuard<TRegularFile>& writeObj) {
    writeObj->Data.resize(TRegularFile::ReservedSpace);
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

        if constexpr(std::same_as<T, TLink>) {
            Update(objWrite, args...);
        } else if constexpr(std::same_as<T, TRegularFile>) {
            Update(objWrite);
        }
    }
    TSetInfoParent{parent}(obj);
    return obj;
}

ASharedRwLock<TDirectory> TDirectory::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent) {
    return DoNew<TDirectory>(name, mode, parent);
}

ASharedRwLock<TRegularFile> TRegularFile::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent) {
    return DoNew<TRegularFile>(name, mode, parent);
}

unsigned TRegularFile::ReservedSpace = 0;

ASharedRwLock<TLink> TLink::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent, const fs::path& path) {
    return DoNew<TLink>(name, mode, parent, path);
}

}