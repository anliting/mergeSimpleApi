#include<algorithm>
#include<filesystem>
#include<fstream>
#include<iostream>
#include<map>
#include<regex>
#include<sstream>
#include<string>
std::string getString(const char*s){
    std::ifstream ifs(s);
    std::stringstream ss;
    ss<<ifs.rdbuf();
    ifs.close();
    return ss.str();
}
struct Package{
    std::string name;
    std::vector<std::string>anchor;
    void getAnchor(const char*path){
        auto s=getString(path);
        std::regex e("(<a.*</a>)");
        std::smatch m;
        while(std::regex_search(s,m,e)){
            anchor.push_back(m[1].str());
            s=m.suffix().str();
        }
    }
};
std::vector<Package>getIndex(char*path){
    std::vector<Package>x;
    auto s=getString((std::string(path)+"/index.html").c_str());
    std::regex e("\">([^<]*)<");
    std::smatch m;
    while(std::regex_search(s,m,e)){
        Package p;
        p.name=m[1].str();
        p.getAnchor(
            (std::string(path)+"/"+m[1].str()+"/index.html").c_str()
        );
        x.push_back(p);
        s=m.suffix().str();
    }
    return x;
}
void toMap(auto&index,auto&map){
    for(auto&p:index){
        if(map.find(p.name)==map.end())
            map[p.name]=p;
        else{
            auto&anchor=map[p.name].anchor;
            anchor.insert(anchor.end(),p.anchor.begin(),p.anchor.end());
            std::sort(anchor.begin(),anchor.end());
            anchor.resize(
                anchor.end()-std::unique(anchor.begin(),anchor.end())
            );
        }
    }
}
int main(int argc,char**argv){
    auto index1=getIndex(argv[1]);
    auto index2=getIndex(argv[2]);
    std::map<std::string,Package>m;
    toMap(index1,m);
    toMap(index2,m);
    std::filesystem::create_directory(argv[3]);
    std::ofstream ofs(std::string(argv[3])+"/index.html");
    ofs<<"<!doctype html><title>.</title>";
    for(auto&p:m)
        ofs<<"<a href=\""<<p.first<<"/\">"<<p.first<<"</a>";
    ofs.close();
    for(auto&p:m){
        std::filesystem::create_directory(
            std::string(argv[3])+"/"+p.first
        );
        std::ofstream ofs(std::string(argv[3])+"/"+p.first+"/index.html");
        ofs<<"<!doctype html><title>.</title>";
        for(auto&s:p.second.anchor)
            ofs<<s;
        ofs.close();
    }
}
