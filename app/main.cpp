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
int GM_CDECL gm_myMultiply(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(2);
	GM_CHECK_INT_PARAM(a_x, 0);
	GM_CHECK_INT_PARAM(a_y, 1);

	int ret = a_x * a_y;

	a_thread->PushInt(ret);

	return GM_OK;
}

int main() {

	// Create gm virtual machine
	gmMachine	gm;

	static gmFunctionEntry lib[] =
	{
		{ "MUL", gm_myMultiply }		// type name, entry point
	};
	gm.RegisterLibrary(lib, sizeof(lib)	/sizeof(lib[0]));
	int ret = gmLoadAndExecuteScript(gm);
	if (ret != 0)
	{
		// There were errors in the script, exit gracefully
		handleErrors(gm);
		return 1;
	}

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