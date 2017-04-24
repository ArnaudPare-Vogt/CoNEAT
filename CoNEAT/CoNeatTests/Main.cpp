#define CATCH_CONFIG_RUNNER
#include <Catch/catch.hpp>

int main(int argc, char **argv) {
	int result = Catch::Session().run(argc, argv);

	std::cin.get();

	return result < 0xff ? result : 0xff;
}
