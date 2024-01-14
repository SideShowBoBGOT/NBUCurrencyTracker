#ifndef CPPCURRENCY_ACURRENCYDATA_HPP
#define CPPCURRENCY_ACURRENCYDATA_HPP

#include <string>
#include <vector>
#include <variant>

namespace curr {

using ACurrencyData = std::array<std::string, 5>;
using ACurrencyError = std::string;
using ACurrencyVector = std::vector<ACurrencyData>;
using AProvideResult = std::variant<ACurrencyVector, ACurrencyError>;

}

#endif //CPPCURRENCY_ACURRENCYDATA_HPP
