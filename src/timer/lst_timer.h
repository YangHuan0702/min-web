//
// Created by huan.yang on 2022-04-29.
//

#ifndef MIN_WEB_LST_TIMER_H
#define MIN_WEB_LST_TIMER_H

#include <sys/socket.h>
#include <netinet/in.h>

namespace halosky { namespace timer {
class util_timer;

struct client_data{
    sockaddr_in address;
    int sockfd;
    util_timer *u_time;
};
class util_timer{

public:
    util_timer():prev(nullptr),next(nullptr){}

public:
    time_t expire;

    void (* cb_func)(client_data *);

    client_data *user_data;

    util_timer *prev;

    util_timer *next;
};

class sort_timer_lst{

public:
    sort_timer_lst();
    ~sort_timer_lst();


    void add_timer(util_timer *timer);

    void adjust_timer(util_timer *timer);

    void del_time(util_timer *timer);

    void tick();


private:
    void add_timer(util_timer *timer,util_timer *lst_head);

    util_timer *head;

    util_timer *tail;
};


class util{

public:
    util(){}
    ~util(){}

    void init(int time_slot);

    // 对文件描述设置非阻塞
    int set_non_blocking(int fd);

    // 将内核事件表注册读事件，ET模式，选择开启EPOLL ONE SHOT
    void addfd(int epollfd,int fd,bool one_shot,int trig_model);

    // 信号处理函数
    static void sig_handler(int sig);

    // 设置信号函数
    void addsig(int sig,void(handler)(int),bool restart = true);

    // 定时处理任务，重新定时以不断出发SIGALRM信号
    void timer_handler();

    void show_error(int connfd,const char *info);


public:
    static int *u_pipefd;

    sort_timer_lst m_timer_lst;

    static int u_epollfd;

    int m_time_slot;
};

void cb_func(client_data *user_data);

}}


#endif //MIN_WEB_LST_TIMER_H
