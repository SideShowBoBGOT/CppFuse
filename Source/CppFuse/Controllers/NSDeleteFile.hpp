#ifndef CPPFUSE_NSDELETEFILE_HPP
#define CPPFUSE_NSDELETEFILE_HPP

#include <filesystem>

namespace fs = std::filesystem;

namespace cppfuse::NSDeleteFile {

void Delete(const fs::path& path);

}



#endif //CPPFUSE_NSDELETEFILE_HPP
