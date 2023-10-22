#ifndef CPPFUSE_TSPECIALIZEDOBJECTMIXIN_HPP
#define CPPFUSE_TSPECIALIZEDOBJECTMIXIN_HPP

#include "TObjectMixin.hpp"

namespace cppfuse {

template<auto ObjectMask, typename ParentType>
class TSpecializedObjectMixin : public TObjectMixin<ParentType> {
    public:
    TSpecializedObjectMixin(const std::string& name, mode_t mode)
        : TObjectMixin<ParentType>(name, mode | ObjectMask) {}
    virtual void Mode(mode_t mode) override { this->m_uMode = mode | ObjectMask; }
};

}

#endif //CPPFUSE_TSPECIALIZEDOBJECTMIXIN_HPP
