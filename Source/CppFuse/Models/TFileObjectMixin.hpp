#ifndef CPPFUSE_TFILEOBJECTMIXIN_HPP
#define CPPFUSE_TFILEOBJECTMIXIN_HPP

#include <CppFuse/Models/NNFileType.hpp>
#include <CppFuse/Helpers/ASharedLock.hpp>
#include <string>

namespace cppfuse {

template<typename ParentType>
class TFileObjectMixin {
    public:
    TFileObjectMixin(const std::string& name, mode_t mode, const ASharedRwLock<ParentType>& parent)
        : m_sName{name}, m_uMode{mode}, m_pParent{parent} {}
    virtual ~TFileObjectMixin()=default;

    public:
    virtual NFileType Type() const { return NNFileType::None; };
    virtual mode_t Mode() const { return this->m_uMode; }
    virtual void Mode(mode_t mode) { this->m_uMode = mode | Type(); }
    virtual const std::string& Name() const { return this->m_sName; }
    virtual void SetName(const std::string& name) { this->m_sName = name; }
    virtual const AWeakRwLock<ParentType>& Parent() const { return this->m_pParent; }
    virtual void SetParent(const ASharedRwLock<ParentType>& parent) { this->m_pParent = parent; }

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    AWeakRwLock<ParentType> m_pParent;
};

}



#endif //CPPFUSE_TFILEOBJECTMIXIN_HPP
