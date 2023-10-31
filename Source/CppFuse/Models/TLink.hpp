#ifndef CPPFUSE_TLINK_HPP
#define CPPFUSE_TLINK_HPP

#include <CppFuse/Models/TDirectory.hpp>
#include <filesystem>

namespace cppfuse {

class TLink : public TFileObjectMixin<TDirectory, NFileType::Link> {
    public:
    TLink(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent,
        const std::filesystem::path& linkTo);

    public:
    const std::filesystem::path& LinkTo() const;
    virtual void FillAttributes(struct stat* st) const override;

    protected:
    std::filesystem::path m_xLinkTo;
};

}

#endif //CPPFUSE_TLINK_HPP
