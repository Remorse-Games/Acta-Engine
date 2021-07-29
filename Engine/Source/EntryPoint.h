#pragma once

#include "actapch.h"
#include "Core/Application.h"

#if !UNIT_TESTING
int main(int argc, char** argv)
{
	auto app = CreateApplication();
	app->Run();
	delete app;
}
#endif