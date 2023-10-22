#include "TFileSystemObject.hpp"

namespace cppfuse {

cppfuse::TFileSystemObject::TFileSystemObject(const std::string& name, mode_t mode)
    : m_sName{name}, m_uMode{mode} {}

mode_t cppfuse::TFileSystemObject::Mode() const { return m_uMode; }

void cppfuse::TFileSystemObject::Mode(mode_t mode) { m_uMode = mode; }

const std::string& cppfuse::TFileSystemObject::Name() const { return m_sName; }

void cppfuse::TFileSystemObject::Name(const std::string& name) { m_sName = name; }

}


