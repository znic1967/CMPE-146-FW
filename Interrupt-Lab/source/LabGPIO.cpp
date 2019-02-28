#include "LabGPIO.h"
#include "utility/log.hpp"
#include "utility/time.hpp"

/*constexpr*/ LabGPIO::LabGPIO(uint8_t portGPIO, uint8_t pinGPIO)
{
	port = portGPIO;
	pin = pinGPIO;
	if(port > 5) 
	{
		LOG_INFO("Invalid Port");
	}
	if(pin > 32) 
	{
		LOG_INFO("Invalid Pin");
	}
	else
	{
		switch (port)
		{
			case 0: 
			{
				gpioDef = LPC_GPIO0; 
				//Set internal pulldowns for switch 0
				LPC_IOCON->P1_19 &= ~((1 << 4) | (1 << 3));  
      			LPC_IOCON->P1_19 |= (1 << 3);
				break;
			}
			case 1:
			{
				gpioDef = LPC_GPIO1; 
				//Set internal pulldowns for switch 1
				LPC_IOCON->P1_15 &= ~((1 << 4) | (1 << 3)); 
      			LPC_IOCON->P1_15 |= (1 << 3);
				break;
			}
			case 2: 
			{
				gpioDef = LPC_GPIO2; 
				break;
			}
			case 3: 
			{
				gpioDef = LPC_GPIO3; 
				break;
			}
			case 4: 
			{
				gpioDef = LPC_GPIO4;
				break;
			}
			case 5: 
			{
				gpioDef = LPC_GPIO5; 
				break;
			}
		} 
	}
}
void LabGPIO::SetAsInput()
{
	gpioDef->DIR &= ~(1 << pin);
}
void LabGPIO::SetAsOutput()
{
	gpioDef->DIR |= (1 << pin);
}
void LabGPIO::SetDirection(Direction direction)
{
	if (direction==Direction::kInput) 
	{
		SetAsInput();
	}
	else 
	{
		SetAsOutput();
	}
}
void LabGPIO::SetHigh()
{
	gpioDef->SET = (1 << pin);
}
void LabGPIO::SetLow()
{
	gpioDef->CLR = (1 << pin);
}
void LabGPIO::set(State state)
{
	if(state==State::kLow)
	{
		SetLow();
	}
	else 
	{
		SetHigh();
	}
}
LabGPIO::State LabGPIO::Read()
{
	State currentState = State::kLow;
	bool statusBit = gpioDef->PIN & (1 << pin);
	if(statusBit) 
	{
		currentState = State::kHigh;
	}
	return currentState;
}
bool LabGPIO::ReadBool()
{
	bool boolState = 0;
	State currentState = Read();
	if (currentState == State::kHigh) 
	{
		boolState = 1;
	}
	return boolState;
}

uint8_t LabGPIO::getPort()
{ 
	return port;
}

uint8_t LabGPIO::getPin() 
{
	return pin;
}