#include "afxwin.h"

std::string helloWorld(const std::string &t_name) {
    return "Hello " + t_name + "!";
}

template <typename T>
class countable
{
    static int count;

    int id;

public:
    countable() :
        id(count + 1)
    {
        ++count;
    }

    countable(countable&&) :
        id(count + 1)
    {
        ++count;
    }

    countable(const countable&) :
        id(count + 1)
    {
        ++count;
    }
public:
    int my_id() const {
        return id;
    }
};
template <typename T> int countable<T>::count(0);

class test : public countable<test> {
public:
    // test(test&&) {
    //     std::cout << __FUNCTION__ << "(test&&)" << std::endl;        
    // }
    test(const test&) {
        std::cout << __FUNCTION__ << "(const test&)" << std::endl;        
    }
    test() {
        std::cout << __FUNCTION__ << "()" << std::endl;
    }
    ~test() {
        std::cout << __FUNCTION__ << std::endl;
    }
    void foo() {
        std::cout << "foo!" << std::endl;
    }
};

int main() {
    try {
        chaiscript::ChaiScript chai;
        chai
            .add(chaiscript::fun(&helloWorld), "helloWorld")
            .add(chaiscript::user_type<test>(), "test")
            .add(chaiscript::constructor<test()>(),"test")
            .add(chaiscript::constructor<test(const test&)>(), "test")
            .add(chaiscript::fun(&test::foo), "foo")
        ;

        chai.eval("print(helloWorld(\"Bob\"));");
        chai.eval("var t = test(); t.foo();");
        chai.eval("var t2 = t; t2.foo();");
        chai.eval("def test::bar() { print(\"bar!\"); } t.bar();");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
