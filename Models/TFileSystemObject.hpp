#ifndef CPPFUSE_TFILESYSTEMOBJECT_HPP
#define CPPFUSE_TFILESYSTEMOBJECT_HPP

#include <string>

namespace cppfuse {

class TFileSystemObject {
    public:
    TFileSystemObject(const std::string& name, mode_t mode);
    virtual ~TFileSystemObject()=default;
    [[nodiscard]] virtual mode_t Mode() const;
    virtual mode_t Mode(mode_t mode);
    [[nodiscard]] virtual const std::string& Name() const;
    virtual void Name(const std::string& name);

    protected:
    std::string m_sName;
    mode_t m_uMode = 0;
};

}



#endif //CPPFUSE_TFILESYSTEMOBJECT_HPP
