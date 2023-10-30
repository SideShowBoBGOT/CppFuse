#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include <CppFuse/Models/TFileObjectMixin.hpp>

#include <sys/stat.h>
#include <vector>
#include <filesystem>

namespace cppfuse {

class TDirectory;
class TFile;
class TLink;

using TFileObject = TFileObjectMixin<TDirectory>;

class TDirectory : public TFileObject {
    public:
    TDirectory(const std::string& name, mode_t mode, const TSharedRwLock<TDirectory>& parent);

    public:
    virtual NFileType Type() const override;
    const std::vector<TSharedRwLock<TFileObject>>& FileObjects() const;

    protected:
    std::vector<TSharedRwLock<TFileObject>> m_vObjects;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
