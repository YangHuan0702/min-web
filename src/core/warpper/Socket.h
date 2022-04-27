//
// Created by huan.yang on 2022-04-27.
//

#ifndef MIN_WEB_SOCKET_H
#define MIN_WEB_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>

namespace halosky {
    namespace warpper {



        class Socket {
        public:

            int socket_domain;

            int socket_type;

            int protocol;

            int port;

            int ip;

            int max_conn;

            Socket(int domain, int type, int protocol, int port, int ip, int max_conn) :
                    socket_domain(domain), socket_type(type), protocol(protocol), port(port), ip(ip),
                    max_conn(max_conn) {}

            Socket(Socket& socket){
                this->max_conn = socket.max_conn;
                this->socket_domain = socket.socket_domain;
                this->socket_type = socket.socket_type;
                this->protocol = socket.protocol;
                this->port = socket.port;
                this->ip = socket.ip;
            }


            /**
            * Socket监听
            * @param max_conn 最大监听数
            */
            void listener(int max_conn);


            /**
             * Socket绑定
             * @param socket_fd
             * @param port
             * @param ip
             * @param family
             */
            void bind(int socket_fd, int port, int ip, int family);
        };

        class DefaultSocketConfig : public Socket {

        public :
            DefaultSocketConfig() : Socket(AF_INET,
                                           SOCK_STREAM,
                                           0, 8014,
                                           INADDR_ANY,
                                           1024) {}

        };

    }
}


#endif //MIN_WEB_SOCKET_H
