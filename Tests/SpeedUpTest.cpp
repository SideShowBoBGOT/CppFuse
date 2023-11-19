#include <CppFuse/Views/TFileSystemCLI.hpp>
#include <chrono>
#include <thread>
#include <filesystem>

namespace fs = std::filesystem;

static const fs::path s_xMountPath = "/mnt/fuse";

size_t WriteToFile(const std::filesystem::path& path, unsigned size) {
    const std::vector<char> v(size);
    const auto start = std::chrono::system_clock::now();
    auto file = std::ofstream(path, std::ios::ate);
    file.seekp(0);
    file.write(v.data(), v.size());
    const auto duration = std::chrono::system_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

size_t ReadFromFile(const std::filesystem::path& path, unsigned size) {
    const auto start = std::chrono::system_clock::now();
    auto file = std::ifstream(path);
    auto v = std::vector<char>(size);
    file.read(v.data(), v.size());
    const auto duration = std::chrono::system_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

int main() {
    using namespace std::chrono_literals;
    auto t = std::jthread([]() {
        std::system((std::string("mount -t ") + s_xMountPath.c_str()).c_str());
        std::system((std::string("fusermount -u ") + s_xMountPath.c_str()).c_str());
        std::vector<const char*> args = { fs::current_path().c_str(), "-f", "-m", s_xMountPath.c_str() };
        auto cli = cppfuse::TFileSystemCLI("CppFuse");
        CLI11_PARSE(cli, args.size(), const_cast<char**>(args.data()));
    });
    std::this_thread::sleep_for(300ms);

    std::vector<std::pair<size_t, size_t>> writesFuse;
    std::vector<std::pair<size_t, size_t>> writes;
    std::vector<std::pair<size_t, size_t>> readsFuse;
    std::vector<std::pair<size_t, size_t>> reads;

    for(auto size : {100, 200, 500, 800, 1000, 2000, 2500, 3000, 3500, 4000, 5000}) {
        std::ofstream("/home/sideshowbobgot/university/text.txt");
        std::ofstream("/mnt/fuse/text.txt");

        const auto writeTime = WriteToFile("/home/sideshowbobgot/university/text.txt", size);
        const auto fuseWriteTime = WriteToFile("/mnt/fuse/text.txt", size);

        writesFuse.emplace_back(size, fuseWriteTime);
        writes.emplace_back(size, writeTime);

        const auto readTime = ReadFromFile("/home/sideshowbobgot/university/text.txt", size);
        const auto fuseReadTime = ReadFromFile("/mnt/fuse/text.txt", size);

        readsFuse.emplace_back(size, fuseReadTime);
        reads.emplace_back(size, readTime);

        fs::remove("/home/sideshowbobgot/university/text.txt");
        fs::remove("/mnt/fuse/text.txt");
    }



    t.detach();
    return 0;
}