//  Created by Kerim Njuhović on 6/6/15.
//  Copyright (c) 2015 Kerim Njuhovic. All rights reserved.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 60345
#define BUF_SIZE 4096
#define QUEUE_SIZE 10

#define EXECUTION_MODE "client"
void printTimer(double, int, char*, char*);
void returnIpAddress(struct hostent  *hp, char*);
char* returnExtractedFileName(char *path);
void sendEmail();
int main(int argc, const char * argv[]) {
    ///////////////////////////////////////////
    //>>>>>>>> C L I E N T    M O D E <<<<<<<<<
    ///////////////////////////////////////////
        time_t start,end;
        start=clock();
        int c, s, bytes, fileSize;
        char buf[BUF_SIZE];
        struct hostent *h;
        struct sockaddr_in channel;
        
        if (argc != 3)
            fatal("Usage: client server-name file-name");
        h = gethostbyname(argv[1]);
        
        if (!h) fatal("gethostbyname failed");
            s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s <0)
            fatal("socket");
        memset(&channel, 0, sizeof(channel));
        channel.sin_family= AF_INET;
        memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
        channel.sin_port= htons(SERVER_PORT);
        
        c = connect(s, (struct sockaddr*) &channel, sizeof(channel));
        if (c < 0)
            fatal("connect failed");
        
        write(s, argv[2], strlen(argv[2])+1);
        end = clock();
    
        double difference = end - start;
        char ip[100];
        returnIpAddress(h, ip);
        printTimer(difference, fileSize, ip, returnExtractedFileName(argv[2]));
        char to1[256];
        char from1[256];
        char message1[256];
        char sub1[256];
    
        while (1) {
            bytes = read(s, buf, BUF_SIZE);
            if (bytes <= 0)
                exit(0);
            write(1, buf, bytes);
        }
    return 0;
}
fatal(char*string)
{
    printf("%s\n", string);
    exit(1);
}
void printTimer(double difference, int sizeOfFile, char *host, char*fileName){
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    double msec = (double)(difference)/ CLOCKS_PER_SEC;
    FILE *f = fopen("/Applications/XAMPP/xamppfiles/htdocs/FileTransferProtocol/fileNo77.html", "a");
    if (f == NULL)
    {
        printf("\nError opening LOG file!");
        exit(1);
    }
    fprintf(f, "\n<h3>Date of transfer: %s | Transfer duration: %f seconds | Host:%s | File name: %s</h3>", asctime (timeinfo), msec*1000, host, fileName);
    sendEmail();
}
void returnIpAddress(struct hostent  *he, char* ip){
    struct in_addr **addr_list;
    int i;
    
    addr_list = (struct in_addr **) he->h_addr_list;
    
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
    }
}
void sendEmail(){
    system("osascript /Users/kerimnjuhovic/Documents/client/client/send_email.scpt");
}
char* returnExtractedFileName(char *path){
    char *ssc;
    int l = 0;
    ssc = strstr(path, "/");
    do{
        l = strlen(ssc) + 1;
        path = &path[strlen(path)-l+2];
        ssc = strstr(path, "/");
    }while(ssc);
    
    return path;
}