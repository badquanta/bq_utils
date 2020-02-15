/*
 * SharedPtrCache_test.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "WeakPtrCache.hpp"

namespace bq {
  TEST_CASE("bq::utilsWeakPtrCache"){
    class TempStruct {
      public:
        int something=0;
        float complex=0;
    };
    typedef WeakPtrCache<int, TempStruct> TempStructCache;
    TempStructCache cache1(stdMakeShared<int, TempStruct>);
    CHECK_EQ(cache1.countAlive(),0);
    TempStructCache::shared_ptr ptr = cache1.ensure_sptr(22);
    CHECK_EQ(cache1.countAlive(),1);
    ptr->complex = 1.1;
    ptr->something=24;
    TempStructCache::shared_ptr ptr2 = cache1.get_sptr(22);
    CHECK_EQ(cache1.countAlive(),1);
    CHECK_EQ(ptr2->something,ptr->something);
    ptr=nullptr;
    CHECK_EQ(cache1.countAlive(),1);
    ptr = cache1.ensure_sptr(21);
    CHECK_EQ(cache1.countAlive(),2);
    ptr2=nullptr;
    CHECK_EQ(cache1.countAlive(),1);
    ptr=nullptr;
    CHECK_EQ(cache1.countAlive(),0);
  }

  TEST_CASE("test with 1 constructor param"){
    class MyClass {
      public:
        float param;
        MyClass(float p):param{p}{

        }
    };

    typedef WeakPtrCache<int, MyClass, float> MyClassCache;
    MyClassCache mcc(stdMakeShared<int, MyClass, float>);
    CHECK_EQ(mcc.countAlive(),0);
    MyClassCache::shared_ptr ptr1 = mcc.get_sptr(60);
    CHECK_EQ(nullptr, ptr1);
    CHECK_EQ(mcc.countAlive(),0);
    ptr1 = mcc.ensure_sptr(60,60.0);
    CHECK_NE(nullptr, ptr1);
    CHECK_EQ(mcc.countAlive(), 1);
    ptr1 = nullptr;
    CHECK_EQ(mcc.countAlive(),0);
  }

} /* namespace bqpd */
