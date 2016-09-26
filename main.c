

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <string.h>

/*
 * 網路程式
 * 1. ip 位置
 * 2. bind (port 0~65535)
 */

int main(int argc, char *argv[]) {
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000];
//Create socket
    /**
    * @param Address Family - AF_INET (this is IP version 4)
    * @param Type - SOCK_STREAM (this means connection oriented TCP protocol)
    * @param Protocol - 0 [ or IPPROTO_IP This is IP protocol]
    * Function socket() creates a socket and returns a descriptor
    * which can be used in other functions.
    * The above code will create a socket with following properties
    */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    // check return value.
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    // ipv4 32bits
    // ipv6 128bits
    server.sin_addr.s_addr = inet_addr("106.185.40.49"); // 轉換為 32bits 位置
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // 每台電腦 cpu 不同，位元不同，host to network 轉為統一格式

//Connect to remote server
    // sizeof => bytes
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {

        // check return value.
        puts("connect error");
        return 1;
    }
    puts("Connected");
//Send some data
    message = "GET /api/data/%E7%A6%8F%E5%88%A9/10/1 HTTP/1.1\r\nHost: gank.io\r\n\r\n";
    if (send(socket_desc, message, strlen(message), 0) < 0) {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
//Receive a reply from the server
    if (recv(socket_desc, server_reply, 2000, 0) < 0) {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);
    return 0;
}


// IPv4 AF_INET sockets:
//struct sockaddr_in {
//    short            sin_family;   // e.g. AF_INET, AF_INET6
//    unsigned short   sin_port;     // e.g. htons(3490)
//    struct in_addr   sin_addr;     // see struct in_addr, below
//    char             sin_zero[8];  // zero this if you want to
//};
//struct in_addr {
//    unsigned long s_addr;          // load with inet_pton()
//};
//struct sockaddr {
//    unsigned short    sa_family;    // address family, AF_xxx
//    char              sa_data[14];  // 14 bytes of protocol address
//};

