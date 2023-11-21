#include <CLI/CLI.hpp>

int main(int argc, char *argv[]) {
    auto pipePath = std::filesystem::path();
    auto fileName = std::string();
    auto cli = CLI::App("FindByName");
    cli.add_option("--pipe-point,-p", pipePath, "Pipe point")
        ->required(true)->check(CLI::ExistingFile);
    cli.add_option("--file-name,-f", fileName, "File name")
        ->required(true);
    cli.parse_complete_callback([&pipePath, &fileName]() {
        {
            auto fOut = std::ofstream(pipePath);
            if(!fOut.is_open()) {
                throw std::invalid_argument("Can not open the pipe");
            }
            fOut << fileName;
        }
        {
            auto buffer = std::array<char, 10000>();
            auto fIn = std::ifstream(pipePath);
            if(!fIn.is_open()) {
                throw std::invalid_argument("Can not open the pipe");
            }
            fIn.read(buffer.data(), buffer.size());
            auto str = std::string_view(buffer.data());
            std::cout << str << "\n";
        }
    });
    CLI11_PARSE(cli, argc, argv);
    return 0;
}
