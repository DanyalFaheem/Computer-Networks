#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <fstream>
using namespace std;

string divide_str(string s, int count)
{
    string str = "";
    for (int count2 = 0, counter = 0; count2 < count; count2++)
    {
        str = "";
        for (; s[counter] != 0 && s[counter] != '-'; counter++)
            str += s[counter];
        counter++;
    }
    return str;
}

int main()
{

    char server_message[256] = "Hi, Yes you have reached the server!";
    char buf[200];
    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 5);
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // send the message
    while (1)
    {
        recv(client_socket, &buf, sizeof(buf), 0);
        fstream file;
        fstream file_input;
        string orders(buf + '\0');
        string saveToFile;
        time_t current_time;
        time(&current_time);
        string Ordertime = ctime(&current_time);
        Ordertime = Ordertime.substr(Ordertime.find(':') - 3, 8);
        string serving_time = ctime(&current_time);
        serving_time = serving_time.substr(serving_time.find(':') - 3, 3) + ":" + to_string(stoi(serving_time.substr(serving_time.find(':') + 1, 2)) + 15) + serving_time.substr(serving_time.find(':') + 3, 3);
        string response = "Order time: " + Ordertime + '\n' + "Serving time: " + serving_time;
        //cout
        //<< orders[11] << orders[12] << endl;
        char dept[3] = {toupper(buf[11]), toupper(buf[12])};
        if (!strcmp(dept, "CS"))
        {
            file_input.open("CS.txt", ios::app);
            getline(file, saveToFile);
            if (saveToFile[0] == '1')
            {
                while (!file.eof())
                {
                    {
                        getline(file, saveToFile);
                    }
                    saveToFile = saveToFile[0] + 1;
                    saveToFile += "," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
                }
            }
            else
            {
                saveToFile = "1," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
            }
            file_input.close();
            file.open("CS.txt", ios::app);

            // cout << saveToFile << endl;
            file << saveToFile << endl;
            file.close();
        }
        else if (!strcmp(dept, "SE"))
        {
            file_input.open("SE.txt", ios::app);
            getline(file, saveToFile);
            if (saveToFile[0] == '1')
            {
                while (!file.eof())
                {
                    {
                        getline(file, saveToFile);
                    }
                    saveToFile = saveToFile[0] + 1;
                    saveToFile += "," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
                }
            }
            else
            {
                saveToFile = "1," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
            }
            file_input.close();
            file.open("SE.txt", ios::app);

            // cout << saveToFile << endl;
            file << saveToFile << endl;
            file.close();
        }
        else if (!strcmp(dept, "AI"))
        {
            file_input.open("AI.txt", ios::app);
            getline(file, saveToFile);
            if (saveToFile[0] == '1')
            {
                while (!file.eof())
                {
                    {
                        getline(file, saveToFile);
                    }
                    saveToFile = saveToFile[0] + 1;
                    saveToFile += "," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
                }
            }
            else
            {
                saveToFile = "1," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
            }
            file_input.close();
            file.open("AI.txt", ios::app);

            // cout << saveToFile << endl;
            file << saveToFile << endl;
            file.close();
        }
        else if (!strcmp(dept, "DS"))
        {
            file_input.open("DS.txt", ios::app);
            getline(file, saveToFile);
            if (saveToFile[0] == '1')
            {
                while (!file.eof())
                {
                    {
                        getline(file, saveToFile);
                    }
                    saveToFile = saveToFile[0] + 1;
                    saveToFile += "," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
                }
            }
            else
            {
                saveToFile = "1," + divide_str(orders, 2) + "," + ctime(&current_time) + "," + divide_str(orders, 3) + "," + orders.substr(orders.find_last_of(':'));
            }
            file_input.close();
            file.open("DS.txt", ios::app);

            // cout << saveToFile << endl;
            file << saveToFile << endl;
            file.close();
        }
        //PrintToFile(order);
        //printf("\n %s \n", buf);

        send(client_socket, response.c_str(), strlen(response.c_str()), 0);
    }
    // close the socket
    close(server_socket);

    return 0;
}