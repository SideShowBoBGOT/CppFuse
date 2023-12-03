#include <CppFuse/Views/TFileSystemCLI.hpp>
#include <CppFuse/Views/TFileSystemClientCLI.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

#include <unistd.h>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

static const fs::path s_xMountPath = "/mnt/fuse";
static const std::string_view s_sTestFifo = "TestFifo";
static constexpr unsigned long s_uBufferSize = 1000;

class TFileSystemTestFixture : public ::testing::Test {
    protected:
    static void SetUpTestSuite() {
        mkfifo(s_xFifoPath.c_str(), 0775);
        s_pChildThread = std::make_unique<std::jthread>([fifoPath=s_xFifoPath]() {
            std::system((std::string("mount -t ") + s_xMountPath.c_str()).c_str());
            std::system((std::string("fusermount -u ") + s_xMountPath.c_str()).c_str());
            std::vector<const char*> args = { fs::current_path().c_str(), "-f", "-m", s_xMountPath.c_str(), "-p", fifoPath.c_str() };
            auto cli = cppfuse::TFileSystemCLI();
            CLI11_PARSE(cli, args.size(), const_cast<char**>(args.data()));
            return 0;
        });
        std::this_thread::sleep_for(300ms);
    }

    static void TearDownTestSuite() {
        s_pChildThread->detach();
    }

    protected:
    static fs::path s_xFifoPath;
    static std::unique_ptr<std::jthread> s_pChildThread;
};

std::unique_ptr<std::jthread> TFileSystemTestFixture::s_pChildThread = nullptr;
fs::path TFileSystemTestFixture::s_xFifoPath = fs::current_path() / s_sTestFifo;

TEST_F(TFileSystemTestFixture, RegularFile) {
    const auto filePath = s_xMountPath / fs::path("text.txt");
    std::ofstream(filePath.c_str()) << "information";
    EXPECT_TRUE(fs::is_regular_file(filePath));
    std::string r;
    std::ifstream(filePath.c_str()) >> r;
    EXPECT_EQ(r.find_first_of("information"), 0);
}

TEST_F(TFileSystemTestFixture, Link) {
    const auto filePath = s_xMountPath / fs::path("linked");
    std::ofstream(filePath.c_str());
    const auto linkPath = s_xMountPath / fs::path("link");
    fs::create_symlink(filePath, linkPath);
    EXPECT_TRUE(fs::is_symlink(linkPath));
    EXPECT_EQ(filePath, fs::read_symlink(linkPath));
}

TEST_F(TFileSystemTestFixture, Directory) {
    const auto dirPath = s_xMountPath / fs::path("dir");
    fs::create_directory(dirPath);
    EXPECT_TRUE(fs::is_directory(dirPath));
    const auto filePath = dirPath / fs::path("indirFile");
    {
        std::ofstream(filePath.c_str());
    }

    {
        SCOPED_TRACE("CheckFileInsideDirectory");
        const auto fileIt = fs::directory_iterator(dirPath);
        EXPECT_TRUE(fileIt->is_regular_file());
        EXPECT_EQ(fileIt->path().filename(), "indirFile");
        EXPECT_NE(fileIt, end(fileIt));
    }

    {
        SCOPED_TRACE("CheckDeleteFileInsideDirectory");
        fs::remove(filePath);
        const auto fileIt = fs::directory_iterator(dirPath);
        EXPECT_EQ(fileIt, end(fileIt));
    }
}

TEST_F(TFileSystemTestFixture, FindByName) {
    fs::create_directory(s_xMountPath / "bar");
    fs::create_directory(s_xMountPath / "bar/bar");
    fs::create_directory(s_xMountPath / "bar/bar/baz");
    fs::create_directory(s_xMountPath / "bar/bar/baz/bar");

    auto buffer = std::array<char, s_uBufferSize>();
    cppfuse::TFileSystemClientCLI::FindByName(s_xFifoPath, "bar", buffer);
    EXPECT_STREQ(buffer.data(), "/bar\n/bar/bar\n/bar/bar/baz/bar\n");
}

TEST_F(TFileSystemTestFixture, FileAccess) {
    const auto filePath = s_xMountPath / fs::path("accessFile");
    {
        auto f = std::ofstream(filePath.c_str());
    }
    {
        SCOPED_TRACE("AllPermissionGranted");
        fs::permissions(filePath, fs::perms::owner_all, fs::perm_options::add);
        const auto file = std::fstream(filePath.c_str(), std::ios::out | std::ios::in);
        EXPECT_TRUE(file.is_open());
        const auto perms = fs::status(filePath).permissions();
        EXPECT_EQ(perms & fs::perms::owner_read, fs::perms::owner_read);
        EXPECT_EQ(perms & fs::perms::owner_write, fs::perms::owner_write);
        EXPECT_EQ(perms & fs::perms::owner_exec, fs::perms::owner_exec);
    }
    {
        SCOPED_TRACE("WriteProtected");
        fs::permissions(filePath, fs::perms::owner_write, fs::perm_options::remove);
        EXPECT_EQ(fs::status(filePath).permissions() & fs::perms::owner_write, fs::perms::none);
        auto file = std::fstream(filePath.c_str(), std::ios::ate);
        EXPECT_FALSE(file.is_open());
    }
    {
        SCOPED_TRACE("ReadProtected");
        fs::permissions(filePath, fs::perms::owner_read, fs::perm_options::remove);
        EXPECT_EQ(fs::status(filePath).permissions() & fs::perms::owner_read, fs::perms::none);
        const auto file = std::fstream(filePath.c_str(), std::ios::in);
        EXPECT_FALSE(file.is_open());
    }
    {
        SCOPED_TRACE("ExecuteProtected");
        const auto cmdName = std::string("mkdir");
        const auto cmdPath = s_xMountPath / cmdName;
        fs::copy(fs::path("/bin") / cmdName, cmdPath);
        fs::permissions(cmdPath,
            fs::perms::owner_all | fs::perms::group_all | fs::perms::others_all,
            fs::perm_options::add);
        const auto cmdOne = std::string(".") + cmdPath.native() + " " + (s_xMountPath / "cmdDir1").c_str();
        EXPECT_EQ(std::system(cmdOne.c_str()), 0);
        fs::permissions(cmdPath,
            fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec,
            fs::perm_options::remove);
        EXPECT_EQ(fs::status(cmdPath).permissions() & fs::perms::owner_exec, fs::perms::none);
        const auto cmdTwo = std::string(".") + cmdPath.native() + " " + (s_xMountPath / "cmdDir2").c_str();
        EXPECT_EQ(std::system(cmdTwo.c_str()), 32256);
    }
}

TEST_F(TFileSystemTestFixture, DirectoryAccess) {
    const auto dirPath = s_xMountPath / fs::path("accessDirectory");
    fs::create_directory(dirPath);
    {
        SCOPED_TRACE("AllPermissionGranted");
        fs::permissions(dirPath, fs::perms::owner_all, fs::perm_options::add);
        const auto perms = fs::status(dirPath).permissions();
        EXPECT_EQ(perms & fs::perms::owner_read, fs::perms::owner_read);
        EXPECT_EQ(perms & fs::perms::owner_write, fs::perms::owner_write);
        EXPECT_EQ(perms & fs::perms::owner_exec, fs::perms::owner_exec);
        const auto testFileOnePath = dirPath / "accessDirectoryTestFileOne";
        auto file = std::ofstream(testFileOnePath);
        EXPECT_TRUE(fs::exists(testFileOnePath.c_str()));
        auto it = fs::directory_iterator(dirPath);
        EXPECT_EQ(std::distance(it, fs::end(it)), 1);
    }
    {
        SCOPED_TRACE("WriteProtected");
        fs::permissions(dirPath, fs::perms::owner_write, fs::perm_options::remove);
        EXPECT_EQ(fs::status(dirPath).permissions() & fs::perms::owner_write, fs::perms::none);
        const auto testFileTwoPath = dirPath / "accessDirectoryTestFileTwo";
        auto file = std::ofstream(testFileTwoPath);
        EXPECT_FALSE(file.is_open());
    }
    {
        SCOPED_TRACE("ReadProtected");
        fs::permissions(dirPath, fs::perms::owner_read, fs::perm_options::remove);
        EXPECT_EQ(fs::status(dirPath).permissions() & fs::perms::owner_read, fs::perms::none);
        const auto file = std::fstream(dirPath.c_str(), std::ios::in);
        auto isCaughtError = false;
        try {
            auto it = fs::directory_iterator(dirPath);
        } catch(const fs::filesystem_error& ex) {
            isCaughtError = true;
        }
        EXPECT_TRUE(isCaughtError);
    }
    {
        SCOPED_TRACE("ExecuteProtected");
        fs::permissions(dirPath, fs::perms::owner_exec, fs::perm_options::remove);
        EXPECT_EQ(fs::status(dirPath).permissions() & fs::perms::owner_exec, fs::perms::none);
    }
}

//TEST_F(TFileSystemTestFixture, LinkAccess) {
//    const auto filePath = s_xMountPath / "accessLinkFile";
//
//    const auto linkPath = s_xMountPath / "accessLink";
//    fs::create_symlink(filePath, linkPath);
//
//}