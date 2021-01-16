#pragma once

#include "CWorkSpawner.h"

class MyContext : public CContext {
 public:
  MyContext(std::string name) : name_(name) {}
  virtual ~MyContext() {}

 public:
  // 通过 CContext 继承
  virtual int32_t Active() override;
  virtual int32_t Deactive() override;

 private:
  std::string name_;
};

class MyContext1 : public MyContext, public CInterrupt {
 public:
  MyContext1() : MyContext("context1") {}
  virtual ~MyContext1() {}

 public:
  int32_t foo1();
};

class MyWorker1 : public CWorker {
 public:
  MyWorker1() {}
  virtual ~MyWorker1() {}

 public:
  // 通过 CWorker 继承
  virtual int32_t Run(const std::shared_ptr<CContext> c) override;
};

class MyContext2 : public MyContext {
 public:
  MyContext2() : MyContext("context2") {}
  virtual ~MyContext2() {}

 public:
  int32_t foo2();
};

class MyWorker2 : public CWorker {
 public:
  MyWorker2() {}
  virtual ~MyWorker2() {}

 public:
  // 通过 CWorker 继承
  virtual int32_t Run(const std::shared_ptr<CContext> c) override;
};

class CWorkSpawnerTest {
 public:
  CWorkSpawnerTest() {}
  ~CWorkSpawnerTest() {}

 public:
  void Test();
  void Foo();

 private:
  CWorkSpawner<4> spawner_;
};
