#include <CppCurrency/Views/NSTable.hpp>

#include <ftxui/component/component.hpp>
#include <simdutf.h>
#include <ranges>

namespace curr::NSTable {



void ArrangeColumns(std::vector<std::vector<std::string>>& data) {
	for(auto columnIndex = 0u; columnIndex < data.front().size(); ++columnIndex) {
		auto maxSize = size_t(0);
		for(const auto& row : data) {
			const auto& el = row[columnIndex];
			maxSize = std::max(maxSize, simdutf::count_utf8(el.data(), el.size()));
		}
		for(auto& row : data) {
			auto& el = row[columnIndex];
			el += std::string(maxSize - simdutf::count_utf8(el.data(), el.size()), ' ');
		}
	}
}

ftxui::Component New(std::vector<std::vector<std::string>>&& data) {
	ArrangeColumns(data);
	const auto head = ftxui::Make<TRow>(std::move(data.front()));
	const auto body = ftxui::Container::Vertical({});
	for(auto& row : data | std::views::drop(1)) {
		body->Add(ftxui::Make<TRow>(std::move(row)));
	}
	const auto bodyRenderer = ftxui::Renderer(body, [body]() {
		return body->Render() | ftxui::vscroll_indicator | ftxui::frame;
	});
	const auto table = ftxui::Container::Vertical({head, bodyRenderer});
	const auto tableRenderer = ftxui::Renderer(table, [head, bodyRenderer]() {
		return ftxui::vbox(head->Render(), ftxui::separator(), bodyRenderer->Render()) | ftxui::border;
	});
	return tableRenderer;
}

}