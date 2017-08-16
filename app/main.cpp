#include <gmThread.h>
#include <gmCall.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iterator> 
#include <vector>
#include <CFSM.h>


int main() {

	// Create gm virtual machine

	CFSM behavioralMachine;
	behavioralMachine.Init();
	float delta = 0.1;
	while (true)
	{
		behavioralMachine.Update(delta);
	}

	
	return 0;
}