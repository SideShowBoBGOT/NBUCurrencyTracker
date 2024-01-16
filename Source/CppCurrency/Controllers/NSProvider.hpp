#ifndef CPPCURRENCY_NSPROVIDER_HPP
#define CPPCURRENCY_NSPROVIDER_HPP

#include "NNFileType.hpp"
#include <CppCurrency/Models/ACurrencyData.hpp>
#include <filesystem>
#include <memory>

namespace spdlog {
class logger;
}

namespace curr::NSProvider {
	AProvideResult Do(const NFileType fileType);
}

#endif //CPPCURRENCY_NSPROVIDER_HPP
