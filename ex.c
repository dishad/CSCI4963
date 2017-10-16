#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int sockfd, clientlen, portno, n, newSocket;
  char buffer[256];
  struct sockaddr_in serverAddr, clientAddr, ;
  struct sockaddr_storage serverStorage;

  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(7891);


  /* Set port number, using htons function to use proper byte order */

  /* Set IP address to localhost */
  // int len = 20;
  // char str[len];
  // inet_ntop( AF_INET, &serverAddr.sin_addr, str, len);  
  // printf("IP address is: %s\n", str); 
  //  inet_ntoa(serverAddr.sin_addr.s_addr));
  // SET IP ADDRESS
  // SET PORT 
  //printf("IP address is: %s\n", inet_ntoa(serverAddr.sin_addr.s_addr));
  /* Set all bits of the padding field to 0 */
  // memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*ddress is: %s\n", inet_ntoa(client_addr.sin_addr));---- Bind the address struct to the socket ----*/
  if (bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    error("ERROR on binding");
  
  bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(sockfd, 5) == 0)
    printf("Listening\n");
  else
    printf("Error\n");

  clientlen = sizeof clientAddr;
  while (1) {
    newSocket = accept(sockfd, (struct sockaddr *) &clientAddr, &clientlen);
         if (newSocket < 0)
             error("ERROR on accept");
         n = fork();
         if (n < 0)
             error("ERROR on fork");
         if (n == 0)  {
             close(sockfd);
             printf('hi');
            //  dostuff(newSocket);
             exit(0);
         }
         else close(newsockfd);
  } 
  /* end of while */
  close(sockfd);

  /*---- Accept call creates a new socket for the incoming connection ----*/
  // newSocket = accept(sockfd, (struct sockaddr *) &clientAddr, &clientlen);
// 
  // if (newSocket < 0) 
    // error("ERROR on accept");

  // bzero(buffer,256);
  // n = read(newSocket, buffer, 255);
  
  // if (n < 0) 
    // error("ERROR reading from socket");

  // printf("Here is the message: %s\n",buffer);
  
  /*---- Send message to the socket of the incoming connection ----*/
  // strcpy(buffer,"Hello World\n");
  // send(newSocket,buffer,13,0);

  return 0;
}
