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
    std::ofstream(filePath.c_str());

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