#include <chrono>
#include <filesystem>
#include <fstream>

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
    auto v = std::vector<char>(size);

    const auto start = std::chrono::system_clock::now();
    auto file = std::ifstream(path);
    file.read(v.data(), v.size());
    const auto duration = std::chrono::system_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

int main() {
    fs::remove("/home/sideshowbobgot/university/CppFuse/SpeedUp.csv");
    auto speedUpCSV = std::ofstream("/home/sideshowbobgot/university/CppFuse/SpeedUp.csv");
    speedUpCSV << "writeFuse,writeGeneral,writeSpeedUp,readFuse,readGeneral,readSpeedUp\n";

    for(auto size : {100, 200, 500, 800, 1000, 2000, 2500, 3000, 3500, 4000, 5000}) {
        std::ofstream("/home/sideshowbobgot/university/text.txt");
        std::ofstream("/mnt/fuse/text.txt");

        const double writeTime = WriteToFile("/home/sideshowbobgot/university/text.txt", size);
        const double fuseWriteTime = WriteToFile("/mnt/fuse/text.txt", size);

        const double readTime = ReadFromFile("/home/sideshowbobgot/university/text.txt", size);
        const double fuseReadTime = ReadFromFile("/mnt/fuse/text.txt", size);

        fs::remove("/home/sideshowbobgot/university/text.txt");
        fs::remove("/mnt/fuse/text.txt");

        speedUpCSV << std::to_string(fuseWriteTime) + "," + std::to_string(writeTime)
            + "," + std::to_string(double(writeTime) / fuseWriteTime)
            + "," + std::to_string(fuseReadTime) + "," + std::to_string(readTime)
            + "," + std::to_string(double(readTime) / fuseReadTime) + "\n";
    }

    return 0;
}