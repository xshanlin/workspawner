#include "CWorkSpawner.h"

void CInterrupt::Interrupt(uint64_t FLAG) { interrupt_.fetch_or(FLAG); }

uint64_t CInterrupt::InterruptTest(uint64_t FLAG) {
  return interrupt_.fetch_and(~FLAG) & FLAG;
}
