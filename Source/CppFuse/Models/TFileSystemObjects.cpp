#include <CppFuse/Models/TFileSystemObjects.hpp>

namespace cppfuse {

void SetParent::operator()(const ASharedRwLock<SDirectory>& var, const ASharedRwLock<SDirectory>& parent) { SetParent{}(var->Write(), parent); }
void SetParent::operator()(const ASharedRwLock<SFile>& var, const ASharedRwLock<SDirectory>& parent) { SetParent{}(var->Write(), parent); }
void SetParent::operator()(const ASharedRwLock<SLink>& var, const ASharedRwLock<SDirectory>& parent) { SetParent{}(var->Write(), parent); }
void SetParent::operator()(const rwl::TRwLockWriteGuard<SDirectory>& var, const ASharedRwLock<SDirectory>& parent) { var->m_pParent = parent; }
void SetParent::operator()(const rwl::TRwLockWriteGuard<SFile>& var, const ASharedRwLock<SDirectory>& parent) { var->m_pParent = parent; }
void SetParent::operator()(const rwl::TRwLockWriteGuard<SLink>& var, const ASharedRwLock<SDirectory>& parent) { var->m_pParent = parent; }

}