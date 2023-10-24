#include "TDirectory.hpp"
#include <algorithm>
#include <array>

namespace cppfuse {

static const std::string_view s_sEmptyName = "";
static const std::string_view s_sSelfName = ".";
static const std::string_view s_sParentName = "..";

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode, const rppsync::TSharedRw<TDirectory>& parent)
    : TFileObject(name, mode, parent) {}

NFileType TDirectory::Type() const { return NFileType::Directory; }

const std::vector<rppsync::TSharedRw<TFileObject>>& TDirectory::Objects() const { return m_vObjects; }

TFSExpected<rppsync::TSharedRw<TFileObject>> TDirectory::Find(const std::filesystem::path& path) const {
//    const auto ownName = std::string_view(Name());
//    for(auto it = path.begin(); it!=path.end(); ++it) {
//        const auto itName = std::string_view();
//        const auto selfNames = std::array{s_sSelfName, s_sEmptyName, ownName};
//        if(std::ranges::contains(selfNames, itName)) {
//
//            continue;
//        }
//
//
//
//    }
//
//    for(auto it = ++path.begin(); it != path.end(); ++it) {
//        const auto nameStr = std::string_view(it->c_str());
//        if(nameStr == s_sSelfPath) {
//            return tempDir;
//        }
//        const auto objIt = std::ranges::find_if(tempDir->FileVariants,
//            [&nameStr](const TStFileVariant& var) {
//                return std::visit([&nameStr](const auto& obj) {
//                    return obj->Info.Name == nameStr;
//                }, var);
//            }
//        );
//        if(objIt == tempDir->FileVariants.end()) {
//            return std::unexpected(TFileObjectNotExistException(path.begin(), it));
//        }
//        if(std::distance(it, path.end()) == 1) {
//            return *objIt;
//        }
//        if(const auto t = std::get_if<TStDirectory>(&*objIt)) {
//            tempDir = *t;
//            continue;
//        }
//        return std::unexpected(TNotDirectoryException(path.begin(), it));
//    }
    //return cppfuse::TFSExpected<rppsync::TSharedRw<TFileObject>>();
}




}
