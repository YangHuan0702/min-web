//
// Created by huan.yang on 2022-04-28.
//

#ifndef MIN_WEB_CONFIG_H
#define MIN_WEB_CONFIG_H


namespace halosky { namespace config {

    class config {
    public:
        /**
         * 构造函数
         */
        config();

        // 端口
        int port;

        //日志写入方式
        int log_type;

        // 触发组合模式
        int trig_model;

        // listenfd触发模式
        int listen_fd_model;

        // config触发模式
        int config_model;

        // 优雅关闭
        int opt_stop;

        // 线程池线程数量
        int thread_num;

        // 是否关闭日志
        int close_log;

        // 并发模式选择
        int atomic_model;

    };
}}

#endif //MIN_WEB_CONFIG_H
