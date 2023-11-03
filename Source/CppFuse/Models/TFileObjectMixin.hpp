#ifndef CPPFUSE_TFILEOBJECTMIXIN_HPP
#define CPPFUSE_TFILEOBJECTMIXIN_HPP

#include <CppFuse/Models/NNFileType.hpp>
#include <CppFuse/Helpers/ASharedLock.hpp>

#include <type_traits>
#include <string>
#include <utility>

namespace cppfuse {

template<typename ParentType, auto FileType>
class TFileObjectMixin {
    public:
    TFileObjectMixin(const std::string& name, mode_t mode, const ASharedRwLock<ParentType>& parent)
        : m_sName{name}, m_pParent{parent} { Mode(mode); }

    public:
    mode_t Mode() const { return m_uMode; }
    void Mode(mode_t mode) { m_uMode = mode | FileType; }

    public:
    const std::string& Name() const { return this->m_sName; }
    void Name(const std::string& name) { this->m_sName = name; }

    public:
    const AWeakRwLock<ParentType>& Parent() const { return this->m_pParent; }
    void Parent(const ASharedRwLock<ParentType>& parent) { this->m_pParent = parent; }

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    ASharedRwLock<ParentType> m_pParent;
};

}



#endif //CPPFUSE_TFILEOBJECTMIXIN_HPP
