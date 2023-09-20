#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
  int socketId = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server, client;

  server.sin_family = AF_INET;
  server.sin_port = htons(8888);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  int serverlen = sizeof(server);
  int clientlen = sizeof(client);

  bind(socketId,(struct sockaddr*) &server, serverlen);

  while(1) {
    char* buffer = (char*) malloc(BUFFER_SIZE);
    memset(buffer, '\0', BUFFER_SIZE);
    recvfrom(socketId, (void*) buffer, BUFFER_SIZE, 0, (struct sockaddr*) &client, (socklen_t*) &clientlen);
    for(int i = 0; i < strlen(buffer); i++) buffer[i] = toupper(buffer[i]);
    sendto(socketId, buffer, strlen(buffer), 0, (struct sockaddr*) &client, (socklen_t) clientlen);
    free(buffer);
  }
}