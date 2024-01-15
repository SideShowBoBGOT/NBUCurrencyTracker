#include <CppCurrency/Views/TCurrencyTable.hpp>
#include <CppCurrency/Views/TCurrencyDataView.hpp>
#include <ftxui/component/component.hpp>
#include <simdutf.h>

namespace curr {

static const ACurrencyData s_xHeader = {"Id", "Full name", "Rate", "Short name", "Exchange date"};

TCurrencyTable::TCurrencyTable() {
	m_pHeader = ftxui::Container::Vertical({});
	m_pHeader->Add(ftxui::Make<TCurrencyDataView>(ACurrencyData(s_xHeader)));
	m_pBody = ftxui::Container::Vertical({});
	m_pRenderTable = ftxui::Container::Vertical({m_pHeader, m_pBody});
	m_pRenderTable = ftxui::Renderer(m_pRenderTable, [this]() {
		const auto bodyRender = m_bIsError ? ftxui::text(m_sErrorMessage)
			: m_pBody->Render() | ftxui::vscroll_indicator | ftxui::frame;
		return ftxui::vbox(m_pHeader->Render(), ftxui::separator(), bodyRender);
	});
}

const ftxui::Component& TCurrencyTable::Component() const {
	return m_pRenderTable;
}

void TCurrencyTable::Update(AProvideResult&& result) {
	m_bIsError = std::holds_alternative<ACurrencyError>(result);
	if(m_bIsError) {
		m_sErrorMessage = std::move(std::get<ACurrencyError>(result));
		return;
	}
	m_pHeader->DetachAllChildren();
	m_pBody->DetachAllChildren();
	auto headerData = s_xHeader;
	auto bodyData = std::move(std::get<ACurrencyVector>(result));
	ArrangeTable(headerData, bodyData);
	m_pHeader->Add(ftxui::Make<TCurrencyDataView>(std::move(headerData)));
	for(auto& row : bodyData) {
		m_pBody->Add(ftxui::Make<TCurrencyDataView>(std::move(row)));
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


