#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SERVER_NAME "SERVER"
#define LISTEN_BACKLOG 10
#define MAX_CLIENTS 10
#define NICK_LENGTH 9
#define ANON_NICK "ANON"
#define MSG_SIZE 512  //RFC 1459
#define MSG_BUFFER_SIZE 1024
#define MSG_BUFFER_OVERWRITE 1
#define MSG_SEPERATOR " : "

//commands;
#define CMD_MSG "MSG"
#define CMD_WHO "WHO"

#endif