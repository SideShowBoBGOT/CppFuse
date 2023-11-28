#include <CppFuse/Views/TFileSystemCLI.hpp>
#include <CppFuse/Controllers/NSFindFile.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

#include <unistd.h>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

static const fs::path s_xMountPath = "/mnt/fuse";
static const fs::path s_xTestFolderPath = "/home/sideshowbobgot/testFolder";
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

        CreateDirectoriesRecursively(0, s_xMountPath);
        fs::create_directory(s_xTestFolderPath);
        CreateDirectoriesRecursively(0, s_xTestFolderPath);
    }

    protected:
    static constexpr unsigned s_uMaxDepth = 4;
    static void CreateDirectoriesRecursively(const unsigned depth, const fs::path& path) {
        if(s_uMaxDepth == depth) return;
        for(auto i = 'A'; i <= 'Z'; ++i) {
            const auto nextPath = path / (std::string() + i);
            fs::create_directory(nextPath);
            CreateDirectoriesRecursively(depth + 1, nextPath);
        }
    }

    static void TearDownTestSuite() {
        fs::remove_all(s_xTestFolderPath);
        s_pChildThread->detach();
    }

    protected:
    static fs::path s_xFifoPath;
    static std::unique_ptr<std::jthread> s_pChildThread;
};

std::unique_ptr<std::jthread> TFileSystemTestFixture::s_pChildThread = nullptr;
fs::path TFileSystemTestFixture::s_xFifoPath = fs::current_path() / s_sTestFifo;


// 3 702
// 4 18279
TEST_F(TFileSystemTestFixture, FindFileTimeVFS) {
    const auto& set = cppfuse::NSFindFile::FindByName("H");
    EXPECT_EQ(set.size(), 18279);
    for(const auto& p : set) {
        EXPECT_EQ(p.filename(), "H");
    }
}

TEST_F(TFileSystemTestFixture, FindFileTimeGeneralFS) {
    const auto count = std::ranges::count_if(fs::recursive_directory_iterator(s_xTestFolderPath),
        [](const auto& entry) { return entry.path().filename() == "H"; });
    EXPECT_EQ(count, 18279);
}
