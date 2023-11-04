#include <CppFuse/Models/TSetParameter.hpp>
#include <CppFuse/Models/SInfo.hpp>

namespace cppfuse {

template<> std::string SInfo::* ASetName::s_pFieldPtr = nullptr;
template<> mode_t SInfo::* ASetMode::s_pFieldPtr = nullptr;
template<> AWeakRwLock<SDirectory> SInfo::* ASetParent::s_pFieldPtr = nullptr;

template<> void ASetName::Init() { s_pFieldPtr = &SInfo::m_sName; }
template<> void ASetMode::Init() { s_pFieldPtr = &SInfo::m_uMode; }
template<> void ASetParent::Init() { s_pFieldPtr = &SInfo::m_pParent; }

}