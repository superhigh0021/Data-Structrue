#include <iostream>
#include <tuple>

static std::tuple<std::string, std::string> haha()
{
    std::string a = "ab";
    std::string b = "cd";

    return std::make_tuple(a, b);
}

int main(void)
{
    std::string s = "abcdefg";
    auto source = haha();
    std::cout<<std::get<0>(source)<<std::endl;
    std::cout<<std::get<1>(source)<<std::endl;


    system("pause");
    return 0;
}
