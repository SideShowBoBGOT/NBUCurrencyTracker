#include <CppCurrency/CLI/TApplicationCLI.hpp>

int main(int argc, char *argv[]) {
	auto cli = curr::TApplicationCLI();
	CLI11_PARSE(cli, argc, argv);
	return 0;
}