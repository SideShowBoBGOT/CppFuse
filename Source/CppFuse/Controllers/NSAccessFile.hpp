#ifndef CPPFUSE_NSACCESSFILE_HPP
#define CPPFUSE_NSACCESSFILE_HPP

#include <filesystem>

namespace cppfuse::NSAccessFile {

namespace fs = std::filesystem;

int Access(const fs::path& path, int accessMask);

}

#endif //CPPFUSE_NSACCESSFILE_HPP
