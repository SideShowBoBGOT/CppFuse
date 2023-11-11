#include <CppFuse/Controllers/TDeleteFile.hpp>
#include <CppFuse/Controllers/TGetFileParameter.hpp>
#include <CppFuse/Controllers/TFindFile.hpp>

namespace cppfuse {

void TDeleteFile::operator()(const char* path) {
//    const auto var = TFindFile::Find(path);
//    std::visit([this](const auto& obj) {  }, var);
}

void TDeleteFile::Delete(const ASharedRwLock<TDirectory>& var) {
//    auto parentDirWrite = parentDir->Write();
//    auto& objs = parentDirWrite->Objects;
//    objs.erase(std::remove_if(objs.begin(), objs.end(),
//        [name=objPath.filename().c_str()](const auto& child) {
//            return name == TGetInfoName{}(child);
//        }
//    ), objs.end());
}

static void DeleteNotDirectory(const auto& var) {

}

void TDeleteFile::Delete(const ASharedRwLock<TRegularFile>& var) {
//    auto varWrite = var->Write();
//    auto parent = TGetInfoParent{}(varWrite).lock()->Write();


}

void TDeleteFile::Delete(const ASharedRwLock<TLink>& var) {

}



}
