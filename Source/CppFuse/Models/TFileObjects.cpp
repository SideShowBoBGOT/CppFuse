#include <CppFuse/Models/TFileObjects.hpp>
#include <CppFuse/Controllers/TSetFileParameter.hpp>

#define FUSE_USE_VERSION 30
#include <fuse3/fuse.h>

namespace cppfuse {

static void Update(rwl::TRwLockWriteGuard<TLink>& writeObj, const fs::path& path) {
    writeObj->LinkTo = path;
}

template<typename T, typename... Args>
static ASharedRwLock<T> DoNew(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent, Args&& ... args) {
    const auto obj = MakeSharedRwLock<T>();
    {
        auto objWrite = obj->Write();
        TSetInfoName{name}(objWrite);
        TSetInfoMode{mode}(objWrite);

        const auto context = fuse_get_context();
        TSetInfoUid{context->uid}(objWrite);
        TSetInfoGid{context->gid}(objWrite);

        if constexpr(std::same_as<T, TLink>) {
            Update(objWrite, args...);
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

ASharedRwLock<TLink> TLink::New(const std::string& name, mode_t mode, const ASharedRwLock<cppfuse::TDirectory>& parent, const fs::path& path) {
    return DoNew<TLink>(name, mode, parent, path);
}

}