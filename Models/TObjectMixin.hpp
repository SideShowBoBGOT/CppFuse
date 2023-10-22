#ifndef CPPFUSE_TOBJECTMIXIN_HPP
#define CPPFUSE_TOBJECTMIXIN_HPP

#include <TRwLock.hpp>

#include <string>
#include <memory>

namespace cppfuse {

template<typename ParentType>
class TObjectMixin {
    public:
    using TRwParent = ::std::shared_ptr<::rppsync::TRwLock<ParentType>>;

    public:
    TObjectMixin(const std::string& name, mode_t mode)
        : m_sName{name}, m_uMode{mode} {}
    virtual ~TObjectMixin()=default;

    public:
    [[nodiscard]] virtual mode_t Mode() const { return this->m_uMode; }
    virtual void Mode(mode_t mode) { this->m_uMode = mode; }
    [[nodiscard]] virtual const std::string& Name() const { return m_sName; }
    virtual void Name(const std::string& name) { m_sName = name; }
    virtual const TRwParent& Parent() const { return m_pParent; }
    virtual void Parent(const TRwParent& parent) { m_pParent = parent; }

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    TRwParent m_pParent = nullptr;
};

}



#endif //CPPFUSE_TOBJECTMIXIN_HPP
