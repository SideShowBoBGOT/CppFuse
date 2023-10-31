#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include <CppFuse/Models/TFileObjectMixin.hpp>
#include <CppFuse/Models/ASharedFileVariant.hpp>

#include <sys/stat.h>
#include <vector>
#include <filesystem>

namespace cppfuse {

class TDirectory;

class TDirectory : public TFileObjectMixin<TDirectory, NFileType::Directory> {
    public:
    TDirectory(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent);

    public:
    const std::vector<ASharedFileVariant>& FileObjects() const;

    protected:
    std::vector<ASharedFileVariant> m_vObjects;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
