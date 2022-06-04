// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#define PORT 8080
#define MAXLINE 3096

int countchar(string s, char c)
{
    int count = 0;
    for (int counter = 0; counter < s.length(); counter++)
    {
        if (s[counter] == c)
        {
            count++;
        }
    }
    return count;
}

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
// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    //memset(&servaddr, 0, sizeof(servaddr));
    //memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int n;
    string s, response = "";
    socklen_t len;
    fstream file;
    len = sizeof(cliaddr); //len is value/resuslt

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     0, (struct sockaddr *)&cliaddr,
                     &len);
        buffer[n] = '\0';
        string request(buffer);
        cout << "request: " << request << endl << countchar(request, '-') << endl;
            string files[countchar(request, '-')];
            for (int counter = 1; counter <= countchar(request, '-'); counter++)
            {
                response += divide_str(request, counter) + ":\n";
                cout << "filename: " << divide_str(request, counter) << "helloworld" << endl;
                file.open(divide_str(request, counter));
                while (!file.eof())
                {
                    getline(file, s);
                    response += s;
                }
                response += '\n';
                file.close();
                //cout << "response:" << response << endl;
            }
        //printf("Client request: %s\n", buffer);
        // file.open(buffer);
        // while (!file.eof())
        // {
        //     getline(file, s);
        //     response += s;
        // }
        sendto(sockfd, response.c_str(), strlen(response.c_str()),
               0, (const struct sockaddr *)&cliaddr,
               len);


    // printf("Hello message sent.\n");

    return 0;
}