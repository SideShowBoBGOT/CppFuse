#ifndef CPPFUSE_TFILEOBJECTS_HPP
#define CPPFUSE_TFILEOBJECTS_HPP

#include <CppFuse/Models/Objects/TInfo.hpp>
#include <CppFuse/Models/Objects/NNFileType.hpp>

#include <variant>
#include <vector>
#include <filesystem>

namespace cppfuse {

class TDirectory;
class TFile;
class TLink;

using ASharedFileVariant = std::variant<
    ASharedRwLock<TDirectory>,
    ASharedRwLock<TFile>,
    ASharedRwLock<TLink>
>;

template<typename T>
concept CFileObject = std::is_same_v<T, TDirectory> || std::is_same_v<T, TFile> || std::is_same_v<T, TLink>;

template<typename T>
concept CReadGuardFileObject = std::is_same_v<T, rwl::TRwLockReadGuard<TDirectory>>
    || std::is_same_v<T, rwl::TRwLockReadGuard<TFile>>
    || std::is_same_v<T, rwl::TRwLockReadGuard<TLink>>;

template<typename T>
concept CWriteGuardFileObject = std::is_same_v<T, rwl::TRwLockWriteGuard<TDirectory>>
    || std::is_same_v<T, rwl::TRwLockWriteGuard<TFile>>
    || std::is_same_v<T, rwl::TRwLockWriteGuard<TLink>>;

template<typename T>
concept CGuardFileObject = CReadGuardFileObject<T> || CWriteGuardFileObject<T>;

template<typename T>
concept CSharedRwFileObject = std::is_same_v<T, ASharedRwLock<TDirectory>>
    || std::is_same_v<T, ASharedRwLock<TFile>> || std::is_same_v<T, ASharedRwLock<TLink>>;

class TDirectory : public TInfo<TDirectory> {
    public:
    TDirectory()=default;
    static ASharedRwLock<TDirectory> New(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent);

    public:
    std::vector<ASharedFileVariant> Objects;
    static constexpr NFileType FileType = NFileType::Directory;
};

class TFile : public TInfo<TDirectory> {
    public:
    TFile()=default;
    static ASharedRwLock<TFile> New(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent);

    public:
    std::vector<char> Data;
    static constexpr NFileType FileType = NFileType::File;
};

class TLink : TInfo<TDirectory> {
    public:
    TLink()=default;
    static ASharedRwLock<TLink> New(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent, const char* path);

    public:
    std::filesystem::path LinkTo;
    static constexpr NFileType FileType = NFileType::Link;
};

}

#endif //CPPFUSE_TFILEOBJECTS_HPP
