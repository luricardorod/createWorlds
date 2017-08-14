#include <gmThread.h>
#include <gmCall.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iterator> 
#include<vector>
int gmLoadAndExecuteScript(gmMachine &a_machine)
{
	std::vector<std::string> scripts;

	scripts.push_back("scripts/helloWorld.gm");
	scripts.push_back("scripts/unit.gm");
	std::string allScript = "";
	for (int i = 0; i < scripts.size(); i++)
	{
		std::ifstream file(scripts[i]);
		if (!file)
			return GM_EXCEPTION;
		allScript += std::string(std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
		file.close();
	}
	return a_machine.ExecuteString(allScript.c_str());
}

void handleErrors(gmMachine &a_machine)
{
	gmLog &log = a_machine.GetLog();
	// Get the first error
	bool firstError = true;
	const char *err = log.GetEntry(firstError);
	while (err)
	{
		std::cout << "Compilation error: -" << err << std::endl;
		err = log.GetEntry(firstError);
	}
}
using namespace std;
int main() {

	// Create gm virtual machine
	gmMachine	gm;
	gmVariable var(gm.AllocStringObject("Hello, World"));

	switch (var.m_type)
	{
	case GM_NULL:
		cout << "Variable is NULL type" << endl;
		break;
	case GM_INT:
		cout << "Variable is INT type" << endl;
		cout << "Value:" << var.m_value.m_int << endl;
		break;
	case GM_FLOAT:
		cout << "Variable is FLOAT type" << endl;
		cout << "Value:" << var.m_value.m_float << endl;
		break;
	case GM_STRING:
		cout << "Variable is STRING type" << endl;
		break;
	case GM_TABLE:
		cout << "Variable is TABLE type" << endl;
		break;
	case GM_FUNCTION:
		cout << "Variable is FUNCTION type" << endl;
		break;
	default:
		cout << "Variable is USER type" << endl;
		// retrieve native pointer from user object

	};

	int ret = gmLoadAndExecuteScript(gm);
	if (ret != 0)
	{
		// There were errors in the script, exit gracefully
		handleErrors(gm);
		return 1;
	}
	gm.Execute(0);

	gmCall  call;
	if (call.BeginGlobalFunction(&gm, "init"))
	{
		call.End();
	}
	else
	{
		std::cout << "Error init'" << std::endl;
	}

	if (call.BeginGlobalFunction(&gm, "update"))
	{
		call.End();
	}
	else
	{
		std::cout << "Error update'" << std::endl;
	}

	if (call.BeginGlobalFunction(&gm, "render"))
	{
		call.End();
	}
	else
	{
		std::cout << "Error render'" << std::endl;
	}

	if (call.BeginGlobalFunction(&gm, "destroy"))
	{
		call.End();
	}
	else
	{
		std::cout << "Error destroy'" << std::endl;
	}

	if (call.BeginGlobalFunction(&gm, "move_ent_left"))
	{
		call.End();
	}
	else
	{
		std::cout << "Error move_ent_left'" << std::endl;
	}
	return 0;
}