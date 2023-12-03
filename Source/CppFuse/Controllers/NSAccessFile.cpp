#include <CppFuse/Controllers/NSAccessFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>

#define FUSE_USE_VERSION 30
#include <fuse3/fuse.h>

#include <array>
#include <map>

namespace cppfuse::NSAccessFile {

const std::map<int, int> s_mAccessFlags = std::map<int, int> {
    {O_RDONLY, R_OK},
    {O_WRONLY, W_OK},
    {O_RDWR, W_OK | R_OK},
    {O_PATH, X_OK}
};

NFileAccess DoAccess(const std::array<int, 3>& sFlags, const mode_t mode, const int accessMask) {
    auto specializedMode = 0;
    static std::array<int, 3> accessFlags = {R_OK, W_OK, X_OK};
    for(auto i = 0u; i < accessFlags.size(); ++i) {
        if(mode & sFlags[i]) specializedMode |= accessFlags[i];
    }
    auto res = specializedMode & accessMask;
    return res ? NFileAccess::Ok : NFileAccess::Restricted;
}

NFileAccess AccessSpecialized(const CSharedRwFileObject auto& var, const int accessMask) {
    const auto mode = TGetInfoMode{}(var);
    const auto context = fuse_get_context();
    const auto uid = TGetInfoUid{}(var);

    if(uid == 0) {
        return NFileAccess::Ok;
    }

    if(uid == context->uid) {
        return DoAccess({S_IRUSR, S_IWUSR, S_IXUSR}, mode, accessMask);
    }
    if(TGetInfoGid{}(var) == context->gid) {
        return DoAccess({S_IRGRP, S_IWGRP, S_IXGRP}, mode, accessMask);
    }
    return DoAccess({S_IROTH, S_IWOTH, S_IXOTH}, mode, accessMask);
}

NFileAccess Access(const fs::path& path, const int accessMask) {
    return Access(NSFindFile::Find(path), accessMask);
}

NFileAccess Access(const ASharedFileVariant& var, const int accessMask) {
    return std::visit([accessMask](const auto& file) {
        return NSAccessFile::Access(file, accessMask);
    }, var);
}

NFileAccess Access(const ASharedRwLock<TLink>& var, const int accessMask) {
    return Access(NSFindFile::Find(var->Read()->LinkTo), accessMask);
}

NFileAccess Access(const ASharedRwLock<TRegularFile>& var, const int accessMask) {
    return AccessSpecialized(var, accessMask);
}

NFileAccess Access(const ASharedRwLock<TDirectory>& var, const int accessMask) {
    return AccessSpecialized(var, accessMask);
}

NFileAccess AccessWithFuseFlags(const fs::path& path, const int fuseFlags) {
    return AccessWithFuseFlags(NSFindFile::Find(path), fuseFlags);
}

NFileAccess AccessWithFuseFlags(const ASharedFileVariant& var, const int fuseFlags) {
    return std::visit([fuseFlags](const auto& file) {
        return NSAccessFile::AccessWithFuseFlags(file, fuseFlags);
    }, var);
}

NFileAccess AccessWithFuseFlagsSpecialized(const CSharedRwFileObject auto& var, const int fuseFlags) {
    auto mask = 0;
    for(const auto [oFlag, okFlag] : s_mAccessFlags) {
        if((fuseFlags & oFlag) == oFlag) {
            mask |= okFlag;
        }
    }
    return NSAccessFile::Access(var, mask);
}

NFileAccess AccessWithFuseFlags(const ASharedRwLock<TRegularFile>& var, const int fuseFlags) {
    return AccessWithFuseFlagsSpecialized(var, fuseFlags);
}

NFileAccess AccessWithFuseFlags(const ASharedRwLock<TLink>& var, const int fuseFlags) {
    return AccessWithFuseFlagsSpecialized(var, fuseFlags);
}

NFileAccess AccessWithFuseFlags(const ASharedRwLock<TDirectory>& var, const int fuseFlags) {
    return AccessWithFuseFlagsSpecialized(var, fuseFlags);
}

}