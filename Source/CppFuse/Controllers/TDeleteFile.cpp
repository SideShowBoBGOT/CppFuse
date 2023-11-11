#include <CppFuse/Controllers/TDeleteFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>

namespace cppfuse {

void TDeleteFile::operator()(const ASharedFileVariant& var) { std::visit(*this, var); }

void TDeleteFile::operator()(const ASharedRwLock<TDirectory>& var) {
    auto parentDirWrite = parentDir->Write();
    auto& objs = parentDirWrite->Objects;
    objs.erase(std::remove_if(objs.begin(), objs.end(),
        [name=objPath.filename().c_str()](const auto& child) {
            return name == TGetInfoName{}(child);
        }
    ), objs.end());
}

static void DeleteNotDirectory(const auto& var) {

}

void TDeleteFile::operator()(const ASharedRwLock<TRegularFile>& var) {
    auto varWrite = var->Write();
    auto parent = TGetInfoParent{}(varWrite).lock()->Write();

}

void TDeleteFile::operator()(const ASharedRwLock<TLink>& var) {

}

}
