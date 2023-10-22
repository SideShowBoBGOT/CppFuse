#ifndef CPPFUSE_TDIRECTORY_HPP
#define CPPFUSE_TDIRECTORY_HPP

#include "TSpecializedObjectMixin.hpp"
#include <sys/stat.h>
#include <vector>

namespace cppfuse {

class TDirectory;

using TRwObject = ::std::shared_ptr<::rppsync::TRwLock<TDirectory>>;

class TDirectory : public TSpecializedObjectMixin<S_IFDIR, TDirectory> {
    public:
    TDirectory(const std::string& name, mode_t mode);
    [[nodiscard]] const std::vector<TRwObject>& Objects() const;

    protected:
    std::vector<TRwObject> m_vObjects;
};

}

#endif //CPPFUSE_TDIRECTORY_HPP
