#ifndef CPPFUSE_SOVERLOADVARIANT_HPP
#define CPPFUSE_SOVERLOADVARIANT_HPP

namespace cppfuse {

template<class... Ts>
struct SOverloadVariant : Ts... { using Ts::operator()...; };

template<class... Ts>
SOverloadVariant(Ts...) -> SOverloadVariant<Ts...>;

}

#endif //CPPFUSE_SOVERLOADVARIANT_HPP
