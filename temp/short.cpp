#include <typeinfo>
#include<iostream>
#include<string>

int main()
{
    std::string choice = "I Wanna improve my programming skills";
    std::cout << typeid(choice).name() << std::endl;
    return 0;
}