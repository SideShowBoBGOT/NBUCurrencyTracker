#include <CppCurrency/Views/NSTable.hpp>
#include <CppCurrency/Views/NSToggle.hpp>

#include <pugixml.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

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

	const auto table = curr::NSTable::New(std::move(data));
	const auto toggle = curr::NSToggle({std::make_pair("JSON", nullptr), std::make_pair("XML", nullptr), std::make_pair("CSV", nullptr)});
	const auto toggleComponent = toggle.Component();
	const auto vert = ftxui::Renderer(ftxui::Container::Vertical({toggle.Component(), table}), [toggle, table]() {
		return ftxui::vbox(
			ftxui::hbox(ftxui::text("File type: "), toggle->Render(), ftxui::separator()),
			table->Render()
		);
	});

	auto screen = ftxui::ScreenInteractive::FitComponent();
	screen.Loop(vert);

	return 0;
}