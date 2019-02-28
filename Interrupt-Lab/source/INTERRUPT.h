#pragma once 

// Gives you access to 
#include "L0_LowLevel/interrupts.hpp"

class LabGPIO
{
 public:
  enum class Edge
  {
    kNone = 0,
    kRising,
    kFalling,
    kBoth
  };
  static constexpr size_t kPorts = 2;
  static constexpr size_t kPins = 32; 
  // This handler should place a function pointer within the lookup table for 
  // the GpioInterruptHandler() to find.
  //
  // @param isr  - function to run when the interrupt event occurs.
  // @param edge - condition for the interrupt to occur on.
  void AttachInterruptHandler(IsrPointer isr, Edge edge);
 private:
  // Statically allocated a lookup table matrix here of function pointers 
  // to avoid dynamic allocation.
  // 
  // Upon AttachInterruptHandler(), you will store the user's function callback
  // in this matrix.
  //
  // Upon the GPIO interrupt, you will use this matrix to find and invoke the
  // appropriate callback.
  //
  // Initialize everything to nullptr.
  static IsrPointer pin_isr_map[kPorts][kPins] = { nullptr };
  // This function is invoked by NVIC via the GPIO peripheral asynchronously.
  // This ISR should do the following:
  //  1) Find the Port and Pin that caused the interrupt via the IO0IntStatF,
  //     IO0IntStatR, IO2IntStatF, and IO2IntStatR registers.
  //  2) Lookup and invoke the user's registered callback.
  //
  // VERY IMPORTANT!
  //  - Be sure to clear the interrupt flag that caused this interrupt, or this 
  //    function will be called repetitively and lock your system.
  //  - NOTE that your code needs to be able to handle two GPIO interrupts 
  //    occurring at the same time.
  static void GpioInterruptHandler();
  // Register GPIO_IRQn here
  static void EnableInterrupts();
};

// ...

int main(void)
{
  // This is just an example, use which ever pins and ports you like 
  Gpio gpio(2, 3);
  gpio.EnableInterrupts();

  while(true)
  {
    continue;
  }
  return 0;
}
