#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <curl/curl.h>

const char* outputfile =  "webpage.out";

size_t cbfunction( void* ptr, size_t size, size_t nmemb, void* arg ) {
    size_t written = fwrite( ptr, size, nmemb, (FILE*) arg);
    return written;
}

int main( int argc, char** argv ) {
    
    if ( argc != 2 ) {
        printf( "Usage: %s <url>\n", argv[0] );
        return -1;
    }
    FILE* f = fopen( outputfile, "w+" );
    curl_global_init( CURL_GLOBAL_DEFAULT );
    CURL *handle = curl_easy_init( );

    curl_easy_setopt( handle, CURLOPT_URL, argv[1] );
    curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, cbfunction );
    curl_easy_setopt( handle, CURLOPT_WRITEDATA, f );

    curl_easy_perform( handle );

    curl_global_cleanup( );
    return 0;
}
