// Client side implementation of UDP client-server model
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
using namespace std;

#define PORT 8080
#define MAXLINE 2048

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    //memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    string request = "", requests = "", det = "";
    int n = 0, detail = 0;
    socklen_t len;
        while (1)
        {
            cout << "Enter movie number from list below or press 0 to send request: \n"
                 << "1. The Matrix Revolutions\n2. The Godfather\n3. The Expendables I\n4. Star Wars Episode I - The Phantom Menace\n5. Les Miserables\n6. Clash of the Titans\n7. Avatar\n8. Amadeus\n9. 2012\n10. A Beautiful Mind\n";
            cin >> n;
            if (n == 0)
            {
                break;
            }
            cout << "Enter the detail of movie you want: \n"
                 << "1. Ratings\n2. Polarity\n3. Sentiments\n";
            cin >> detail;
            switch (detail)
            {
            case 1:
                det = "ratings.txt";
                break;

            case 2:
                det = "polarity.txt";
                break;

            case 3:
                det = "sentiments.txt";
                break;
            default:
                break;
            }
            switch (n)
            {
            case 1:
                requests = "The Matrix Revolutions";
                break;
            case 2:
                requests = "The Godfather";
                break;
            case 3:
                requests = "The Expendables I";
                break;
            case 4:
                requests = "Star Wars Episode I - The Phantom Menace";
                break;
            case 5:
                requests = "Les Miserables";
                break;
            case 6:
                requests = "Clash of the Titans";
                break;
            case 7:
                requests = "Avatar";
                break;
            case 8:
                requests = "Amadeus";
                break;
            case 9:
                requests = "2012";
                break;
            case 10:
                request = "A Beautiful Mind";
                break;
            default:
                break;
            }
            request += requests + "/" + det + "-";
        }
        sendto(sockfd, request.c_str(), strlen(request.c_str()),
               0, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     0, (struct sockaddr *)&servaddr,
                     &len);
        buffer[n] = '\0';
        printf("Server response: %s\n", buffer);

    close(sockfd);
    return 0;
}