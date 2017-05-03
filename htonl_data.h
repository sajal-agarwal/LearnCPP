#include <winsock2.h>


// link with Ws2_32.lib
#if 0   // below not working
#pragma comment (lib, "Ws2_32.lib")
#endif

char * htonl_char_buf(char *arr) {
    for (unsigned i = 0; i < sizeof(arr) / sizeof(unsigned); ++i) {
        unsigned o = *((unsigned*)(arr + 4));
        unsigned tc = htonl(o);
        *(unsigned*)(arr + 4) = tc;
    } return arr;
}

int main(int argc, char **argv)
{

    unsigned c = 0x01020304;

    // usinged to char array
    char *charr = (char*)(&c);

    char arr[8] = { 0x01, 0x02, 0x3, 0x04, 0x11, 0x12, 0x13, 0x14 };//(char*)&c;

    htonl_char_buf(arr);

    return 0;
}
