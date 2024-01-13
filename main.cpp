// Copyright 2022 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <memory>  // for allocator, __shared_ptr_access, shared_ptr
#include <string>  // for to_string, operator+
#include <ranges>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Button, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, text, Element, hbox, separator, size, vbox, border, frame, vscroll_indicator, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color, Color::Default, Color::GrayDark, Color::White

#include <pugixml.hpp>
#include <simdutf.h>

class TRow : public ftxui::ComponentBase {
	public:
	TRow(const std::vector<std::string>& attrs, const bool isFirst) {
		auto rendered = ftxui::Elements();
		const auto attrSize = attrs.size();
		rendered.reserve(attrSize);
		for(auto i = 0u; i < attrSize - 1; ++i) {
			rendered.push_back(ftxui::text(attrs[i]));
			rendered.push_back(ftxui::separator());
		}
		rendered.push_back(ftxui::text(attrs.back()));
		m_Row = ftxui::hbox(std::move(rendered));
		if(isFirst) {
			m_Row = ftxui::vbox(m_Row, ftxui::separator());
		}
	}

	public:
	virtual ftxui::Element Render() override {
		const auto isActive = Active();
		const auto isFocused = Focused();
		const auto focusManagement =  isFocused ? ftxui::focus : isActive ? ftxui::select : ftxui::nothing;
		return m_Row | focusManagement;
	}

	virtual bool Focusable() const { return true; }

	protected:
	ftxui::Element m_Row = nullptr;
};

int main() {
	auto xmlDocument = pugi::xml_document();
	if(not xmlDocument.load_file("fff.xml")) return -1;

	auto data = std::vector<std::vector<std::string>>();
	data.push_back({"Id", "Full name", "Rate", "Short name", "Exchange date"});
	for(const auto& currency : xmlDocument.child("exchange").children("currency")) {
		auto row = std::vector<std::string>();
		for(const auto& attr : currency.children()) {
			row.push_back(attr.child_value());
		}
		data.push_back(std::move(row));
	}
	for(auto columnIndex = 0u; columnIndex < data.front().size(); ++columnIndex) {
		auto maxSize = size_t(0);
		for(const auto& row : data) {
			const auto& el = row[columnIndex];
			maxSize = std::max(maxSize, simdutf::count_utf8(el.data(), el.size()));
		}
		for(auto& row : data) {
			auto& el = row[columnIndex];
			while(simdutf::count_utf8(el.data(), el.size()) < maxSize) {
				el += " ";
			}
		}
	}
	auto table = ftxui::Container::Vertical({});
	table->Add(ftxui::Make<TRow>(data.front(), true));
	for(const auto& row : data | std::views::drop(1)) {
		table->Add(ftxui::Make<TRow>(row, false));
	}

	auto renderer = ftxui::Renderer(table, [&] {
		return table->Render() | ftxui::vscroll_indicator | ftxui::frame | ftxui::border;
	});

	auto screen = ftxui::ScreenInteractive::FitComponent();
	screen.Loop(renderer);

	return 0;
}