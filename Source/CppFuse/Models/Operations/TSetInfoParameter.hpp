#ifndef CPPFUSE_TSETINFOPARAMETER_HPP
#define CPPFUSE_TSETINFOPARAMETER_HPP

#include "CppFuse/Models/Aliases/ASharedFileVariant.hpp"
#include "CppFuse/Models/Concepts/CSharedRwFileObject.hpp"
#include "CppFuse/Models/Concepts/CRwGuardFileObject.hpp"

namespace cppfuse {

class TSetInfoName {
    public:
    TSetInfoName(const std::string& param);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var);
    void operator()(const CWriteGuardFileObject auto& var);

    protected:
    const std::string& m_Param;
};

class TSetInfoUid {
    public:
    TSetInfoUid(const uid_t & param);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var);
    void operator()(const CWriteGuardFileObject auto& var);

    protected:
    const uid_t& m_Param;
};

class TSetInfoGid {
    public:
    TSetInfoGid(const gid_t & param);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var);
    void operator()(const CWriteGuardFileObject auto& var);

    protected:
    const gid_t& m_Param;
};

class TSetInfoMode {
    public:
    TSetInfoMode(const mode_t& param);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var);
    void operator()(const CWriteGuardFileObject auto& var);

    protected:
    const mode_t& m_Param;
};

class TSetInfoParent {
    public:
    TSetInfoParent(const ASharedRwLock<SDirectory>& param);

    public:
    void operator()(const ASharedFileVariant& var);
    void operator()(const CSharedRwFileObject auto& var);

    protected:
    void operator()(const CWriteGuardFileObject auto& var);

    protected:
    const ASharedRwLock<SDirectory>& m_Param;
};

}

#endif //CPPFUSE_TSETINFOPARAMETER_HPP