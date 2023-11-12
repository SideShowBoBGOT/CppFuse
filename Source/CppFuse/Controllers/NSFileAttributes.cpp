#include "NSFileAttributes.hpp"
#include <CppFuse/Controllers/TGetFileParameter.hpp>

namespace cppfuse::NSFileAttributes {

void UpdateSize(const rwl::TRwLockReadGuard<TDirectory>& varRead, struct stat* st) {
    st->st_size = 0;
}

void UpdateSize(const rwl::TRwLockReadGuard<TRegularFile>& varRead, struct stat* st) {
    st->st_size = static_cast<off_t>(varRead->Data.size());
}

void UpdateSize(const rwl::TRwLockReadGuard<TLink>& varRead, struct stat* st) {
    st->st_size = static_cast<off_t>(std::string_view(varRead->LinkTo.c_str()).size());
}

void GetGeneral(const CSharedRwFileObject auto& var, struct stat* st) {
    const auto varRead = var->Read();
    st->st_mode = TGetInfoMode{}(varRead);
    st->st_gid = TGetInfoGid{}(varRead);
    st->st_uid = TGetInfoUid{}(varRead);
    st->st_nlink = var.use_count();
    UpdateSize(varRead, st);
}

void Get(const ASharedFileVariant& var, struct stat* st) {
    std::visit([st](const auto& file) { GetGeneral(file, st); }, var);
}

}
