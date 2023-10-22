#ifndef CPPFUSE_TCOMMONDECLARATIONS_HPP
#define CPPFUSE_TCOMMONDECLARATIONS_HPP

#include <TRwLock.hpp>
#include <memory>

namespace cppfuse {

class TDirectory;

using TRwDirectory = std::shared_ptr<rppsync::TRwLock<TDirectory>>;

}

#endif //CPPFUSE_TCOMMONDECLARATIONS_HPP
