#ifndef CPPFUSE_TLINK_HPP
#define CPPFUSE_TLINK_HPP

#include <CppFuse/Models/TDirectory.hpp>
#include <filesystem>

namespace cppfuse {

class TLink : public TFileObject {
    public:
    TLink(const std::string& name, mode_t mode, const TSharedRwLock<TDirectory>& parent,
        const std::filesystem::path& linkTo);

    public:
    virtual NFileType Type() const override;
    const std::filesystem::path& LinkTo() const;

    protected:
    std::filesystem::path m_xLinkTo;
};

}

#endif //CPPFUSE_TLINK_HPP