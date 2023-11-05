#ifndef CPPFUSE_SINFOMIXIN_HPP
#define CPPFUSE_SINFOMIXIN_HPP

#include <CppFuse/Models/Objects/SInfo.hpp>
#include <CppFuse/Models/Operations/SSetParameter.hpp>
#include <CppFuse/Models/Operations/SGetParameter.hpp>

namespace cppfuse {

template<typename T>
struct SInfoMixin : SInfo {
    friend struct SInfo;

    template<typename... Args>
    static ASharedRwLock<T> New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent,
        Args&& ... args) {
        const auto obj = MakeSharedRwLock<T>();
        const auto objWrite = obj->Write();
        ASetName{name}(objWrite);
        ASetMode{mode}(objWrite);
        ASetUid{getuid()}(objWrite);
        ASetGid{getgid()}(objWrite);
        T::DoNew(objWrite, std::forward<Args>(args)...);
        ASetParent{parent}(objWrite);
        return obj;
    }
};

}

#endif //CPPFUSE_SINFOMIXIN_HPP