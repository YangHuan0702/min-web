//
// Created by huan.yang on 2022-04-28.
//

#include "log.h"
#include <pthread.h>
#include <cstring>
#include <sys/time.h>
#include <cstdarg>

using namespace halosky::log;

log::log() {
    m_count = 0;
    m_is_async = false;
}

log::~log() {
    if (m_fp != NULL) {
        fclose(m_fp);
    }
}

bool log::init(char *file_name, int close_log, int log_buf_size, int split_lines, int max_queue_size) {

    // 如果设置了max_queue_size，则设置为异步
    if (max_queue_size >= 0) {
        m_is_async = true;
        m_log_queue = new block_queue<std::string>(max_queue_size);
        pthread_t tid;
        // flush_log_thread为回调函数，这里表示创建线程异步写日志
        pthread_create(&tid, NULL, flush_log_thread, NULL);
    }


    m_close_log = close_log;
    m_log_buf_size = log_buf_size;
    m_buf = new char[m_log_buf_size];
    memset(m_buf, '\0', m_log_buf_size);
    m_split_lines = split_lines;

    char log_full_name[256] = {0};


    time_t t = time(NULL);
    struct tm *sys_tm = localtime(&t);
    struct tm my_tm = *sys_tm;

    const char *p = strrchr(file_name, '/');

    // 如果find函数没有找到，则返回一个特别的标志，c++中用npos表示
    if (p != nullptr) {
        strcpy(log_name, p + 1);
        strncpy(dir_name, file_name, p - file_name + 1);
    }
    snprintf(log_full_name, 255, "%s%d_%02d_%02d,%s", dir_name, my_tm.tm_year + 1900, my_tm.tm_mon + 1,
             my_tm.tm_mday, file_name);

    m_today = my_tm.tm_mday;

    m_fp = fopen(log_full_name, "a");
    if (m_fp == NULL) {
        return false;
    }
    return true;
}


void log::write_log(int level, const char *format, ...) {


    struct timeval now = {0, 0};
    gettimeofday(&now, NULL);
    time_t t = now.tv_sec;
    struct tm *sys_tm = localtime(&t);
    struct tm my_tm = *sys_tm;
    std::string title;
    switch (level) {
        case 0:
            title = "[debug]:";
            break;
        case 1:
            title = "[info]:";
            break;
        case 2:
            title = "[warn]:";
            break;
        case 3:
            title = "[error]:";
            break;
        default:
            title = "[info]:";
            break;
    }


    // 写一个log,对m_count++, m_split_lines最大行数
    m_mutex.lock();
    m_count++;

    if (m_today != my_tm.tm_mday || m_count % m_split_lines == 0) {
        fflush(m_fp);
        fclose(m_fp);

        char nowlog[256] = {0};
        char tail[16] = {0};
        snprintf(tail, 16, "%d_%02d_%02d_", my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday);

        if (m_today != my_tm.tm_mday) {
            snprintf(nowlog, 255, "%s%s%s", dir_name, tail, log_name);
            m_today = my_tm.tm_mday;
            m_count = 0;
        } else {
            snprintf(nowlog, 255, "%s%s%s.%lld", dir_name, tail, log_name, m_count / m_split_lines);
        }
        m_fp = fopen(nowlog, "a");
    }

    m_mutex.unlock();

    va_list vaList;
    //va_start使argp指向第一个可选参数
    va_start(vaList, format);

    std::string log_str;

    m_mutex.lock();

    // 写入的具体时间内容格式
    int n = snprintf(m_buf, 45, "%d-%02d-%02d %02d:%02d:%02d.%06ld %s",
                     my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday,
                     my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, now.tv_usec, title.c_str());

    int m = vsnprintf(m_buf + n, m_log_buf_size - 1, format, vaList);

    m_buf[n + m] = '\n';
    m_buf[n + m + 1] = '\0';
    log_str = m_buf;

    m_mutex.unlock();

    if (m_is_async && !m_log_queue->full())
    {
        m_log_queue->push(log_str);
    }
    else
    {
        m_mutex.lock();
        fputs(log_str.c_str(), m_fp);
        m_mutex.unlock();
    }

    va_end(vaList);
}

void log::flush()
{
    m_mutex.lock();
    //强制刷新写入流缓冲区
    fflush(m_fp);
    m_mutex.unlock();
}
