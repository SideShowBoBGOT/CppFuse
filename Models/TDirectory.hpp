#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include "TSpecializedObjectMixin.hpp"
#include <sys/stat.h>
#include <vector>

namespace cppfuse {

class TDirectory;

using TFileObject = TObjectMixin<TDirectory>;

class TDirectory : public TSpecializedObjectMixin<S_IFDIR, TDirectory> {
    public:
    TDirectory(const std::string& name, mode_t mode, const rppsync::TSharedRw<TDirectory>& parent);
    [[nodiscard]] const std::vector<rppsync::TSharedRw<TFileObject>>& Objects() const;

    protected:
    std::vector<rppsync::TSharedRw<TFileObject>> m_vObjects;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
