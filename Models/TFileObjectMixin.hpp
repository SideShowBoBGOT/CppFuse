#ifndef CPPFUSE_TFILEOBJECTMIXIN_HPP
#define CPPFUSE_TFILEOBJECTMIXIN_HPP

#include "NNFileType.hpp"
#include <TRwLock.hpp>
#include <string>

namespace cppfuse {

template<typename ParentType>
class TFileObjectMixin {
    public:
    TFileObjectMixin(const std::string& name, mode_t mode, const rppsync::TSharedRw<ParentType>& parent)
        : m_sName{name}, m_uMode{mode}, m_pParent{parent} {}
    virtual ~TFileObjectMixin()=default;

    public:
    virtual NFileType Type() const { return NNFileType::None; };
    virtual mode_t Mode() const { return m_uMode; }
    virtual void Mode(mode_t mode) { m_uMode = mode | Type(); }
    virtual const std::string& Name() const { return m_sName; }
    virtual void SetName(const std::string& name) { m_sName = name; }
    virtual const rppsync::TWeakRw<ParentType>& Parent() const { return m_pParent; }
    virtual void SetParent(const rppsync::TSharedRw<ParentType>& parent) { m_pParent = parent; }

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    rppsync::TWeakRw<ParentType> m_pParent;
};

}



#endif //CPPFUSE_TFILEOBJECTMIXIN_HPP
