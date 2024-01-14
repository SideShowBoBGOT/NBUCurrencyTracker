#ifndef CPPCURRENCY_TCURRENCYTABLE_HPP
#define CPPCURRENCY_TCURRENCYTABLE_HPP

#include <CppCurrency/Models/ACurrencyData.hpp>
#include <ftxui/component/component_base.hpp>

namespace curr {

class TCurrencyTable {
	public:
	TCurrencyTable();

	public:
	const ftxui::Component& Component() const;
	void Update(AProvideResult&& result);

	protected:
	static void ArrangeTable(ACurrencyData& headerData, ACurrencyVector& bodyData);
	static void AddSpace(std::string& str, const size_t maxSize);
	static size_t CountUTF8Chars(const std::string& str);

	protected:
	bool m_IsError = false;
	std::string m_ErrorMessage;
	ftxui::Component m_Header = nullptr;
	ftxui::Component m_Body = nullptr;
	ftxui::Component m_RenderTable = nullptr;
};

}

#endif //CPPCURRENCY_TCURRENCYTABLE_HPP
