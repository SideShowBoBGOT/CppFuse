#ifndef CPPFUSE_SINFO_HPP
#define CPPFUSE_SINFO_HPP

#include <CppFuse/Models/TGetParameter.hpp>
#include <CppFuse/Models/TSetParameter.hpp>

namespace cppfuse {

// https://www.gnu.org/software/libc/manual/html_node/Attribute-Meanings.html
struct SInfo {
    friend AGetName;
    friend AGetMode;
    friend AGetParent;
    friend AGetUid;
    friend AGetGid;
    friend ASetName;
    friend ASetMode;
    friend ASetParent;
    friend ASetUid;
    friend ASetGid;

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    // ino_t st_ino is not implemented;
    // dev_t st_dev is not implemented;
    // st_nlink is the use_count of std::shared_ptr, so there is no need to keep the track of hard links;
    uid_t m_uUid = 0; // user's id;
    gid_t m_uGid = 0; // group's id a user belongs to;
    // off_t st_size is the size of file a.k.a Data.size(), and is the length of soft link a.k.a std::string_view(LinkTo.data()).size();

    // It was decided not to have time attributes, because it will cause a lot of synchronization issues.
    // Take "rename" operation, for example( https://www.gnu.org/software/libc/manual/html_node/File-Times.html ):
    //      " Renaming a file with rename affects only the attribute change time and modification time fields of the
    //      two parent directories involved, and not the times for the file being renamed. "

    // time_t ATime = 0; // Last access time to the file;
    // time_t MTime = 0; // Last modification of contents of the file;
    // time_t ctim = 0; // Last modification of attributes to the file;
    AWeakRwLock<SDirectory> m_pParent;
};

}

#endif //CPPFUSE_SINFO_HPP
