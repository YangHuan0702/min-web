//
// Created by huan.yang on 2022-04-26.
//

#ifndef HELLO_LIBD_CONFIG_H
#define HELLO_LIBD_CONFIG_H



/**
 * 如果未禁用，则启用 HALOSKY::base::Countable 类的所有对象的计数以用于调试目的和检测内存泄漏。
 * 使用“-D HALOSKY_DISABLE_ENV_OBJECT_COUNTERS”标志禁用发布版本的对象计数以获得更好的性能
 */
//#define HALOSKY_DISABLE_ENV_OBJECT_COUNTERS

/**
 * 定义它以禁用内存池分配。
 * 这将使 halosky::base::memory::MemoryPool, 方法获取和自由调用 new 并直接删除
 */
//#define HALOSKY_DISABLE_POOL_ALLOCATIONS

/**
 * 函数 HALOSKY::concurrency::Thread::getHardwareConcurrency() 的预定义值；
 */
//#define HALOSKY_THREAD_HARDWARE_CONCURRENCY 4

/**
 * ThreadDistributedMemoryPool 的分片数量（许多 HALOSKY 对象的默认池）数量越高，线程争用每个分片上的资源就越少。
 */
#ifndef HALOSKY_THREAD_DISTRIBUTED_MEM_POOL_SHARDS_COUNT
#define HALOSKY_THREAD_DISTRIBUTED_MEM_POOL_SHARDS_COUNT 10
#endif

/**
 * Disable `thread_local` feature. <br>
 * See https://github.com/HALOSKY/HALOSKY/issues/81
 */
//#define HALOSKY_COMPAT_BUILD_NO_THREAD_LOCAL 1

#ifndef HALOSKY_FLOAT_STRING_FORMAT
#define HALOSKY_FLOAT_STRING_FORMAT "%.16g"
#endif

/**
 * DISABLE 日志优先级 V
 */
//#define HALOSKY_DISABLE_LOGV

/**
 * DISABLE logs priority D
 */
//#define HALOSKY_DISABLE_LOGD

/**
 * DISABLE logs priority I
 */
//#define HALOSKY_DISABLE_LOGI

/**
 * DISABLE logs priority W
 */
//#define HALOSKY_DISABLE_LOGW

/**
 * DISABLE logs priority E
 */
//#define HALOSKY_DISABLE_LOGE


#endif //HELLO_LIBD_CONFIG_H
