#include <CppFuse/Models/TGetParameter.hpp>
#include <CppFuse/Models/SInfo.hpp>

namespace cppfuse {

template<> std::string SInfo::* AGetName::s_pFieldPtr = nullptr;
template<> mode_t SInfo::* AGetMode::s_pFieldPtr = nullptr;
template<> AWeakRwLock<SDirectory> SInfo::* AGetParent::s_pFieldPtr = nullptr;

template<> void AGetName::Init() { s_pFieldPtr = &SInfo::m_sName; }
template<> void AGetMode::Init() { s_pFieldPtr = &SInfo::m_uMode; }
template<> void AGetParent::Init() { s_pFieldPtr = &SInfo::m_pParent; }

}