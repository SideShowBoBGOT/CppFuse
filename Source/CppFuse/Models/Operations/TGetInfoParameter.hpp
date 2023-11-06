#ifndef CPPFUSE_TGETINFOPARAMETER_HPP
#define CPPFUSE_TGETINFOPARAMETER_HPP

#include "CppFuse/Models/Aliases/ASharedFileVariant.hpp"
#include "CppFuse/Models/Concepts/CSharedRwFileObject.hpp"
#include "CppFuse/Models/Concepts/CRwGuardFileObject.hpp"

namespace cppfuse {

class TGetInfoName {
    public:
    TGetInfoName()=default;

    public:
    const std::string& operator()(const ASharedFileVariant& var);
    const std::string& operator()(const CSharedRwFileObject auto& var);
    const std::string& operator()(const CReadGuardFileObject auto& var);
    std::string& operator()(const CWriteGuardFileObject auto& var);
};

class TGetInfoUid {
    public:
    TGetInfoUid()=default;

    public:
    const uid_t& operator()(const ASharedFileVariant& var);
    const uid_t& operator()(const CSharedRwFileObject auto& var);
    const uid_t& operator()(const CReadGuardFileObject auto& var);
    uid_t& operator()(const CWriteGuardFileObject auto& var);
};

class TGetInfoGid {
    public:
    TGetInfoGid()=default;

    public:
    const gid_t& operator()(const ASharedFileVariant& var);
    const gid_t& operator()(const CSharedRwFileObject auto& var);
    const gid_t& operator()(const CReadGuardFileObject auto& var);
    gid_t& operator()(const CWriteGuardFileObject auto& var);
};

class TGetInfoMode {
    public:
    TGetInfoMode()=default;

    public:
    const mode_t& operator()(const ASharedFileVariant& var);
    const mode_t& operator()(const CSharedRwFileObject auto& var);
    const mode_t& operator()(const CReadGuardFileObject auto& var);
    mode_t& operator()(const CWriteGuardFileObject auto& var);
};

class TGetInfoParent {
    public:
    TGetInfoParent()=default;

    public:
    const AWeakRwLock<SDirectory>& operator()(const ASharedFileVariant& var);
    const AWeakRwLock<SDirectory>& operator()(const CSharedRwFileObject auto& var);
    const AWeakRwLock<SDirectory>& operator()(const CReadGuardFileObject auto& var);
    AWeakRwLock<SDirectory>& operator()(const CWriteGuardFileObject auto& var);
};

}

#endif //CPPFUSE_TGETINFOPARAMETER_HPP
