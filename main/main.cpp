#include<filesystem>
#include<iostream>
#include<string>
int main(int argc,char**argv){
    std::cout<<std::string(argv[1])+"/packages"<<std::endl;
    for(auto&e:std::filesystem::directory_iterator(
        std::string(argv[1])+"/packages"
    ))
        std::cout<<e.path()<<std::endl;
}
