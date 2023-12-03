#ifndef CPPFUSE_NSACCESSFILE_HPP
#define CPPFUSE_NSACCESSFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>
#include <CppFuse/Models/NNFileAccess.hpp>

#include <filesystem>

namespace cppfuse::NSAccessFile {

namespace fs = std::filesystem;

NFileAccess Access(const fs::path& path, const int accessMask);
NFileAccess Access(const ASharedFileVariant& var, const int accessMask);
NFileAccess Access(const ASharedRwLock<TLink>& var, const int accessMask);
NFileAccess Access(const ASharedRwLock<TRegularFile>& var, const int accessMask);
NFileAccess Access(const ASharedRwLock<TDirectory>& var, const int accessMask);
NFileAccess AccessWithFuseFlags(const fs::path& path, const int fuseFlags);
NFileAccess AccessWithFuseFlags(const ASharedFileVariant& var, const int fuseFlags);
NFileAccess AccessWithFuseFlags(const ASharedRwLock<TRegularFile>& var, const int fuseFlags);
NFileAccess AccessWithFuseFlags(const ASharedRwLock<TLink>& var, const int fuseFlags);
NFileAccess AccessWithFuseFlags(const ASharedRwLock<TDirectory>& var, const int fuseFlags);

}

#endif //CPPFUSE_NSACCESSFILE_HPP
