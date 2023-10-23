#ifndef CPPFUSE_TLINK_HPP
#define CPPFUSE_TLINK_HPP

#include "TDirectory.hpp"
#include <filesystem>

namespace cppfuse {

class TLink : public TSpecializedObjectMixin<S_IFLNK, TDirectory> {
    public:
    TLink(const std::string& name, mode_t mode, const rppsync::TSharedRw<TDirectory>& parent,
        const std::filesystem::path& linkTo);
    [[nodiscard]] const std::filesystem::path& LinkTo() const;

    protected:
    std::filesystem::path m_xLinkTo;
};

}

#endif //CPPFUSE_TLINK_HPP
