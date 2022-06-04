#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <set>
using namespace std;
int main()
{

    char server_message[256] = "Hi, Yes you have reached the server!";
    char buf[256];
    string request = "";
    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    bool check = false;
    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 5);
    int client_socket[3];
    int option = 0, balance = 0, limit = 0;
    srand(time(NULL));
    cout << "Press 1 to withdraw cash\n";
    cin >> option;
    if (option == 1)
    {
        balance = rand() % 50000;
        balance > 25000 ? limit = 25000 : limit = balance - 1;
    }
        set<int> myset;
        set<int>::iterator set_iterator;
        for (; myset.size() != 3;)
        {
            option = rand() % 4;
            if (option == 0)
            {
                cout << "\nTransaction Failed\n";
            }
            else
            {
                myset.insert(option);
            }
        }
        cout << "\nTransaction Continues\n";
        client_socket[0] = accept(server_socket, NULL, NULL);
        printf("Client 1 connected: %d\n", client_socket[0]);

        client_socket[1] = accept(server_socket, NULL, NULL);
        printf("Client 2 connected: %d\n", client_socket[1]);

        client_socket[2] = accept(server_socket, NULL, NULL);
        printf("Client 3 connected: %d\n", client_socket[2]);
    status:
        request = "1";
        send(client_socket[distance(myset.begin(), myset.find(1))], request.c_str(), strlen(request.c_str()), 0);
        request.clear();
        recv(client_socket[distance(myset.begin(), myset.find(1))], &buf, sizeof(buf), 0);
        request.assign(buf);
        if (request == "Approved")
        {
            printf("\nCard Status Verified\n");
            close(client_socket[distance(myset.begin(), myset.find(1))]);
        PIN:
            request = "2";
            send(client_socket[distance(myset.begin(), myset.find(2))], request.c_str(), strlen(request.c_str()), 0);
            request.clear();
            recv(client_socket[distance(myset.begin(), myset.find(2))], &buf, sizeof(buf), 0);
            request.assign(buf);
            if (request == "Verified")
            {
                printf("\nPIN Verified\n");
                close(client_socket[distance(myset.begin(), myset.find(2))]);
                check = false;
                while(check != true) {
                    cout << "Enter amount to withdraw: ";
                    cin >> option;
                    if (option > limit || option < 0) {
                        cout << "Invalid amount.\nLimit of transaction is: " << limit << endl;
                    }
                    else {
                        check = true;
                    }
                }
                request = "3";
                send(client_socket[distance(myset.begin(), myset.find(3))], request.c_str(), strlen(request.c_str()), 0);
                request.clear();
                request = to_string(balance) + "," + to_string(option);
                send(client_socket[distance(myset.begin(), myset.find(3))], request.c_str(), strlen(request.c_str()), 0);
                recv(client_socket[distance(myset.begin(), myset.find(3))], &buf, sizeof(buf), 0);
                request.assign(buf);
                close(client_socket[distance(myset.begin(), myset.find(3))]);

                printf("\n%s \n", buf);
            }
            else
            {
                goto PIN;
            }
        }
        else
        {
            goto status;
        }
    close(server_socket);
    return 0;
}