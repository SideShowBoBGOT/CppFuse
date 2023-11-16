#include <CppFuse/Controllers/TFileSystem.hpp>
#include <gtest/gtest.h>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

static const std::string s_sShellCommand = "sh";
static const std::string s_sMountFuseScript = "MountFuse.sh";

static constexpr std::string_view s_sFuseArgs = "-f -s -d /mnt/fuse";
static constexpr int s_iFuseArgv = 5;

TEST(TestTopic, TrivialTest) {
    fs::current_path("../..");
    std::cout << fs::current_path() << std::endl;
    const auto fuseThread = std::jthread([]() {
        std::system((s_sShellCommand + " " + s_sMountFuseScript).c_str());


    });
    EXPECT_EQ(1, 0);
}