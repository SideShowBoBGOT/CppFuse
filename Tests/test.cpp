#include <CppFuse/Controllers/TFileSystem.hpp>
#include <gtest/gtest.h>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

static constexpr std::string_view s_sMountFuse = "mount -t /mnt/fuse";
static constexpr std::string_view s_sMountFuseScript = "fusermount -u /mnt/fuse";

TEST(TestTopic, TrivialTest) {
    const auto fuseThread = std::jthread([]() {
        std::system(s_sMountFuse.data());
        std::system(s_sMountFuseScript.data());
        std::vector<const char*> fuseArgs = {
            fs::current_path().c_str(),
            "-f", "-s", "/mnt/fuse"
        };
        cppfuse::TFileSystem::Init(static_cast<int>(fuseArgs.size()), const_cast<char**>(fuseArgs.data()));
    });
    //EXPECT_EQ(1, 0);
}