#ifndef ZHANMM_CACHE_H
#define ZHANMM_CACHE_H
#include<string>



namespace zhanmm {

class Cache {
public:
  Cache() = default;
  Cache(const Cache&) = delete;
  Cache& operator=(const Cache&) = delete;

  // Destroys all existing entries by calling the "deleter"
  // function that was passed to the constructor.
  virtual ~Cache() {}


  virtual bool Set(const std::string& key, const std::string& value, int expire_time = -1) = 0;


  virtual std::string Get(const std::string& key) = 0;


  virtual bool ExpireKey(const std::string& key, int expire_time) = 0;

  virtual const std::string&  Name() const = 0;

};

} //namespace zhanmm

#endif



