#include <CppFuse/Controllers/TFileSystem.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>
#include <CppFuse/Controllers/NSFileAttributes.hpp>
#include <CppFuse/Controllers/TSetFileParameter.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>
#include <CppFuse/Controllers/TReadDirectory.hpp>
#include <CppFuse/Controllers/NSDeleteFile.hpp>
#include <CppFuse/Errors/TFSException.hpp>

#include <thread>
#include <cstring>
#include <iostream>
#include <span>
#include <fstream>

namespace cppfuse {

static constexpr std::string_view s_sRootPath = "/";
static constexpr unsigned s_uCommunicationBufferSize = 1000;
static constexpr std::string_view s_sNoFilesWithSuchName = "No files with such name\n";

ASharedRwLock<TDirectory> TFileSystem::s_pRootDir = TDirectory::New(s_sRootPath.data(), static_cast<mode_t>(0777), nullptr);
fs::path TFileSystem::FifoPath = "";

int TFileSystem::Init(int argc, char *argv[]) {
    fuse_operations FileSystemOperations = {
        .getattr = GetAttr,
        .readlink = ReadLink,
        .mknod = MkNod,
        .mkdir = MkDir,
        .unlink = Unlink,
        .rmdir = RmDir,
        .symlink = SymLink,
        .chmod = ChMod,
        .read = Read,
        .write = Write,
        .opendir = OpenDir,
        .readdir = ReadDir,
        .access = Access
    };
    auto fifoCommunicationThread = std::jthread(TFileSystem::FindByNameThread);
    return fuse_main(argc, argv, &FileSystemOperations, nullptr);
}

int TFileSystem::GetAttr(const char* path, struct stat* st, struct fuse_file_info* fi) {
    try {
        const auto result = NSFindFile::Find(path);
        NSFileAttributes::Get(result, st);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ReadLink(const char* path, char* buffer, size_t size) {
    try {
        const auto link = NSFindFile::FindLink(path);
        const auto linkRead = link->Read();
        const auto pathView = std::string_view(linkRead->LinkTo.c_str());
        std::memcpy(buffer, pathView.data(), pathView.size());
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::MkNod(const char* path, mode_t mode, dev_t rdev) {
    try {
        const auto newPath = std::filesystem::path(path);
        auto parentDir = NSFindFile::FindDir(newPath.parent_path());
        TRegularFile::New(newPath.filename(), mode, parentDir);
        NSFindFile::AddToNameHash(newPath);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::MkDir(const char* path, mode_t mode) {
    try {
        const auto newPath = std::filesystem::path(path);
        auto parentDir = NSFindFile::FindDir(newPath.parent_path());
        TDirectory::New(newPath.filename(), mode, parentDir);
        NSFindFile::AddToNameHash(newPath);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Unlink(const char* path) {
    try {
        NSDeleteFile::Delete(path);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::RmDir(const char* path) {
    try {
        NSDeleteFile::Delete(path);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::SymLink(const char* target_path, const char* link_path) {
    try {
        const auto newPath = std::filesystem::path(link_path);
        const auto parentDir = NSFindFile::FindDir(newPath.parent_path());
        TLink::New(newPath.filename(), static_cast<mode_t>(0775), parentDir, target_path);
        NSFindFile::AddToNameHash(newPath);
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ChMod(const char* path, mode_t mode, struct fuse_file_info* fi) {
    try {
        const auto var = NSFindFile::Find(path);
        TSetInfoMode{mode}(var);
    } catch(const TFSException& ex) {
        return ex.Type();
    }
    return 0;
}

//int TFileSystem::Open(const char* path, struct fuse_file_info* info) {
//    try {
//        const auto var = NSFindFile::FindRegularFile(path);
//        auto mode = 0;
//        if(info->flags & O_WRONLY) mode |= W_OK;
//        if(info->flags & O_RDONLY) mode |= R_OK;
//        if(info->flags & O_RDWR) mode |= W_OK | R_OK;
//        return static_cast<int>(TGetInfoMode{}(var)) & mode ? 0 : NFSExceptionType::AccessNotPermitted;
//    } catch(const TFSException& ex) {
//        return ex.Type();
//    }
//    return 0;
//}

int TFileSystem::Read(const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    try {
        auto file = NSFindFile::FindRegularFile(path);
        const auto fileRead = file->Read();
        const auto& data = fileRead->Data;
        const auto offsetSize = static_cast<size_t>(data.end() - (data.begin() + offset));
        const auto readSize = std::min(offsetSize, size);
        std::memcpy(buffer, fileRead->Data.data() + offset, readSize);
        return static_cast<int>(readSize);
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Write(const char* path, const char* buffer, size_t size, off_t offset, struct fuse_file_info* info) {
    try {
        auto file = NSFindFile::FindRegularFile(path);
        auto fileWrite = file->Write();
        auto& data = fileWrite->Data;
        const auto src = std::span(buffer, size);
        if(info->flags & O_WRONLY) {
            const auto replaceSize = static_cast<size_t>(data.end() - (data.begin() + offset));
            if(replaceSize < size) {
                data.resize(data.size() + size - replaceSize);
            }
            std::copy(src.begin(), src.end(), data.begin() + offset);
        } else if(info->flags & O_APPEND) {
            data.insert(data.begin() + offset, src.begin(), src.end());
        }
        return static_cast<int>(size);
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::OpenDir(const char* path, struct fuse_file_info* info) {
    try {
        const auto var = NSFindFile::FindDir(path);
        return static_cast<int>(TGetInfoMode{}(var)) & R_OK ? 0 : NFSExceptionType::AccessNotPermitted;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::ReadDir(const char* path, void* buffer, fuse_fill_dir_t filler, off_t offset,
    struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    try {
        TReadDirectory{path, buffer, filler}();
        return 0;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

int TFileSystem::Access(const char* path, int mode) {
    try {
        const auto var = NSFindFile::Find(path);
        return static_cast<int>(TGetInfoMode{}(var)) & mode ? 0 : NFSExceptionType::AccessNotPermitted;
    } catch(const TFSException& ex) {
        return ex.Type();
    }
}

const ASharedRwLock<TDirectory>& TFileSystem::RootDir() { return s_pRootDir; }

void TFileSystem::FindByNameThread() {
    auto buffer = std::array<char, s_uCommunicationBufferSize>();
    while(true) {
        {
            auto fIn = std::ifstream(FifoPath);
            if(!fIn.is_open()) {
                continue;
            }
            fIn.read(buffer.data(), buffer.size());
        }
        const auto path = std::string(buffer.data());
        try {
            const auto& paths = NSFindFile::FindByName(path);
            auto fOut = std::ofstream(FifoPath);
            if(!fOut.is_open()) {
                continue;
            }
            for(const auto& p : paths) {
                fOut << p.native() << "\n";
            }
        } catch(const TFSException& ex) {
            auto fOut = std::ofstream(FifoPath);
            if(fOut.is_open()) {
                fOut << s_sNoFilesWithSuchName;
            }
        }
    }
}

}