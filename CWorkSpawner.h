#pragma once
#include "ThreadPool.h"

class CContext {
 public:
  virtual int32_t Active() = 0;
  virtual int32_t Deactive() = 0;
};

class CWorker {
 public:
  virtual int32_t Run(const std::shared_ptr<CContext> c) = 0;
};

class CInterrupt {
 public:
  virtual void Interrupt(uint64_t FLAG) final;

 protected:
  virtual uint64_t InterruptTest(uint64_t FLAG) final;

 private:
  std::atomic<uint64_t> interrupt_;
};

template<int32_t thread_num>
class CWorkSpawner : private ThreadPool {
 public:
  CWorkSpawner() : ThreadPool(thread_num) {}
  virtual ~CWorkSpawner() {}

 public:
  std::future<int32_t> Spawn(const std::shared_ptr<CWorker> w,
                             const std::shared_ptr<CContext> c) {
    auto res = this->enqueue(
        [](const std::shared_ptr<CWorker> w,
           const std::shared_ptr<CContext> c) {
          c->Active();
          auto res = w->Run(c);
          c->Deactive();
          return res;
        },
        w, c);
    return res;
  }
};
