# WeThinkCode_--ft_irc-
This project implements an Internet Relay Chat (IRC) client and server, allowing the exchange of messages on TCP/IP networks.
Making use of circular buffers in order to perserve message integrity and prevent partial data reads.

# Features:
* IPV4/IPV6 compatible
* Nickname allocation
* Channel Communication
* Group Messaging
* Private Messaging

## Usage:

Update dependancies: 

    $ make update

Build:

    $ make 

Run Server:

    $ ./server [port] //ports below 1025 usually require special permissions

Run Client:

    $ ./client [host_ip] [port]

## Commands:

    //Reserve Nickname:
    $ nick [nickname]

    //Private Message:
    $ msg [nickname] [message]

    //Join Channel:
    $ join [channel_number]

    //Public Message to active channel
    $ msg [message]

    //List clients In channel:
    $ who


