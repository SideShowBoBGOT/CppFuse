#ifndef CPPFUSE_TGETATTRIBUTES_HPP
#define CPPFUSE_TGETATTRIBUTES_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>
#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>
#include <sys/stat.h>

namespace cppfuse {

class TGetAttributes {
    public:
    explicit TGetAttributes(struct stat* st);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var) {
        const auto varRead = var->Read();
        m_pSt->st_mode = TGetInfoMode{}(varRead);
        m_pSt->st_gid = TGetInfoGid{}(varRead);
        m_pSt->st_uid = TGetInfoUid{}(varRead);
        m_pSt->st_nlink = var.use_count();
        UpdateSize(varRead);
    }

    protected:
    void UpdateSize(const rwl::TRwLockReadGuard<TDirectory>& varRead);
    void UpdateSize(const rwl::TRwLockReadGuard<TFile>& varRead);
    void UpdateSize(const rwl::TRwLockReadGuard<TLink>& varRead);

    protected:
    struct stat* m_pSt = nullptr;
};

}

#endif //CPPFUSE_TGETATTRIBUTES_HPP
