//
// Created by huan.yang on 2022-04-27.
//

#include <memory>
#include "SocketFactory.h"
#include "../warpper/Socket.h"


namespace halosky { namespace factory {


        int SocketFactory::build_socket() {

            std::make_signed<warpper::DefaultSocketConfig>();


        }

}}
