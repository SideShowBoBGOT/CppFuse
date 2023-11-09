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
concept CFileObject = std::same_as<T, TDirectory> || std::same_as<T, TFile> || std::same_as<T, TLink>;

template<typename T>
concept CReadGuardFileObject = std::same_as<T, rwl::TRwLockReadGuard<TDirectory>>
    || std::same_as<T, rwl::TRwLockReadGuard<TFile>>
    || std::same_as<T, rwl::TRwLockReadGuard<TLink>>;

template<typename T>
concept CWriteGuardFileObject = std::same_as<T, rwl::TRwLockWriteGuard<TDirectory>>
    || std::same_as<T, rwl::TRwLockWriteGuard<TFile>>
    || std::same_as<T, rwl::TRwLockWriteGuard<TLink>>;

template<typename T>
concept CGuardFileObject = CReadGuardFileObject<T> || CWriteGuardFileObject<T>;

template<typename T>
concept CSharedRwFileObject = std::same_as<T, ASharedRwLock<TDirectory>>
    || std::same_as<T, ASharedRwLock<TFile>> || std::same_as<T, ASharedRwLock<TLink>>;

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
