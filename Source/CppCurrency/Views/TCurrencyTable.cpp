#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Views/TCurrencyDataView.hpp>
#include <ftxui/component/component.hpp>
#include <simdutf.h>

namespace curr {

static const ACurrencyData s_Header = {"Id", "Full name", "Rate", "Short name", "Exchange date"};

TCurrencyTable::TCurrencyTable() {
	m_Header = ftxui::Container::Vertical({});
	m_Header->Add(ftxui::Make<TCurrencyDataView>(ACurrencyData(s_Header)));
	m_Body = ftxui::Container::Vertical({});
	m_RenderTable = ftxui::Container::Vertical({m_Header, m_Body});
	m_RenderTable = ftxui::Renderer(m_RenderTable, [this]() {
		const auto bodyRender = m_IsError ? ftxui::text(m_ErrorMessage)
			: m_Body->Render() | ftxui::vscroll_indicator | ftxui::frame;
		return ftxui::vbox(m_Header->Render(), ftxui::separator(), bodyRender);
	});
}

const ftxui::Component& TCurrencyTable::Component() const {
	return m_RenderTable;
}

void TCurrencyTable::Update(AProvideResult&& result) {
	m_IsError = std::holds_alternative<ACurrencyError>(result);
	if(m_IsError) {
		m_ErrorMessage = std::move(std::get<ACurrencyError>(result));
		return;
	}
	m_Header->DetachAllChildren();
	m_Body->DetachAllChildren();
	auto headerData = s_Header;
	auto bodyData = std::move(std::get<ACurrencyVector>(result));
	ArrangeTable(headerData, bodyData);
	m_Header->Add(ftxui::Make<TCurrencyDataView>(std::move(headerData)));
	for(auto& row : bodyData) {
		m_Body->Add(ftxui::Make<TCurrencyDataView>(std::move(row)));
	}
}

void TCurrencyTable::ArrangeTable(ACurrencyData& headerData, ACurrencyVector& bodyData) {
	for(auto columnIndex = 0u; columnIndex < bodyData.front().size(); ++columnIndex) {
		auto maxSize = headerData[columnIndex].size();
		for(const auto& row : bodyData) {
			const auto& el = row[columnIndex];
			maxSize = std::max(maxSize, CountUTF8Chars(el));
		}
		for(auto& row : bodyData) AddSpace(row[columnIndex], maxSize);
		AddSpace(headerData[columnIndex], maxSize);
	}
}

size_t TCurrencyTable::CountUTF8Chars(const std::string& str) {
	return simdutf::count_utf8(str.data(), str.size());
}

void TCurrencyTable::AddSpace(std::string& str, const size_t maxSize) {
	str += std::string(maxSize - CountUTF8Chars(str), ' ');
}

}


