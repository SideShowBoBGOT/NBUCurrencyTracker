#ifndef CPPCURRENCY_NSPROVIDER_HPP
#define CPPCURRENCY_NSPROVIDER_HPP

#include <CppCurrency/Models/NNFileType.hpp>
#include <CppCurrency/Models/SCurrencyData.hpp>

namespace curr::NSProvider {

AProvideResult Do(const NFileType fileType);

}

#endif //CPPCURRENCY_NSPROVIDER_HPP
