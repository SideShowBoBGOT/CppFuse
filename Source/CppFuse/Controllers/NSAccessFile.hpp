#ifndef CPPFUSE_NSACCESSFILE_HPP
#define CPPFUSE_NSACCESSFILE_HPP

#include <filesystem>

#include <CppFuse/Models/NNFileAccess.hpp>

namespace cppfuse::NSAccessFile {

namespace fs = std::filesystem;

NFileAccess Access(const fs::path& path, int accessMask);
NFileAccess AccessWithFuseFlags(const fs::path& path, int fuseFlags);

}

#endif //CPPFUSE_NSACCESSFILE_HPP
