#ifndef CPPFUSE_SINFOMIXIN_HPP
#define CPPFUSE_SINFOMIXIN_HPP

#include <CppFuse/Models/Objects/SInfo.hpp>
#include <CppFuse/Models/Operations/TSetInfoParameter.hpp>
#include <CppFuse/Models/Operations/TGetInfoParameter.hpp>

namespace cppfuse {

template<typename T>
struct SInfoMixin : SInfo {
    friend struct SInfo;

    template<typename... Args>
    static ASharedRwLock<T> New(const std::string& name, mode_t mode, const ASharedRwLock<SDirectory>& parent,
        Args&& ... args) {
        const auto obj = MakeSharedRwLock<T>();
        const auto objWrite = obj->Write();
        TSetInfoName{name}(objWrite);
        TSetInfoMode{mode}(objWrite);
        TSetInfoUid{getuid()}(objWrite);
        TSetInfoGid{getgid()}(objWrite);
        T::DoNew(objWrite, std::forward<Args>(args)...);
        TSetInfoParent{parent}(objWrite);
        return obj;
    }
};

}

#endif //CPPFUSE_SINFOMIXIN_HPP