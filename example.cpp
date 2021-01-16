#include "example.h"

#include <iostream>

void CWorkSpawnerTest::Test() {

  auto c1 = std::make_shared<MyContext1>();
  auto c2 = std::make_shared<MyContext2>();
  spawner_.Spawn(std::make_shared<MyWorker1>(), c1);
  spawner_.Spawn(std::make_shared<MyWorker2>(), c2).get();

  c1->Interrupt(0x32);
}

void CWorkSpawnerTest::Foo() { std::cout << "foo\n"; }

int32_t MyContext::Active() { return 0; }

int32_t MyContext::Deactive() { return 0; }

int32_t MyContext1::foo1() {
  int x = 0;

  while (x++ < 30) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ">>>>>>>>>>>>foo1\n";

    auto FLAG = this->InterruptTest(0x02);
    if (FLAG) {
      return FLAG;
    }
  }
  return 0;
}

int32_t MyWorker1::Run(const std::shared_ptr<CContext> c) {
  auto c1 = std::dynamic_pointer_cast<MyContext1>(c);
  return c1->foo1();
}

int32_t MyContext2::foo2() {
  std::cout << ">>foo2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(3700));
  std::cout << "<<foo2\n";
  return 0;
}

int32_t MyWorker2::Run(const std::shared_ptr<CContext> c) {
  auto c1 = std::dynamic_pointer_cast<MyContext2>(c);
  return c1->foo2();
}
