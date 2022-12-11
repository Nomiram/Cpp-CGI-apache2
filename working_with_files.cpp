#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "HTTP.hpp"
#include "db.hpp"
#include "db.cpp"
using namespace std;
int main()
{
    HTTP http;
    http.init();
    FILEDB<std::string, std::string> db;
    std::string getparam = http.rawURLDecode(string(http.httpGet("get")));
    std::string getallparam = string(http.httpGet("getall"));
    if(http.httpGet("gui")!="false"){
        http.httpSendFile("uploadFile.html");
    }
    for(auto i = http.filesData.begin();i != http.filesData.end();i++){
        auto key = (*i).first;
        auto val = (*i).second;
        // cout << key <<endl;
        int res = http.move_uploaded_file(val,"./usrfiles/"+val.filename);
        // int res = http.move_uploaded_file(val,"/tmp/"+val.filename);
        if(res != 0){
            std::cout << strerror(errno)<<" ";
            cout <<res<<" "<<val.filename+" ";
            unlink(val.tmp_name.c_str());
        }
    }
    http.send();
}