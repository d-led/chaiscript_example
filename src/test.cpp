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
public:
    virtual ~countable() {}
};
template <typename T> int countable<T>::count(0);

class test : public countable < test > {
private:
    void print(const char* fun, const char* adornment = "") {
        std::cout << fun << adornment << "[" << this->my_id() << "]" << std::endl;
    }
public:
    test(test&&) {
        print(__FUNCTION__, "(test&&)");
    }
    test(const test&) {
        print(__FUNCTION__, "(const test&)");
    }
    test() {
        print(__FUNCTION__, "()");
    }
    ~test() {
        print(__FUNCTION__);
    }
    void foo() {
        print("foo!");
    }
};

int main() {
    try {
        chaiscript::ChaiScript chai;
        chai
            .add(chaiscript::fun(&helloWorld), "helloWorld")
            .add(chaiscript::base_class<countable<test>, test>())
            .add(chaiscript::user_type<test>(), "test")
            .add(chaiscript::constructor<test()>(), "test")
            .add(chaiscript::constructor<test(const test&)>(), "test")
            .add(chaiscript::fun(&test::foo), "foo")
            .add(chaiscript::fun(&countable<test>::my_id), "my_id")
            ;

        chai.eval("print(helloWorld(\"Bob\"));");
        chai.eval("var t = test(); t.foo();");
        chai.eval("var t2 = t; t2.foo();");
        chai.eval("def test::bar() { print(\"bar![\"+this.my_id.to_string+\"]\"); } t.bar();");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
