#include <CppFuse/Controllers/TFileSystem.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

static const fs::path s_xMountPath = "/mnt/fuse";
static const fs::path s_xExecutablePath = "";

class TFileSystemTestFixture : public ::testing::Test {
    protected:
    static void SetUpTestSuite() {
        s_pChildThread = std::make_unique<std::jthread>([]() {
            std::system((std::string("mount -t ") + s_xMountPath.c_str()).c_str());
            std::system((std::string("fusermount -u ") + s_xMountPath.c_str()).c_str());
            std::vector<const char*> args = { fs::current_path().c_str(), "-f", s_xMountPath.c_str() };
            cppfuse::TFileSystem::Init(static_cast<int>(args.size()), const_cast<char**>(args.data()));
        });
        std::this_thread::sleep_for(300ms);
    }

    static void TearDownTestSuite() {
        s_pChildThread->detach();
    }

    protected:
    static std::unique_ptr<std::jthread> s_pChildThread;
};

std::unique_ptr<std::jthread> TFileSystemTestFixture::s_pChildThread = nullptr;

TEST_F(TFileSystemTestFixture, CreateRegularFile) {
    const auto filePath = s_xMountPath / fs::path("text.txt");
    std::ofstream(filePath.c_str());
    EXPECT_TRUE(fs::is_regular_file(filePath));
}

TEST_F(TFileSystemTestFixture, CreateLink) {
    const auto filePath = s_xMountPath / fs::path("linked");
    std::ofstream(filePath.c_str());
    const auto linkPath = s_xMountPath / fs::path("link");
    fs::create_symlink(filePath, linkPath);
    EXPECT_TRUE(fs::is_symlink(linkPath));
}

TEST_F(TFileSystemTestFixture, CreateDirectory) {
    const auto filePath = s_xMountPath / fs::path("dir");
    fs::create_directory(filePath);
    EXPECT_TRUE(fs::is_directory(filePath));
}

TEST_F(TFileSystemTestFixture, WriteReadFile) {
    const auto filePath = s_xMountPath / fs::path("writeText.txt");
    std::ofstream(filePath.c_str()) << "information";
    std::string r;
    std::ifstream(filePath.c_str()) >> r;
    EXPECT_EQ(r.find_first_of("information"), 0);
}