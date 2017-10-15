#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */

  /* Set IP address to localhost */
  int len = 20;
  char str[len];
  inet_ntop( AF_INET, &serverAddr.sin_addr, str, len);  
  printf("IP address is: %s\n", str); 
 
//  inet_ntoa(serverAddr.sin_addr.s_addr));
  
  // SET IP ADDRESS
  serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
  // serverAddr.sin_addr.s_addr = inet_addr("172.31.18.149");

  // SET PORT 
  serverAddr.sin_port = htons(7891);

 //printf("IP address is: %s\n", inet_ntoa(serverAddr.sin_addr.s_addr));
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*ddress is: %s\n", inet_ntoa(client_addr.sin_addr));---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
  strcpy(buffer,"Hello World\n");
  send(newSocket,buffer,13,0);

  return 0;
}
