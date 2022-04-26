//
// Created by huan.yang on 2022-04-26.
//
#ifndef halosky_base_Environment_hpp

#define halosky_base_Environment_hpp

#include "./config.h"
#include <cstdlib>
#include <atomic>
#include <string>
#include <cstdio>

typedef unsigned char v_char8;
typedef v_char8 *p_char8;

typedef int8_t v_int8;
typedef v_int8 *p_int8;
typedef uint8_t v_uint8;
typedef v_uint8 *p_uint8;

typedef int16_t v_int16;
typedef v_int16 *p_int16;
typedef uint16_t v_uint16;
typedef v_uint16 *p_uint16;

typedef int32_t v_int32;
typedef v_int32 *p_int32;
typedef uint32_t v_uint32;
typedef v_uint32 *p_uint32;

typedef int64_t v_int64;
typedef v_int64 *p_int64;
typedef uint64_t v_uint64;
typedef v_uint64 *p_uint64;

typedef double v_float64;
typedef v_float64 *p_float64;

typedef float v_float32;
typedef v_float32 *p_float32;

typedef std::atomic_int_fast64_t v_atomicCounter;
typedef v_int64 v_counter;


/**
 * 该类型是能够存储指针的整数类型。因此能够存储分配内存的大小。
 * 使用此类型定义缓冲区的大小。
 */
typedef intptr_t v_buff_size;
typedef v_buff_size *p_buff_size;

typedef uintptr_t v_buff_usize;
typedef v_buff_usize *p_buff_usize;


namespace halosky {

    namespace base {

        /**
         * constexpr关键字：
         * C++ 11标准中，为了解决 const 关键字的双重语义问题，保留了 const 表示“只读”的语义，而将“常量”的语义划分给了新添加的 const 关键字。
         * 因此 C++11 标准中，建议将 const 和 const 的功能区分开，即凡是表达“只读”语义的场景都使用 const，表达“常量”语义的场景都使用 const
         *
         * const表达式是指值不会改变并且在编译过程就能得到计算结果的表达式。声明为const的变量一定是一个const变量
         *
         * 系统范围 Logger 的接口。
         * 所有对 `OATPP_DISABLE_LOGV`、`OATPP_DISABLE_LOGD`、`OATPP_DISABLE_LOGI`、`OATPP_DISABLE_LOGW`、`OATPP_DISABLE_LOGE` 的调用都将在此处进行。
         */
        class Logger {
        public :
            /**
              * Log priority V-verbouse.
            */
            static const v_uint32
            PRIORITY_V = 0;

            /**
             * Log priority D-debug.
             */
            static const v_uint32
            PRIORITY_D = 1;

            /**
             * Log priority I-Info.
             */
            static const v_uint32
            PRIORITY_I = 2;

            /**
             * Log priority W-Warning.
             */
            static const v_uint32
            PRIORITY_W = 3;

            /**
             * Log priority E-error.
             */
            static const v_uint32
            PRIORITY_E = 4;

        public:
            virtual ~Logger() = default;

            /**
             * 使用优先级、标签、消息记录消息
             * @param priority -  消息的优先通道
             * @param tag - 日志消息的标记
             * @param message - 消息
             */
            virtual void log(v_uint32 priority, const std::string& tag, const std::string& message) = 0;

            /**
             * 返回是否应记录打印的优先级
             * @param priority
             * @return - true 如果应该记录给定的优先级
             */
            virtual bool isLogPriorityEnabled(v_uint32 priority) {
                return true;
            }

            /**
             * 应该返回应该为单个日志消息分配的最大字节数
             * @return - 最大缓冲区大小
             */
            virtual v_buff_size getMaxFormattingBufferSize() {
                return 4096;
            }
        };


        /**
         * 描述日志类别（即日志“命名空间”）
         */
        class LogCategory{

        public:
            /**
             * 日志类别构造函数
             * @param pTag - 此日志记录类别的标签
             * @param pCategoryEnabled - 完全启用或禁用类别
             * @param pEnabledPriorities - 初始活动日志记录类别的位图。
             */
            LogCategory(std::string pTag, bool pCategoryEnabled, v_uint32 pEnabledPriorities = ((1<<Logger::PRIORITY_V) | (1<<Logger::PRIORITY_D) | (1<<Logger::PRIORITY_I) | (1<<Logger::PRIORITY_W) | (1<<Logger::PRIORITY_E)))
                    : tag(std::move(pTag))
                    , categoryEnabled(pCategoryEnabled)
                    , enabledPriorities(pEnabledPriorities)
            {};

        };

    }
}


#endif