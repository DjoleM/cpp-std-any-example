#include <any>
#include <string>
#include <vector>
#include <iostream>

class ComplexType {
public:
    ComplexType() {
        a = 4;
        b = "hi";
    }
    int a;
    std::string b;
};

int main(int argc, char* argv[]) {
    std::cout << "Testing for int, expected 1, got: ";
	std::any testInt = 1;
    std::cout << std::any_cast<int>(testInt) << std::endl;

    std::cout << "Testing for std::string, expected woah, got: ";
    std::any testString = std::string("woah");
    std::cout << std::any_cast<std::string>(testString) << std::endl;

    std::cout << "Testing for 'ComplexType', expected a = 4, b = hi, got: ";
	std::any complexAny = new ComplexType();
    ComplexType* complexCast = std::any_cast<ComplexType*>(complexAny);
    std::cout << "a = " << complexCast->a << ", b = " << complexCast->b << std::endl;
    
    std::vector<std::any> vec;
    vec.push_back(1);
    vec.push_back(std::string("hi"));
    vec.push_back(new ComplexType());
	for (auto v = vec.begin(); v != vec.end(); ++v) {
        std::cout << "v is: " << v->type().name() << std::endl;
        if (v->type().name() == typeid(ComplexType*).name()) {
            auto complex = std::any_cast<ComplexType*>(*v);
            std::cout << "v: a: " << complex->a << " b: " << std::any_cast<ComplexType*>(*v)->b << std::endl;
        } else if (v->type().name() == typeid(std::string).name()) {
            std::cout << "v: " << std::any_cast<std::string>(*v) << std::endl;
        } else if (v->type().name() == typeid(int).name()) {
            std::cout << "v: " << std::any_cast<int>(*v) << std::endl;
        }
    }

    std::cout << "Hit enter to continue" << std::endl;
    int terminalPause;
	std::cin >> terminalPause;
    return 0;
}