#pragma once
#include "Map.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "input.h"
#include "imgui.h"

/*!
		Struktura reprezentujaca komende w terminalu.
*/
struct Command
{
	/*!
		Nazwa komendy.
	*/
	const char* signature;
	/*!
		Wskaznik na funkcje ktora ma sie wykonac po wpisaniu komendy.
	*/
	void (*Func)(std::vector<char*>);
};

/*!
		Klasa odpowiedzialna za terminal w silniku.
*/
class CLI
{
public:
	/*!
		Funkcja inicjalizujaca.
	*/
	void Init();
	/*!
		Funkcja rysujaca terminal.
	*/
	void Draw(ImGuiIO& io);
	/*!
		Funkcja zapisujaca do terminala dany ciag.
	*/
	void AddLog(const char* fmt, ...);

	/*!
		Lista komend w terminalu.
	*/
	std::vector<Command> commands;
private:
	void Parse();

	std::vector<const char*> items;
};

extern CLI cli;