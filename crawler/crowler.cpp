#include<regex>
#include<iostream>
#include<cstdio>
#include<curl/curl.h>
//#include<regex>
#include<string>
#include<bits/stdc++.h>
using namespace std;

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
int main(void) {
  string info;
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  vector <string> list;
  vector <string> tmp;
  vector <string> tmp1;
  int len = 1;
  string site = "http://msu.kz";
  regex rgx("http[s]?://[\\w\\.\\?\\$\\-\\+#/%=]+");
  if (curl) {
      for (int i = 0; i < 1; i++) {
          for (int j = 0; j < len; j++) {
              if (i == 0)
                  curl_easy_setopt(curl, CURLOPT_URL, "http://msu.kz");
              else 
                  curl_easy_setopt(curl, CURLOPT_URL, tmp1[j].c_str());
//    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
              curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
              curl_easy_setopt(curl, CURLOPT_WRITEDATA, &info); 
              res = curl_easy_perform(curl);
              if (res != CURLE_OK)
                  fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
              for (sregex_iterator it = sregex_iterator(info.begin(), info.end(), rgx); it != sregex_iterator(); it++) {
                  smatch match;
                  match = *it;
                  tmp.push_back(match.str(0));
                  list.push_back(match.str(0));
//                cout<<match.str(0)<<endl;
              }
//              len = tmp.size();
//              tmp1 = tmp;
          }
          tmp1 = tmp;
          len = tmp1.size();
      }
  }
  curl_easy_cleanup(curl);
  for (int i = 0; i < list.size(); i++)
      cout<<list[i]<<endl;;
  return 0;
}
