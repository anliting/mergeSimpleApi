#include<fstream>
#include<iostream>
#include<string>
int main(int argc,char**argv){
    std::ifstream ifs;
    ifs.open(std::string(argv[1])+"/index.html");
    ifs.close();
    /*for(auto&e:std::filesystem::directory_iterator(
        std::string(argv[1])
    ))
        std::cout<<e.path()<<std::endl;*/
}
