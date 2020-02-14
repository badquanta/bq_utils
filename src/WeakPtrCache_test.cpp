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
    TempStructCache cache1(stdMakeShared<TempStruct>);
    CHECK_EQ(cache1.countAlive(),0);
    TempStructCache::shared_ptr ptr = cache1.get_sptr(22);
    CHECK_EQ(cache1.countAlive(),1);
    ptr->complex = 1.1;
    ptr->something=24;
    TempStructCache::shared_ptr ptr2 = cache1.get_sptr(22);
    CHECK_EQ(cache1.countAlive(),1);
    CHECK_EQ(ptr2->something,ptr->something);
    ptr=nullptr;
    CHECK_EQ(cache1.countAlive(),1);
    ptr = cache1.get_sptr(21);
    CHECK_EQ(cache1.countAlive(),2);
    ptr2=nullptr;
    CHECK_EQ(cache1.countAlive(),1);
    ptr=nullptr;
    CHECK_EQ(cache1.countAlive(),0);
  }

} /* namespace bqpd */
