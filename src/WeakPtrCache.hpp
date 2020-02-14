/*
 * SharedPtrCache.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef WEAKPTRCACHE_HPP_
#define WEAKPTRCACHE_HPP_
#include <memory>
#include <map>
#include <mutex>
#include <functional>
namespace bq {
#define BQPD_WEAKPTR_PAIR <class Key, class base>
  template<class base,typename ...Args>
  std::shared_ptr<base> stdMakeShared(Args...args){
      return std::make_shared<base>(args...);
  }
  /**
   * `Key` refers to the symbol by which instances are referred to; other than pointers.
   */
  template<class Key, class base, typename ...Args>
  class WeakPtrCache {
    public:
      typedef std::shared_ptr<base> shared_ptr;
      typedef std::weak_ptr<base> weak_ptr;
      typedef std::map<Key, weak_ptr> map;
      typedef std::function<shared_ptr(Args...)> key_make_shared_f;
      key_make_shared_f makeSharedFunc;
    protected:// internal std::weak_ptr map
      map fCache;
      std::mutex mutex;


    public:
      WeakPtrCache(key_make_shared_f f):makeSharedFunc{f}{

      }
      shared_ptr get_sptr(Key key, Args...args){
        std::lock_guard<std::mutex> hold(mutex);
        auto sp = fCache[key].lock();
        if(!sp) fCache[key] = sp = makeSharedFunc(args...);
        return sp;
      }
      shared_ptr operator()(Key key){
        return get_sptr(key);
      }
      int countAlive(){
        int count = 0;
        for(auto it = fCache.begin(); it!=fCache.end(); ++it){
          auto item = it->second.lock();
          if(item!=nullptr){count++;item=nullptr;}

        }
        return count;
      }
      WeakPtrCache(const WeakPtrCache &other)=delete;
      WeakPtrCache(WeakPtrCache &&other)=delete;
      WeakPtrCache& operator=(const WeakPtrCache &other)=delete;
      WeakPtrCache& operator=(WeakPtrCache &&other)=delete;
  };
  //template <class Key, class base> std::mutex WeakPtrCache<Key,base>::mutex;
  //template <class Key, class base> std::map<Key,std::weak_ptr<base>> WeakPtrCache<Key,base>::fCache;
  //template <class Key, class base> std::function<std::shared_ptr<base>(Key)> WeakPtrCache<Key,base>::makeSharedFunc;
} /* namespace bq */

#endif /* WEAKPTRCACHE_HPP_ */
