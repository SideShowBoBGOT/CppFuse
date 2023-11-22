#ifndef CPPFUSE_TFILE_HPP
#define CPPFUSE_TFILE_HPP

#include <CppFuse/Helpers/ASharedLock.hpp>

namespace cppfuse {

class TSetInfoName;
class TSetInfoMode;
class TSetInfoUid;
class TSetInfoGid;
class TSetInfoParent;

class TGetInfoName;
class TGetInfoMode;
class TGetInfoUid;
class TGetInfoGid;
class TGetInfoParent;

// https://www.gnu.org/software/libc/manual/html_node/Attribute-Meanings.html
template<typename ParentType>
class TFile {
    friend class TSetInfoName;
    friend class TSetInfoMode;
    friend class TSetInfoUid;
    friend class TSetInfoGid;
    friend class TSetInfoParent;

    friend class TGetInfoName;
    friend class TGetInfoMode;
    friend class TGetInfoUid;
    friend class TGetInfoGid;
    friend class TGetInfoParent;

    public:
    TFile()=default;

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
    uid_t m_uUid = 0;
    gid_t m_uGid = 0;
    AWeakRwLock<ParentType> m_pParent;
};

}

#endif //CPPFUSE_TFILE_HPP
