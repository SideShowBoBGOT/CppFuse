#ifndef CPPFUSE_TFILE_HPP
#define CPPFUSE_TFILE_HPP

#include <CppFuse/Models/TDirectory.hpp>

namespace cppfuse {

class TFile : public TFileObjectMixin<TDirectory, NFileType::File> {
    public:
    TFile(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent);

    public:
    std::vector<char>& Content();
    const std::vector<char>& Content() const;

    protected:
    std::vector<char> m_vContent;
};

}




#endif //CPPFUSE_TFILE_HPP
