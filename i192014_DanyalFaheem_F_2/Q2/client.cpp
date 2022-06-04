#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <string.h>
using namespace std;
int main()
{

    string request = "";
    char buf[256];

    // create the socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //setup an address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);

    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));
    int option;
    cout << "Enter your choice from the menu: ";
    cin >> option;
    request = to_string(option);
    send(sock, request.c_str(), strlen(request.c_str()), 0);
    recv(sock, &buf, sizeof(buf), 0);
    printf("%s \n", buf);
    cin >> request;
    send(sock, request.c_str(), strlen(request.c_str()), 0);
    memset(buf, 0, sizeof buf);
    recv(sock, &buf, sizeof(buf), 0);
    printf("%s \n", buf);
    close(sock);

    return 0;
}
