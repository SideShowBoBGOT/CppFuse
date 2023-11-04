#include <CppFuse/Models/TFileSystemObjects.hpp>

namespace cppfuse {

template<> std::string SInfo::* AGetName::s_pFieldPtr = nullptr;
template<> mode_t SInfo::* AGetMode::s_pFieldPtr = nullptr;
template<> AWeakRwLock<SDirectory> SInfo::* AGetParent::s_pFieldPtr = nullptr;
template<> std::string SInfo::* ASetName::s_pFieldPtr = nullptr;
template<> mode_t SInfo::* ASetMode::s_pFieldPtr = nullptr;
template<> AWeakRwLock<SDirectory> SInfo::* ASetParent::s_pFieldPtr = nullptr;

template<> int AGetName::Init() { s_pFieldPtr = &SInfo::m_sName; return 0; }
template<> int AGetMode::Init() { s_pFieldPtr = &SInfo::m_uMode; return 0; }
template<> int AGetParent::Init() { s_pFieldPtr = &SInfo::m_pParent; return 0; }

template<> int ASetName::Init() { s_pFieldPtr = &SInfo::m_sName; return 0; }
template<> int ASetMode::Init() { s_pFieldPtr = &SInfo::m_uMode; return 0; }
template<> int ASetParent::Init() { s_pFieldPtr = &SInfo::m_pParent; return 0; }

#define INIT_FUNC(ClassName) const auto s_iInit##ClassName = ClassName::Init();
    INIT_FUNC(AGetName)
    INIT_FUNC(AGetMode)
    INIT_FUNC(AGetParent)
    INIT_FUNC(ASetName)
    INIT_FUNC(ASetMode)
    INIT_FUNC(ASetParent)
#undef INIT_FUNC

void SDirectory::DoNew(const rwl::TRwLockWriteGuard<SDirectory>& var) {}
void SFile::DoNew(const rwl::TRwLockWriteGuard<SFile>& var) {}
void SLink::DoNew(const rwl::TRwLockWriteGuard<SLink>& var, const std::filesystem::path& path) { var->LinkTo = path; }

}