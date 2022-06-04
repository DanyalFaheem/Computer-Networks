#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;
bool isPalindrome(string s)
{
    for (int counter = 0, count = s.length() - 1; counter < s.length() && count >= 0; counter++, count--)
    {
        if (s[counter] != s[count])
        {
            return false;
        }
    }
    return true;
}
string addNumbers(string num1, string num2)
{
    int num = 0, num3 = 0;
    map<int, string> list;
    list.insert(pair<int, string>(0, "Zero"));
    list.insert(pair<int, string>(1, "One"));
    list.insert(pair<int, string>(2, "Two"));
    list.insert(pair<int, string>(3, "Three"));
    list.insert(pair<int, string>(4, "Four"));
    list.insert(pair<int, string>(5, "Five"));
    list.insert(pair<int, string>(6, "Six"));
    list.insert(pair<int, string>(7, "Seven"));
    list.insert(pair<int, string>(8, "Eight"));
    list.insert(pair<int, string>(9, "Nine"));
    list.insert(pair<int, string>(10, "Ten"));
    for (int counter = 0; counter < 11; counter++)
    {
        if (list[counter] == num1)
            num = counter;
        if (list[counter] == num2)
            num3 = counter;
    }
    return list[num + num3];
}
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

    string server_message;
    char buf[256];
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
    int option;
    pid_t pid;
    for (int counter = 0; counter < 5; counter++)
    {
        client_socket = accept(server_socket, NULL, NULL);
        pid = fork();
        if (pid == 0)
        {
            cout << "Choose one of the options below by entering the number: \n"
                 << "1. String concatenation\n"
                 << "2. Find character\n"
                 << "3. Compare string\n"
                 << "4. Check Palindrome\n"
                 << "5. String Number addition\n"
                 << "6. Exit Program\n";
            recv(client_socket, &buf, sizeof(buf), 0);
            string input(buf);
            //cout << "input1: " << input << endl;
            switch (stoi(input))
            {
            case 1:
                server_message = "Enter your string: ";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                recv(client_socket, &buf, sizeof(buf), 0);
                input.assign(buf);
                //cout << "input2: " << input << endl << "length: " << input.length() << endl;
                cout << endl;
                server_message.clear();
                server_message = divide_str(input, 1) + divide_str(input, 2);
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                break;
            case 2:
                server_message = "Enter your string and character: ";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                recv(client_socket, &buf, sizeof(buf), 0);
                input.assign(buf);
                cout << endl;
                server_message.clear();
                //cout << divide_str(input, 1) << "  " << divide_str(input, 2) << endl;
                server_message = to_string(divide_str(input, 1).find(divide_str(input, 2)));
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                break;
            case 3:
                server_message = "Enter your string: ";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                recv(client_socket, &buf, sizeof(buf), 0);
                input.clear();
                input.assign(buf);
                cout << "input2: " << input << endl
                     << "length: " << input.length() << endl;
                cout << endl;
                server_message.clear();
                cout << divide_str(input, 1) << "  " << divide_str(input, 2) << endl;
                server_message = divide_str(input, 1).compare(divide_str(input, 2)) != 0 ? "false" : "true";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                break;
            case 4:
                server_message = "Enter your string: ";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                recv(client_socket, &buf, sizeof(buf), 0);
                input.clear();
                input.assign(buf);
                cout << "input2: " << input << endl
                     << "length: " << input.length() << endl;
                cout << endl;
                server_message.clear();
                server_message = isPalindrome(input) ? "String is a Palindrome" : "String is not a Palindrome";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                break;
            case 5:
                server_message = "Enter your numbers: ";
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                recv(client_socket, &buf, sizeof(buf), 0);
                input.clear();
                input.assign(buf);
                cout << "input2: " << input << endl
                     << "length: " << input.length() << endl;
                cout << endl;
                server_message.clear();
                server_message = addNumbers(divide_str(input, 1), divide_str(input, 2));
                send(client_socket, server_message.c_str(), strlen(server_message.c_str()), 0);
                break;
            default:
                break;
            }
            close(server_socket);
        }
        else
        {
            close(client_socket);
        }
    }
    return 0;
}
