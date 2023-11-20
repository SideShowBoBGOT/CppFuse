#ifndef CPPFUSE_NSFINDFILE_HPP
#define CPPFUSE_NSFINDFILE_HPP

#include <CppFuse/Models/TFileObjects.hpp>

#include <set>

namespace cppfuse {

namespace NSFindFile {

ASharedFileVariant Find(const fs::path& path);
void AddToNameHash(const fs::path& path);
void RemoveFromNameHash(const fs::path& path);
const std::set<fs::path>& FindByName(const std::string& name);
ASharedRwLock<TDirectory> FindDir(const fs::path& path);
ASharedRwLock<TLink> FindLink(const fs::path& path);
ASharedRwLock<TRegularFile> FindRegularFile(const fs::path& path);

};

}

#endif //CPPFUSE_NSFINDFILE_HPP
