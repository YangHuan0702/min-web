//
// Created by huan.yang on 2022-04-28.
//

#include "config.h"

using namespace halosky::config;

config::config() {
    // 端口
    port = 8014;

    //日志写入方式
    log_type = 0;

    // 触发组合模式
    trig_model = 0;

    // listenfd触发模式
    listen_fd_model = 0;

    // config触发模式
    config_model = 0;

    // 优雅关闭
    opt_stop = 0;

    // 线程池线程数量
    thread_num = 8;

    // 是否关闭日志
    close_log = 0;

    // 并发模式选择
    atomic_model = 0;
};