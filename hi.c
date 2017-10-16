#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h> /* time for randomizer*/


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    int GuessedInteger, integerRandom, serverFlagCorrect;
    char charGuess[4], answerServer[1];
    char* delimiter = "\\n";

    /** initialization of variables **/
    serverFlagCorrect = 0;

    /** generate random integer from 1 to 100 **/
    srand (time(NULL));
    integerRandom = (rand() % 100) + 1;

    printf("This is the random integer : %d \n", integerRandom);

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    // Creates the socket socket() --> endpoints of sockets
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
       error("ERROR opening socket");
    // Creates the socket socket() --> endpoints of sockets

    // assign unique new address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
             error("ERROR on binding");
    // assign unique new address

    // wait for a connection
    listen(sockfd,5);
    // wait for a connection

    // accepts the connection
    clilen = sizeof(cli_addr);
    while (1) {
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         n = fork();
         if (n < 0)
             error("ERROR on fork");
         if (n == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     close(sockfd);
     return 0; /* we never get here */
}


    void dostuff (int sock) {
    int GuessedInteger, integerRandom, serverFlagCorrect;
    char charGuess[4], answerServer[1];
    char* delimiter = "\\n";
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    while (serverFlagCorrect != 1)
    {

        // reads the data being received
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        // reads the data being received

        printf("Buffer from client: <%s>\n", buffer);
        memcpy(charGuess, buffer, sizeof(charGuess));
        printf("Message from client in charGuess: <%s>\n", charGuess);

        /* Put if statement here for error out if no \n at the end */
        int len = strlen(charGuess);
        const char *last_two = &charGuess[len-2];

        printf("Last two characters of charGuess: <%s>\n", last_two);

        if (strncmp ( last_two, delimiter, 2) )
            error (" ERROR Wrong protocol received");

        /** turn string to int for comparison **/
        GuessedInteger = atoi(charGuess);
        printf("Guessed Integer : %d \n", GuessedInteger);

        /** Server response for comparison**/
        if (GuessedInteger > integerRandom)
            memcpy(&answerServer, "Lower", sizeof(answerServer));
        else if (GuessedInteger < integerRandom)
            memcpy(&answerServer, "Higher", sizeof(answerServer));
        else if (GuessedInteger == integerRandom)
            {
                serverFlagCorrect = 1;
                memcpy(&answerServer, "Correct", sizeof(answerServer));
            }
        printf("Value of answerServer: %c\n", *answerServer);
        /** Server response for comparison**/

        // sends the answer
        n = write(newsockfd, answerServer, 1);
        if (newsockfd < 0)
            error("ERROR on accept");
        // sends the answer

        // closes what was sent
    }
    close(newsockfd);
    }