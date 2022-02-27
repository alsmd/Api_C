#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
//sudo apt install curl
//apt-get install libcurl4-openssl-dev
//apt-get install libcurl4-gnutls-dev
//gcc main.c -lcurl

int	function_pt(void *ptr, size_t size, size_t nmemb, void *stream){
    printf("%s\n", (char *) ptr);
}


int main(void)
{
    CURL    *curl;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://pokeapi.co/api/v2/pokemon/ditto");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
  return 0;
}