#ifndef _HEADER_FILE_U2H_MSG_HPP_
#define _HEADER_FILE_U2H_MSG_HPP_

#include <string>
#include <vector>
#include "u2h_http_post.hpp"
#include "u2h_udp_deli.hpp"


//字符串分割函数
std::vector<std::string> u2h_strsplit(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    size_t size=str.size();

    for(size_t i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

class U2HMsg
{
public:
    U2HMsg(const char * recvBuf):
        _recvBuf(recvBuf)
    {
    }
    ~U2HMsg()
    {
    }
    
    void Process()
    {
        do
        {
            std::vector < std::string > ret =u2h_strsplit(_recvBuf, DELI);
            if(ret.size()!=2)
            {
                printf("recvBuf parsed error! ret.size=%d,%s \n",
                    int(ret.size()),_recvBuf.c_str());
                break;
            }
            
            _url =ret[0];
            _http_data =ret[1];
            
            SendHttpReq(_url,_http_data);
        }while(0);
    }
    
    std::string _url;
    std::string _http_data;

private:
    std::string _recvBuf;    
};

#endif // _HEADER_FILE_U2H_MSG_HPP_
