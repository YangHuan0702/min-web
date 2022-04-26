//
// Created by huan.yang on 2022-04-26.
//

#ifndef halosky_base_countable_hpp

#define halosky_base_countable_hpp

namespace  halosky{

    namespace base{
        /**
         * 可以计算其类实例化
         */
        class Countable{
        public:
            /**
             * 构造函数，递增计数器调用 @id:halosky::base::Environment::incObjects;.
             */
            Countable();


            /**
             * 拷贝构造函数，递增计数器调用 @id:halosky::base::Environment::incObjects;.
             * @param other
             */
            Countable(const Countable& other);

            /**
             * 析构函数，递减计数器调用&id:halosky::base::Environment::decObjects;.
             */
            virtual ~Countable();

        };

    }

}

#endif
