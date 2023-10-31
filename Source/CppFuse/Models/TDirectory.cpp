#include <CppFuse/Models/TDirectory.hpp>

#include <algorithm>
#include <array>

namespace cppfuse {

static constexpr std::string_view s_sEmptyName = "";
static constexpr std::string_view s_sSelfName = ".";
static constexpr std::string_view s_sParentName = "..";

cppfuse::TDirectory::TDirectory(const std::string& name, mode_t mode, const ASharedRwLock<TDirectory>& parent)
    : TFileObjectMixin<TDirectory, NFileType::Directory>(name, mode, parent) {}

const std::vector<ASharedFileVariant>& TDirectory::FileObjects() const { return m_vObjects; }

AFSExpected<ASharedFileVariant> TDirectory::Find(const AStdPath& path) const {
    return RecursiveFind(path, path.begin());
}

AFSExpected<ASharedFileVariant> TDirectory::RecursiveFind(const AStdPath& path, AStdPathIt it) const {
    const auto ownName = std::string_view(Name());
    const auto itName = std::string_view(it->c_str());
    const auto selfNames = std::array{s_sSelfName, s_sEmptyName, ownName};

    if(std::ranges::contains(selfNames, itName)) {

        continue;
    }
}

}
