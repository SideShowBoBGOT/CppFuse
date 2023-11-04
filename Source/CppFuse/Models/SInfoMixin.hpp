#ifndef CPPFUSE_SINFOMIXIN_HPP
#define CPPFUSE_SINFOMIXIN_HPP

#include <CppFuse/Models/SInfo.hpp>

namespace cppfuse {

template<typename T>
struct SInfoMixin : SInfo {
    friend struct SInfo;

    template<typename... Args>
    static ASharedRwLock<T> New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent,
        Args&& ... args) {
        const auto obj = MakeSharedRwLock<T>();
        const auto objWrite = obj->Write();
        ASetName{}(objWrite, name);
        ASetMode{}(objWrite, mode);
        ASetUid{}(objWrite, getuid());
        ASetGid{}(objWrite, getgid());
        T::DoNew(objWrite, std::forward<Args>(args)...);
        ASetParent{}(objWrite, parent);
        return obj;
    }
};

}

#endif //CPPFUSE_SINFOMIXIN_HPP