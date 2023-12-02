#include <CppFuse/Controllers/NSAccessFile.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>
#include "CppFuse/Helpers/NSHelperFuncs.hpp"

#define FUSE_USE_VERSION 30
#include <fuse3/fuse.h>

#include <array>
#include <map>

namespace cppfuse::NSAccessFile {

static const auto s_mAccessFlags = std::map<int, int> {
    {O_RDONLY, R_OK},
    {O_WRONLY, W_OK},
    {O_RDWR, W_OK | R_OK},
    {O_EXCL, X_OK}
};

NFileAccess AccessSpecialized(const std::array<int, 3>& sFlags, const mode_t mode, const int accessMask) {
    auto specializedMode = 0;
    static std::array<int, 3> accessFlags = {R_OK, W_OK, X_OK};
    for(auto i = 0u; i < accessFlags.size(); ++i) {
        if(mode & sFlags[i]) specializedMode |= accessFlags[i];
    }
    auto res = specializedMode & accessMask;
    return res ? NFileAccess::Ok : NFileAccess::Restricted;
}

NFileAccess Access(const std::filesystem::path& path, int accessMask) {
    const auto var = [path]() {
        auto var = NSFindFile::Find(path);
        if(const auto link = std::get_if<ASharedRwLock<TLink>>(&var)) {
            const auto readLink = (*link)->Read();
            return NSFindFile::Find(readLink->LinkTo);
        }
        return var;
    }();
    const auto mode = TGetInfoMode{}(var);
    const auto context = fuse_get_context();
    const auto uid = TGetInfoUid{}(var);

    if(uid == 0) {
        return NFileAccess::Ok;
    }

    if(uid == context->uid) {
        return AccessSpecialized({S_IRUSR, S_IWUSR, S_IXUSR}, mode, accessMask);
    }
    if(TGetInfoGid{}(var) == context->gid) {
        return AccessSpecialized({S_IRGRP, S_IWGRP, S_IXGRP}, mode, accessMask);
    }
    return AccessSpecialized({S_IROTH, S_IWOTH, S_IXOTH}, mode, accessMask);
}

NFileAccess AccessWithFuseFlags(const fs::path& path, int fuseFlags) {
    auto mask = 0;
    for(const auto [oFlag, okFlag] : s_mAccessFlags) {
        if(NSHelperFuncs::IsHasFlag(fuseFlags, oFlag)) {
            mask |= okFlag;
        }
    }
    return Access(path, mask);
}

}