#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#define MAXPENDING 5 
#define BUFFERSIZE 32 

int main(){
int serverSocket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
 if (serverSocket < 0) { printf ("Error while server socket creation"); exit (0); }
 printf ("Server Socket Created\n");  
 //creating the listening socket

struct sockaddr_in serverAddress, clientAddress;
memset (&serverAddress, 0, sizeof(serverAddress));  
serverAddress.sin_family = AF_INET;  
serverAddress.sin_port = htons(12345);  
 serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);   
 //serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
printf ("Server address assigned\n"); //its own address populated //will recieve client addr from accept


int temp = bind(serverSocket, (struct sockaddr*) &serverAddress,  sizeof(serverAddress));
if (temp < 0) { printf ("Error while binding\n");exit (0);}  
printf ("Binding successful\n"); //binding listening socket to its own addr

int temp1 = listen(serverSocket, MAXPENDING);
if (temp1 < 0){printf ("Error in listen");exit (0);}  
printf ("Now Listening\n");  //listening


char msg[BUFFERSIZE];
int clientLength = sizeof(clientAddress); 


int clientSocket = accept (serverSocket, (struct sockaddr*) &clientAddress, &clientLength);
if (clientLength < 0) {printf ("Error in client socket"); exit(0);}   
printf ("Handling Client %s\n", inet_ntoa(clientAddress.sin_addr));
//request from client accepted   


int temp2 = recv(clientSocket, msg, BUFFERSIZE, 0);
if (temp2 < 0){ printf ("problem in temp 2");exit (0);}   
printf ("%s\n", msg);  
//rcving message from client



printf ("ENTER MESSAGE FOR CLIENT\n");
fgets(msg, BUFFERSIZE, stdin);  
int bytesSent = send (clientSocket,msg,strlen(msg),0);
if (bytesSent != strlen(msg)) { printf ("Error while sending message to client");exit(0);}
//sending message to client



close (serverSocket);  close (clientSocket);  
}