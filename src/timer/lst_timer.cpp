//
// Created by huan.yang on 2022-04-29.
//

#include "lst_timer.h"

namespace halosky {
    namespace timer {


        sort_timer_lst::sort_timer_lst() {
            head = nullptr;
            tail = nullptr;
        }

        sort_timer_lst::~sort_timer_lst() {
            util_timer *tmp = head;
            while (tmp) {
                head = tmp->next;
                delete tmp;
                tmp = head;
            }
        }

        void sort_timer_lst::add_timer(util_timer *timer) {
            if (!timer) {
                return;
            }
            if (!head) {
                head = tail = timer;
                return;
            }
            if (timer->expire < head->expire) {
                timer->next = head;
                head->prev = timer;
                head = timer;
                return;
            }
            add_timer(timer, head);
        }


        void sort_timer_lst::adjust_timer(util_timer *timer) {
            if (!timer) {
                return;
            }
            util_timer *tmp = timer->next;
            if (!tmp || (timer->expire < tmp->expire)) {
                return;
            }
            if (timer == head) {
                head = head->next;
                head->prev = nullptr;
                timer->next = nullptr;
                add_timer(timer, head);
            } else {
                timer->prev->next = timer->next;
                timer->next->prev = timer->prev;
                add_timer(timer, timer->next);
            }
        }

        void sort_timer_lst::del_time(util_timer *timer) {
            if (!timer) {
                return;
            }
            if ((timer == head) && (timer == tail)) {
                delete timer;
                head = nullptr;
                tail = nullptr;
                return;
            }
            if (timer == head) {
                head = head->next;
                head->prev = nullptr;
                delete timer;
                return;
            }
            if (timer == tail) {
                tail = tail->prev;
                tail->next = nullptr;
                delete timer;
                return;
            }
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            delete timer;
        }

    }
}