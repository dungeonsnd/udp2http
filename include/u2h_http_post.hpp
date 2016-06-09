#ifndef _HEADER_FILE_HTTP_POST_HPP_
#define _HEADER_FILE_HTTP_POST_HPP_

#include <string>
#include "curl/curl.h"

int SendHttpReq(const std::string & url,const std::string & data)
{
    int res =0;
    std::string errstr(512,'\0');
    do
    {
        printf("SendHttpReq \n");
        
        CURLcode urlcode;
        CURL * curl =curl_easy_init();
        if(NULL==curl)
        {
            res =1;
            printf("SendHttpReq, curl_easy_init failed! \n");
            break;
        }
        
        urlcode =curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,&errstr[0]);
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_setopt CURLOPT_TIMEOUT failed,urlcode=%d.\n",int(urlcode));
        }
        
        urlcode =curl_easy_setopt(curl,CURLOPT_NOSIGNAL,1);
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_setopt CURLOPT_TIMEOUT failed,urlcode=%d,%s \n",
                int(urlcode),curl_easy_strerror(urlcode));
        }
        
        urlcode =curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,12);
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_setopt CURLOPT_TIMEOUT failed,urlcode=%d,%s \n",
                int(urlcode),curl_easy_strerror(urlcode));
        }
        
        urlcode =curl_easy_setopt(curl,CURLOPT_TIMEOUT,16);
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_setopt CURLOPT_TIMEOUT failed,urlcode=%d,%s \n",
                int(urlcode),curl_easy_strerror(urlcode));
        }
        
        urlcode =curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_setopt CURLOPT_URL failed,urlcode=%d,%s \n",
                int(urlcode),curl_easy_strerror(urlcode));
            res =1;
            break;
        }
        
        urlcode =curl_easy_setopt(curl,CURLOPT_POSTFIELDS,data.c_str());
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_setopt CURLOPT_POSTFIELDS failed,urlcode=%d,%s \n",
                int(urlcode),curl_easy_strerror(urlcode));
            res =1;
            break;
        }
        
        urlcode =curl_easy_perform(curl);
        if(urlcode!=CURLE_OK)
        {
            printf("SendHttpReq, curl_easy_perform failed,urlcode=%d,%s \n",
                int(urlcode),curl_easy_strerror(urlcode));
            res =1;
            break;
        }
        
        long httpRetCode =0;
        urlcode =curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&httpRetCode);
        if(urlcode!=CURLE_OK)
        {
            res =1;
            break;
        }
        printf("http server return code:%ld \n",httpRetCode);
        
        curl_easy_cleanup(curl);
    }while(0);
    return res;
}


#endif // _HEADER_FILE_HTTP_POST_HPP_
