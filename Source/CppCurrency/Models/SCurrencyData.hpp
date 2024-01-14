#ifndef CPPCURRENCY_SCURRENCYDATA_HPP
#define CPPCURRENCY_SCURRENCYDATA_HPP

#include <string>
#include <vector>
#include <variant>
#include <array>

namespace curr {

struct SCurrencyData;

using ACurrencyError = std::string;
using AProvideResult = std::variant<std::vector<SCurrencyData>, ACurrencyError>;

struct SCurrencyData {
	SCurrencyData(std::string id, std::string fullName, std::string rate,
		std::string shortName, std::string exchangeDate);
	SCurrencyData(const SCurrencyData& other);
	SCurrencyData(SCurrencyData&& other) noexcept;
	~SCurrencyData();
	union {
		struct {
			std::string Id;
			std::string FullName;
			std::string Rate;
			std::string ShortName;
			std::string ExchangeDate;
		};
		std::array<std::string, 5> Attrs;
	};
};

}

#endif //CPPCURRENCY_SCURRENCYDATA_HPP
