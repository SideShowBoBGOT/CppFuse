#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include "TFileObjectMixin.hpp"
#include "../Errors/TFSException.hpp"
#include <sys/stat.h>
#include <vector>
#include <filesystem>

namespace cppfuse {

class TDirectory;

using TFileObject = TFileObjectMixin<TDirectory>;

class TDirectory : public TFileObject {
    public:
    TDirectory(const std::string& name, mode_t mode, const rppsync::TSharedRw<TDirectory>& parent);

    public:
    virtual NFileType Type() const override;
    const std::vector<rppsync::TSharedRw<TFileObject>>& Objects() const;
    TFSExpected<rppsync::TSharedRw<TFileObject>> Find(const std::filesystem::path& path) const;

    protected:
    std::vector<rppsync::TSharedRw<TFileObject>> m_vObjects;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
