#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include "TSpecializedObjectMixin.hpp"
#include <sys/stat.h>
#include <vector>

namespace cppfuse {

class TDirectory;

using TFileObject = TObjectMixin<TDirectory>;

template<auto ObjectMask>
using TFileSpecializedObject = TSpecializedObjectMixin<ObjectMask, TDirectory>;

class TDirectory : public TFileSpecializedObject<S_IFDIR> {
    public:
    TDirectory(const std::string& name, mode_t mode, const rppsync::TSharedRw<TDirectory>& parent);
    [[nodiscard]] const std::vector<rppsync::TSharedRw<TFileObject>>& Objects() const;

    protected:
    std::vector<rppsync::TSharedRw<TFileObject>> m_vObjects;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
