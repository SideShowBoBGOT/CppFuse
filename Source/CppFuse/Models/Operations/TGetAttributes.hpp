#ifndef CPPFUSE_TGETATTRIBUTES_HPP
#define CPPFUSE_TGETATTRIBUTES_HPP

#include <CppFuse/Models/Objects/TFileObjects.hpp>
#include <sys/stat.h>

namespace cppfuse {

class TGetAttributes {
    public:
    explicit TGetAttributes(struct stat* st);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var);

    protected:
    void UpdateSize(const rwl::TRwLockReadGuard<TDirectory>& varRead);
    void UpdateSize(const rwl::TRwLockReadGuard<TFile>& varRead);
    void UpdateSize(const rwl::TRwLockReadGuard<TLink>& varRead);

    protected:
    struct stat* m_pSt = nullptr;
};

}

#endif //CPPFUSE_TGETATTRIBUTES_HPP
