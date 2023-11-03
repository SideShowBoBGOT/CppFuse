#ifndef CPPFUSE_TFINDER_HPP
#define CPPFUSE_TFINDER_HPP

#include <CppFuse/Models/ASharedFileVariant.hpp>
#include <CppFuse/Errors/TFSException.hpp>

namespace cppfuse {

class TFinder {
    public:
    static AFSExpected<ASharedFileVariant> Find(const AStdPath& path);
    static AFSExpected<ASharedRwLock<TDirectory>> FindDir(const AStdPath& path);
    static AFSExpected<ASharedRwLock<TLink>> FindLink(const AStdPath& path);
    static AFSExpected<ASharedRwLock<TFile>> FindFile(const AStdPath& path);

    protected:
    template<typename T, auto FSExceptionValue>
    static AFSExpected<ASharedRwLock<T>> FindGeneral(const AStdPath& path);

    protected:
    static AFSExpected<ASharedFileVariant> RecursiveFindStepOne(const AStdPath& path, const AStdPathIt& it,
        const ASharedRwLock<TDirectory>& dir);
    static AFSExpected<ASharedFileVariant> RecursiveFindStepTwo(const AStdPath& path, AStdPathIt it,
        const ASharedFileVariant& obj);

};

template<typename T, auto FSExceptionValue>
AFSExpected<ASharedRwLock<T>> TFinder::FindGeneral(const AStdPath& path) {
    const auto result = Find(path);
    if(!result) return std::unexpected(result.error());
    if(const auto t = std::get_if<ASharedRwLock<T>>(&result.value())) {
        return *t;
    }
    return std::unexpected(TFSException(path.begin(), path.end(), FSExceptionValue));
}

}

#endif //CPPFUSE_TFINDER_HPP
