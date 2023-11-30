#include <CppFuse/Controllers/NSAccessFile.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>

#define FUSE_USE_VERSION 30
#include <fuse3/fuse.h>

#include <array>

namespace cppfuse::NSAccessFile {

int AccessSpecialized(const std::array<int, 3>& sFlags, const mode_t mode, const int accessMask) {
    auto specializedMode = 0;
    static std::array<int, 3> accessFlags = {R_OK, W_OK, X_OK};
    for(auto i = 0; i < accessFlags.size(); ++i) {
        if(mode & sFlags[i]) specializedMode |= accessFlags[i];
    }
    auto res = specializedMode & accessMask;
    return res ? 0 : -1;
}

int Access(const std::filesystem::path& path, int accessMask) {
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
        return 0;
    }

    if(uid == context->uid) {
        return AccessSpecialized({S_IRUSR, S_IWUSR, S_IXUSR}, mode, accessMask);
    }
    if(TGetInfoGid{}(var) == context->gid) {
        return AccessSpecialized({S_IRGRP, S_IWGRP, S_IXGRP}, mode, accessMask);
    }
    return AccessSpecialized({S_IROTH, S_IWOTH, S_IXOTH}, mode, accessMask);
}

}