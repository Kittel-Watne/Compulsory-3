#include <iostream>
#include <iomanip>
#include <chrono>
#include "File.h"
#include "Folder.h"
#pragma warning(disable : 4996)





int main(){
	Folder Jumbo("hovedMappe");
	Jumbo.runProgram(0);
	std::cout << "\nYou have escaped the Matrix!\n";
	return 0;
}