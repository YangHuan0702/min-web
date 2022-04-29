cmake_minimum_required(VERSION 3.16)

project(min_web)

set(CMAKE_CXX_STANDARD 17)


add_library(min_web
        src/core/config.cpp
        src/core/config.h
        src/log/log.cpp
        src/log/block_queue.cpp
        src/locker/locker.cpp
        src/pool/thread_pool.h
        src/pool/thread_pool.cpp
        src/timer/lst_timer.cpp
        src/timer/lst_timer.h
        src/http/http_conn.cpp
        src/http/http_conn.h
        )

add_executable(min_app src/main.cpp)

