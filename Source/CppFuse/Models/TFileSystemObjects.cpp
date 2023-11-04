#include <CppFuse/Models/TFileSystemObjects.hpp>

namespace cppfuse {

inline void UpdateParent(AWeakRwLock<SDirectory>& outParent, const ASharedRwLock<SDirectory>& parent) { outParent = parent; }

void SetParent::operator()(const ASharedRwLock<SDirectory>& var, const ASharedRwLock<SDirectory>& parent) { SetParent{}(var->Write(), parent); }
void SetParent::operator()(const ASharedRwLock<SFile>& var, const ASharedRwLock<SDirectory>& parent) { SetParent{}(var->Write(), parent); }
void SetParent::operator()(const ASharedRwLock<SLink>& var, const ASharedRwLock<SDirectory>& parent) { SetParent{}(var->Write(), parent); }
void SetParent::operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const ASharedRwLock<SDirectory>& parent) { UpdateParent(var->m_pParent, parent); }
void SetParent::operator()(const rwl::TRwLockWriteGuard<SFile>& var, const ASharedRwLock<SDirectory>& parent) { UpdateParent(var->m_pParent, parent); }
void SetParent::operator()(const rwl::TRwLockWriteGuard<SLink>& var, const ASharedRwLock<SDirectory>& parent) { UpdateParent(var->m_pParent, parent); }

inline void UpdateName(std::string& outName, const std::string& name) { outName = name; }

void SetName::operator()(const ASharedRwLock<SDirectory>& var, const std::string& name) { SetName{}(var->Write(), name); }
void SetName::operator()(const ASharedRwLock<SFile>& var, const std::string& name) { SetName{}(var->Write(), name); }
void SetName::operator()(const ASharedRwLock<SLink>& var, const std::string& name) { SetName{}(var->Write(), name); }
void SetName::operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const std::string& name) { UpdateName(var->m_sName, name); }
void SetName::operator()(const rwl::TRwLockWriteGuard<SFile>& var, const std::string& name) { UpdateName(var->m_sName, name); }
void SetName::operator()(const rwl::TRwLockWriteGuard<SLink>& var, const std::string& name) { UpdateName(var->m_sName, name); }

NFileType GetType::operator()(const ASharedRwLock<SDirectory>& var) { return NFileType::Directory; }
NFileType GetType::operator()(const ASharedRwLock<SFile>& var) { return NFileType::File; }
NFileType GetType::operator()(const ASharedRwLock<SLink>& var) { return NFileType::Link; }
NFileType GetType::operator()(const rwl::TRwLockReadGuard<SDirectory>& var) { return NFileType::Directory; }
NFileType GetType::operator()(const rwl::TRwLockReadGuard<SFile>& var) { return NFileType::File; }
NFileType GetType::operator()(const rwl::TRwLockReadGuard<SLink>& var) { return NFileType::Link; }
NFileType GetType::operator()(const rwl::TRwLockWriteGuard<SDirectory>& var) { return NFileType::Directory; }
NFileType GetType::operator()(const rwl::TRwLockWriteGuard<SFile>& var) { return NFileType::File; }
NFileType GetType::operator()(const rwl::TRwLockWriteGuard<SLink>& var) { return NFileType::Link; }

template<typename T>
inline void UpdateMode(mode_t& outMode, mode_t mode, const T& var) { outMode = mode | GetType{}(var); }

void SetMode::operator()(const ASharedRwLock<SDirectory>& var, mode_t mode) { SetMode{}(var->Write(), mode); }
void SetMode::operator()(const ASharedRwLock<SFile>& var, mode_t mode) { SetMode{}(var->Write(), mode); }
void SetMode::operator()(const ASharedRwLock<SLink>& var, mode_t mode) { SetMode{}(var->Write(), mode); }
void SetMode::operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, mode_t mode) { UpdateMode(var->m_uMode, mode, var); }
void SetMode::operator()(const rwl::TRwLockWriteGuard<SFile>& var, mode_t mode) { UpdateMode(var->m_uMode, mode, var); }
void SetMode::operator()(const rwl::TRwLockWriteGuard<SLink>& var, mode_t mode) { UpdateMode(var->m_uMode, mode, var); }

void SDirectory::DoNew(const rwl::TRwLockWriteGuard<SDirectory>& var) {}
void SFile::DoNew(const rwl::TRwLockWriteGuard<SFile>& var) {}
void SLink::DoNew(const rwl::TRwLockWriteGuard<SLink>& var, const std::filesystem::path& path) {
    var->LinkTo = path;
}

}