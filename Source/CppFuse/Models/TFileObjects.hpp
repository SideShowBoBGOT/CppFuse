#ifndef CPPFUSE_TFILEOBJECTS_HPP
#define CPPFUSE_TFILEOBJECTS_HPP

#include <CppFuse/Models/TFile.hpp>
#include <CppFuse/Models/NNFileType.hpp>

#include <variant>
#include <vector>
#include <filesystem>

namespace cppfuse {

class TDirectory;
class TRegularFile;
class TLink;

using ASharedFileVariant = std::variant<
    ASharedRwLock<TDirectory>,
    ASharedRwLock<TRegularFile>,
    ASharedRwLock<TLink>>;

template<typename T>
concept CFileObject = std::same_as<T, TDirectory>
    || std::same_as<T, TRegularFile>
    || std::same_as<T, TLink>;

template<typename T>
concept CReadGuardFileObject = std::same_as<T, rwl::TRwLockReadGuard<TDirectory>>
    || std::same_as<T, rwl::TRwLockReadGuard<TRegularFile>>
    || std::same_as<T, rwl::TRwLockReadGuard<TLink>>;

template<typename T>
concept CWriteGuardFileObject = std::same_as<T, rwl::TRwLockWriteGuard<TDirectory>>
    || std::same_as<T, rwl::TRwLockWriteGuard<TRegularFile>>
    || std::same_as<T, rwl::TRwLockWriteGuard<TLink>>;

template<typename T>
concept CGuardFileObject = CReadGuardFileObject<T> || CWriteGuardFileObject<T>;

template<typename T>
concept CSharedRwFileObject = std::same_as<T, ASharedRwLock<TDirectory>>
    || std::same_as<T, ASharedRwLock<TRegularFile>>
    || std::same_as<T, ASharedRwLock<TLink>>;

class TDirectory : public TFile<TDirectory> {
    public:
    TDirectory()=default;
    static ASharedRwLock<TDirectory> New(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent);

    public:
    std::vector<ASharedFileVariant> Files;
    static constexpr NFileType FileType = NFileType::Directory;
};

class TRegularFile : public TFile<TDirectory> {
    public:
    TRegularFile()=default;
    static ASharedRwLock<TRegularFile> New(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent);

    public:
    std::vector<char> Data;
    static constexpr NFileType FileType = NFileType::File;
};

namespace fs = std::filesystem;

class TLink : TFile<TDirectory> {
    public:
    TLink()=default;
    static ASharedRwLock<TLink> New(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent, const fs::path& path);

    public:
    fs::path LinkTo;
    static constexpr NFileType FileType = NFileType::Link;
};

}

#endif //CPPFUSE_TFILEOBJECTS_HPP
