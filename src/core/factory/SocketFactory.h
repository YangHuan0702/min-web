//
// Created by huan.yang on 2022-04-27.
//

#ifndef MIN_WEB_SOCKETFACTORY_H
#define MIN_WEB_SOCKETFACTORY_H

#include "../warpper/Socket.h"

namespace halosky { namespace factory {
    class SocketFactory{

        /**
         * 构建Socket描述符
         * @param socket Socket FD
         * @return
         */
        static int build_socket();
    };
}}

#endif //MIN_WEB_SOCKETFACTORY_H
