#include<regex>
#include<iostream>
#include<cstdio>
#include<curl/curl.h>
//#include<regex>
#include<string>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

size_t save_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
    ((std::string*)userdata)->append((char*)ptr, size * nmemb);
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
      for (int i = 0; i < 3; i++) {
          for (int j = 0; j < len; j++) {
              if (i == 0 && j == 0)
                  curl_easy_setopt(curl, CURLOPT_URL, "http://msu.kz");
              else 
                  curl_easy_setopt(curl, CURLOPT_URL, tmp1[j].c_str());
              curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_data);
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
              }
              info.clear();
          }
          tmp1 = tmp;
          len = tmp1.size();
          tmp.erase(tmp.begin(), tmp.end());
      }
  }
  curl_easy_cleanup(curl);
  ofstream file;
  file.open("answer.txt");
  for (int i = 0; i < list.size(); i++)
      file<<list[i]<<endl;;
  file.close();
  return 0;
}
