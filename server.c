#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
int main(){
  
//============================================ SOCKET INITIALISATIONS =====================================================================================================
  
  char clientRequestSourceDestination[100];
    //create the server socket
   int socketDescriptor = socket(AF_INET,SOCK_STREAM,0);
  
  //define the server address
  //creating the address as same way we have created for TCPclient
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9002);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  //calling bind function to our specified IP and port
  if(bind(socketDescriptor,(struct sockaddr*) &serverAddress,sizeof(serverAddress)))
  printf("Server Started.....\n");
  if(listen(socketDescriptor,5))
  printf("listining to clients.....");
  //starting the accepting 
  //accept(socketWeAreAccepting,structuresClientIsConnectingFrom,)
  int client_socket = accept(socketDescriptor, NULL, NULL);
  
  //sending data
  //send(toWhom,Message,SizeOfMessage,FLAG);
  //send(client_socket,serverMessage,sizeof(serverMessage),0);
  recv(client_socket, &clientRequestSourceDestination, sizeof(clientRequestSourceDestination), 0);
  printf("Client sent the Source_Destination as : %s\n",clientRequestSourceDestination);
  
// ================================= SENDING FLIGHT DETAILS =====================================================================================================

  FILE* airline;
  airline = fopen("airlines.txt","r");
  
  char line[100];
  int line_no = 0;
 if (airline == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    char sourceDestinationFile[30];
    char time[10];
    char price[10];
    char timeOfFlight[10];
    char flightNo[10];
    char flightDataBuffer[1000] = "";
    int i = 0;
    // char** flightDataBufferArray;
        strcat(clientRequestSourceDestination, "\n");

    while (1)
    {
        if (feof(airline))
        {
            printf("\nreached end of file....\n");
            break;
        }
        fgets(sourceDestinationFile, 30, airline);
        fgets(time, 10, airline);
        fgets(price, 10, airline);
        fgets(timeOfFlight, 10, airline);
        fgets(flightNo, 10, airline);
        fgetc(airline);
        printf("clientRequestSourceDestination : %s",clientRequestSourceDestination);
        printf("sourceDestinationFile : %s\n",sourceDestinationFile);

        if (strcmp(sourceDestinationFile, clientRequestSourceDestination) == 0)
        {
            strcat(flightDataBuffer, "Time : ");

            strcat(flightDataBuffer, time);

            strcat(flightDataBuffer, "Price : ");

            strcat(flightDataBuffer, price);

            strcat(flightDataBuffer, "Time of Flight : ");

            strcat(flightDataBuffer, timeOfFlight);

            strcat(flightDataBuffer, "Flight Number : ");

            strcat(flightDataBuffer, flightNo);

            strcat(flightDataBuffer, "\n");

        }

    }
            send(client_socket,flightDataBuffer,1000,0);

            printf("flightDataBuffer : \n%s\n",flightDataBuffer);
// =============================== BOOKING THE FLIGHT ==========================================================================================================
  
  FILE* bookings;
  bookings = fopen("bookings.txt","a");
  char passengerDetailsBuffer[100];
  recv(client_socket, &passengerDetailsBuffer,sizeof(passengerDetailsBuffer),0);
printf("\nbookingDetailsBuffer : \n%s\n",passengerDetailsBuffer);

fputs(passengerDetailsBuffer,bookings);

// =========================================================================================================================================
  //close the socket
  close(socketDescriptor);
  //close the file
  fclose(airline);
    return 0;
}

   