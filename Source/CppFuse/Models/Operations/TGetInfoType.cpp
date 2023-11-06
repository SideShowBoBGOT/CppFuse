#include <CppFuse/Models/Operations/TGetInfoType.hpp>

namespace cppfuse {

NFileType TGetInfoType::operator()(const rwl::TRwLockReadGuard<SDirectory>& var) {
    return NFileType::Directory;
}

NFileType TGetInfoType::operator()(const rwl::TRwLockReadGuard<SFile>& var) {
    return NFileType::File;
}

NFileType TGetInfoType::operator()(const rwl::TRwLockReadGuard<SLink>& var) {
    return NFileType::Link;
}

NFileType TGetInfoType::operator()(const rwl::TRwLockWriteGuard<SDirectory>& var) {
    return NFileType::Directory;
}

NFileType TGetInfoType::operator()(const rwl::TRwLockWriteGuard<SFile>& var) {
    return NFileType::File;
}

NFileType TGetInfoType::operator()(const rwl::TRwLockWriteGuard<SLink>& var) {
    return NFileType::Link;
}

}
