/*
 * WeakPtrCache
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
#define BQPD_WEAKPTR_PAIR <class Key, class Base>
  /**
   * This will just call `std::make_shared` with the specified ...Args
   */
  template<class Key, class Base, typename ...Args>
  std::shared_ptr<Base> stdMakeShared(Key k, Args ...args) {
    return std::make_shared<Base>(args...);
  }
  /** This will call `std::make_shared<Base>(Key) **/
  template<class Key, class Base>
  std::shared_ptr<Base> stdMakeSharedKey(Key k){
    return std::make_shared<Base>(k);
  }
  /**
   * This WeakPtrCache indexes via a `Key` instances of `std::shared_ptr` as a `map` of
   * `std::weak_ptr`s.
   * `Key` refers to the symbol by which instances are referred to; other than pointers. */
  template<class Key, class Base, typename ...Args>
  class WeakPtrCache {
    public:
      /** std::shared_ptr, Using the `Base` specified **/
      typedef std::shared_ptr<Base> shared_ptr;
      /** std::weakptr, using the `Base` specified **/
      typedef std::weak_ptr<Base> weak_ptr;
      /** std::map of key->weak_ptr pairs. **/
      typedef std::map<Key, weak_ptr> map;
      typedef std::function<shared_ptr(Key, Args...)> MakeInstance_f;
      typedef std::function<shared_ptr(Key)> MakeDefault_f;
      MakeInstance_f makeInstance;
      MakeDefault_f makeDefault;
    protected: // internal std::weak_ptr map
      map fCache;
      std::mutex mutex;

    public:
      /**
       * Constructs a "Weak Pointer Cache"
       * Template argument will be the map's key.
       * If a function is given to this constructor;
       * it will be used with `ensure_sptr` to construct
       * instances for cache misses.
       */
      WeakPtrCache(MakeInstance_f mi = nullptr, MakeDefault_f md =
          nullptr)
          : makeInstance { mi }, makeDefault { md } {

      }
      /**
       * Ensures the cache has an instance for key,
       * if it does it returns that existing instance.
       * if it does not it will try to call makeInstance with
       * `key` and `Args...args`; then store that new instance
       * at `key` and return that new instance's `std::shared_ptr`.
       */
      shared_ptr ensure_sptr(Key key, Args ...args) {
        std::lock_guard<std::mutex> hold(mutex);
        auto sp = fCache[key].lock();
        if ((!sp) && (makeInstance != nullptr)) fCache[key] = sp =
            makeInstance(key, args...);
        return sp;
      }
      /**
       * This will try to get the cache instance for `key`.
       * If that entry is nullptr; it will try to run `makeDefault`
       * giving it the `key`.
       */
      shared_ptr get_sptr(Key key) {
        std::lock_guard<std::mutex> hold(mutex);
        auto sp = fCache[key].lock();
        if ((!sp) && (makeDefault != nullptr)) fCache[key] = sp =
            makeDefault(key);
        return sp;
      }
      /**
       * The original implementation of this template was a function;
       * and this operator overload maintains that function-ality.
       */
      shared_ptr operator()(Key key) {
        return get_sptr(key);
      }
      /**
       * Simple helper that travels through the cach entries and
       * returns the count that are still "alive"
       */
      int countAlive() {
        int count = 0;
        for (auto it = fCache.begin(); it != fCache.end(); ++it) {
          auto item = it->second.lock();
          if (item != nullptr) {
            count++;
            item = nullptr;
          }

        }
        return count;
      }
      /** Explicitly delete the following copy /assign constructors and operators
       * until I think about if/how to use them.
       */
      WeakPtrCache(const WeakPtrCache &other) = delete;
      WeakPtrCache(WeakPtrCache &&other) = delete;
      WeakPtrCache& operator=(const WeakPtrCache &other) = delete;
      WeakPtrCache& operator=(WeakPtrCache &&other) = delete;
  };
//template <class Key, class Base> std::mutex WeakPtrCache<Key,Base>::mutex;
//template <class Key, class Base> std::map<Key,std::weak_ptr<Base>> WeakPtrCache<Key,Base>::fCache;
//template <class Key, class Base> std::function<std::shared_ptr<Base>(Key)> WeakPtrCache<Key,Base>::makeInstanceFunc;
} /* namespace bq */

#endif /* WEAKPTRCACHE_HPP_ */
