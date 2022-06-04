#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <netinet/in.h>
using namespace std;

string add_str(string s1, char ch, string s2) 
{
    return s1 + ch + s2;
}

int main()
{

    char request[256] = "Hello I am Client are you there";
    char buf[200];
    string requests = "Order by: ", input;
    // create the socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //setup an address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(3001);
    fflush(stdin);
    cout << "Enter your department: " << endl;
    getline(cin, input);
    requests = add_str(requests, '-', input);
    cout << "Enter your name: " << endl;
    getline(cin, input);
    requests = add_str(requests, '-', input);
    cout << "Enter your Roll Number: " << endl;
    getline(cin, input);
    requests = add_str(requests, '-', input);
    cout << "Enter your Table Number: " << endl;
    getline(cin, input);
    requests = add_str(requests, '-', input);
    requests = add_str(requests, '\n', "Order item:");
    cout << "Enter your Order: " << endl;
    getline(cin, input);
    requests = add_str(requests, ' ', input);
    fflush(stdin);
    cout << requests << endl;

    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

    send(sock, requests.c_str(), strlen(requests.c_str()), 0);
    recv(sock, &buf, sizeof(buf), 0);
    printf("\n %s \n", buf);

    close(sock);

    return 0;
}