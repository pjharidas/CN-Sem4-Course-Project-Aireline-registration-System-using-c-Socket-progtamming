#include <stdio.h>
#include <stdlib.h>
//for socket and related functions
#include <sys/types.h>
#include <sys/socket.h>
//for including structures which will store information needed
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

//main functions
int main()
{
  char source[10];
  char destination[10];
  int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
// server address
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9002);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

// communicates with listen
  connect(socketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

  // char serverResponse[SIZE];
  // recv(socketDescriptor, &serverResponse, sizeof(serverResponse), 0);
  // printf("The server sent the data : %s", serverResponse);
  printf("enter the source : ");
  scanf("%s",source);
  printf("enter the destination : ");
  scanf("%s",destination);

  strcat(source,"_");
  strcat(source,destination);

  // printf("%s",source);
  char flightDataBuffer[1000];
  send(socketDescriptor,&source,sizeof(source)+sizeof(destination),0);
  recv(socketDescriptor, &flightDataBuffer, sizeof(flightDataBuffer), 0);
  printf("\n\nFollowing flights are available : \n\n%s\n",flightDataBuffer);

  char bookingDetailsBuffer[100] = "Flight Number : ";
  char flightNo[3];
  char name[20];
  char mobileNumber[14];
  char numberOfPassengers[3];


  printf("Enter flight number to proceed booking : ");
  scanf("%s",&flightNo);

  printf("Enter Following Details : \n");
  printf("Name : ");
  scanf("%s",&name);

  printf("Contact Number : ");
  scanf("%s",&mobileNumber);

  printf("Number of Passengers : ");
  scanf("%s",&numberOfPassengers);

  strcat(bookingDetailsBuffer,flightNo);

  strcat(bookingDetailsBuffer,"\nName : ");
  strcat(bookingDetailsBuffer,name);

  strcat(bookingDetailsBuffer,"\nContact Number : ");
  strcat(bookingDetailsBuffer,mobileNumber);

  strcat(bookingDetailsBuffer,"\nNo of passengers : ");
  strcat(bookingDetailsBuffer,numberOfPassengers);
  strcat(bookingDetailsBuffer,"\n\n");


printf("\nbookingDetailsBuffer : \n%s\n",bookingDetailsBuffer);

  send(socketDescriptor,&bookingDetailsBuffer,sizeof(bookingDetailsBuffer),0);

  //closing the socket
  close(socketDescriptor);
  return 0;
}