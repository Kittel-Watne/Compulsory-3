#include <iostream>
#include <iomanip>
#include <chrono>
#include "File.h"
#include "Folder.h"
#pragma warning(disable : 4996)





int main(){
	//creating the main folder to run the program
	Folder Jumbo("hovedMappe");
	//running the program
	Jumbo.runProgram(0);
	//top tier comedy
	std::cout << "\nYou have escaped the Matrix!\n";

	return 0;
}