#include <chaiscript/chaiscript.hpp>
#include <stdexcept>

std::string helloWorld(const std::string &t_name) {
    return "Hello " + t_name + "!";
}


// adopted from the docs
int main() {
    try {
        chaiscript::ChaiScript chai;
        chai.add(chaiscript::fun(&helloWorld), "helloWorld");

        chai.eval("puts(helloWorld(\"Bob\"));");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
