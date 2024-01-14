#include <CppCurrency/Models/SCurrencyData.hpp>

namespace curr {

SCurrencyData::SCurrencyData(std::string id, std::string fullName, std::string rate,
	std::string shortName, std::string exchangeDate)
	: 	Id{std::move(id)}, FullName{std::move(fullName)},
		Rate{std::move(rate)}, ShortName{std::move(shortName)},
		ExchangeDate{std::move(exchangeDate)} {}

SCurrencyData::SCurrencyData(const SCurrencyData& other)
	: Attrs{other.Attrs} {}

SCurrencyData::SCurrencyData(SCurrencyData&& other) noexcept
	: Attrs{std::move(other.Attrs)} {}

SCurrencyData::~SCurrencyData() {}

}