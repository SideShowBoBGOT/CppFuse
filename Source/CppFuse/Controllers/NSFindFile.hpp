#ifndef CPPFUSE_NSFINDFILE_HPP
#define CPPFUSE_NSFINDFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

namespace cppfuse {

namespace NSFindFile {

ASharedFileVariant Find(const fs::path& path);
ASharedRwLock<TDirectory> FindDir(const fs::path& path);
ASharedRwLock<TLink> FindLink(const fs::path& path);
ASharedRwLock<TRegularFile> FindRegularFile(const fs::path& path);

};

}

#endif //CPPFUSE_NSFINDFILE_HPP
