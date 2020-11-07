#include<filesystem>
#include<iostream>
int main(int argc,char**argv){
    std::cout<<argv[1]<<std::endl;
    for(auto&entry:std::filesystem::directory_iterator(argv[1]))
        std::cout<<entry.path()<<std::endl;
    //std::filesystem
}
