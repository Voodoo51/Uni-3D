#pragma once
//#include "Player.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "input.h"
#include "imgui.h"

struct Command
{
	const char* signature;
	void (*Func)(std::vector<char*>);
};

class CLI
{
public:
	void Init();
	void Draw(ImGuiIO& io);
	void AddLog(const char* fmt, ...);

	std::vector<Command> commands;
private:
	void Parse();

	std::vector<const char*> items;
};

extern CLI cli;