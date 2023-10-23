#ifndef CPPFUSE_TOBJECTMIXIN_HPP
#define CPPFUSE_TOBJECTMIXIN_HPP

#include <TRwLock.hpp>
#include <string>

namespace cppfuse {

template<typename ParentType>
class TObjectMixin {
    public:
    TObjectMixin(const std::string& name, mode_t mode, const rppsync::TSharedRw<ParentType>& parent)
        : m_sName{name}, m_uMode{mode}, m_pParent{parent} {}
    virtual ~TObjectMixin()=default;

    public:
    [[nodiscard]] virtual mode_t Mode() const { return m_uMode; }
    virtual void SetMode(mode_t mode) { m_uMode = mode; }
    [[nodiscard]] virtual const std::string& Name() const { return m_sName; }
    virtual void SetName(const std::string& name) { m_sName = name; }
    [[nodiscard]] virtual const rppsync::TWeakRw<ParentType>& Parent() const { return m_pParent; }
    virtual void SetParent(const rppsync::TSharedRw<ParentType>& parent) { m_pParent = parent; }

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    rppsync::TWeakRw<ParentType> m_pParent;
};

}



#endif //CPPFUSE_TOBJECTMIXIN_HPP
