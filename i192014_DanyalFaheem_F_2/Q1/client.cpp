#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;
string divide_str(string s, int count)
{
    string str = "";
    for (int count2 = 0, counter = 0; count2 < count; count2++)
    {
        str = "";
        for (; s[counter] != 0 && s[counter] != ','; counter++)
            str += s[counter];
        counter++;
    }
    return str;
}
int main()
{

    string request;
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
    int balance = 0, amount = 0;
    recv(sock, &buf, sizeof(buf), 0);
    request.assign(buf);
    switch (stoi(request))
    {
    case 1:
        request.clear();
        amount = rand() % 10;
        if (amount == 0)
        {
            request = "Not Approved";
        }
        else
        {
            request = "Approved";
        }
        break;
    case 2:
        request.clear();
        amount = rand() % 10;
        if (amount == 0)
        {
            request = "Not Verified";
        }
        else
        {
            request = "Verified";
        }
        break;
    case 3:
        request.clear();
        recv(sock, &buf, sizeof(buf), 0);
        request.assign(buf);
        balance = stoi(divide_str(request, 1));
        amount = stoi(divide_str(request, 2));
        request = "Amount withdrawn: " + to_string(amount) + "\nRemaining Balance: " + to_string(balance - amount) + "\0";
        break;
    default:
        break;
    }

    send(sock, request.c_str(), strlen(request.c_str()), 0);
    close(sock);

    return 0;
}
