#include <CppFuse/Models/SLink.hpp>

namespace cppfuse {

void SLink::DoNew(const rwl::TRwLockWriteGuard<SLink>& var, const std::filesystem::path& path) { var->LinkTo = path; }

}