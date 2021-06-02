# std::any and some of its uses

std::any is a very helpful part of c++17, but due to its infancy there aren't too many helpful guides
on how to use it yet. So here are a few examples on how to use it with some basic and custom types
and most importantly, with vectors and other collecitons.

You can view, download and run a working example in stdAnyTest.cpp (look up^^^)

### Simple types

As described in the documentation simple types work intuitively, simply declare them as std::any types
and when you need them again cast them back to the desired form using `std::any_cast<T>()` as shown

```
std::any testInt = 1;
std::cout << std::any_cast<int>(testInt) << std::endl;

std::any testString = std::string("woah");
std::cout << std::any_cast<std::string>(testString) << std::endl;
```

### Custom classes

Custom classes work similarly to simple types, however it is important to remember that you'll be
re-casting a pointer to the class and not the class itself, everything else works as usual.

```
class ComplexType {
public:
    ComplexType() {
        a = 4;
        b = "hi";
    }
    int a;
    std::string b;
};

std::any complexAny = new ComplexType();
ComplexType* complexCast = std::any_cast<ComplexType*>(complexAny);
std::cout << "a = " << complexCast->a << ", b = " << complexCast->b << std::endl;
```

### Vectors of std::any type

So far, the part of this feature I've been enjoying the most is creating vectors of any types -
I know, very js-esque, but in c++ - I can hear my uni lecturers screaming in terror. This grants 
you an extraordinary flexibility to store any number types in one big (type-safe!!!) collection. 
The struggle then becomes to correctly re-cast the std::any objects to your desired type, but that
can easily be achieved with a little help of `typeid()`

```
class ComplexType {
public:
    ComplexType() {
        a = 4;
        b = "hi";
    }
    int a;
    std::string b;
};

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
```

Fun, right! Enjoy!