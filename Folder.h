#pragma once
///These are here in case the source doesn't link to them, mine does, so they technically do nothing.
#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _CSTDLIB_
#include <cstdlib>
#endif
#ifndef _CHRONO_
#include <chrono>
#endif
#include "File.h"
#pragma warning(disable : 4996)

/// <summary>
/// Class for folder
/// </summary>
class Folder {
private:
	std::string name;
	time_t createDate;
	//Array for the files in the folder
	File files[10];
	//fileAmount and folderAmount are used to make counting easier
	int fileAmount = 0;
	//Array for folderpointers
	Folder* folders[5];
	int folderAmount = 0;
	//Starts at 0, increases as more files are added to the folder
	int size = 0;
public:
	/// <summary>
	/// Folder constructor
	/// </summary>
	/// <param name="name">name of folder</param>
	Folder(std::string name) {
		this->name = name;
		this->createDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}
	/// <summary>
	/// changes the name of the currently active folder through simple input
	/// </summary>
	void changeName() {
		std::string newName;
		std::cout << "Write the new name for the folder: \n";
		std::cin >> newName;
		name = newName;
	}
	/// <summary>
	/// Creates a new folder in the currently active folder, fails if too many folders are created
	/// </summary>
	void createFolder() {
		std::string newName;
		std::cout << "Write the name of the new folder: \n";
		std::cin >> newName;

		//puts the created folder into the currently active folder
		Folder* trist = new Folder(newName);
		if (folderAmount <= 4) {
			folders[folderAmount] = trist;
			folderAmount++;
		}
		else {
			std::cout << "ERROR! The parent folder is full.\n";
		}
	}
	/// <summary>
	/// Adds a file into the currently active folder. The return is not used in the current program.
	/// </summary>
	/// <returns>newly created file</returns>
	File createFile() {
		std::string newName;
		std::cout << "Write the name of the new file: \n";
		std::cin >> newName;
		File file(newName);
		//puts the created file into the currently active folder
		if (fileAmount <= 9) {
			files[fileAmount] = file;
			fileAmount++;
		}
		else {
			std::cout << "Error! The parent folder is full.\n";
		}
		return file;
	}
	/// <summary>
	/// Finds the size of the folder based solely on the files in the folder, does not consider folders in the folder
	/// </summary>
	/// <returns></returns>
	int folderSize() {
		size = 0;
		if (fileAmount > 0) {
			//Checks the size of all the files in order to find the size of the folder
			for (int i = 0; i < fileAmount; i++) {
				size += files[i].getSize();
			}
			return size;
		}
		else {
			return 0;
		}
	}
	/// <summary>
	/// Finds the largest file in the currently active folder
	/// </summary>
	void largestFile() {
		//Checks if there are actually any files in the folder
		if (fileAmount < 1) {
			std::cout << "There are no files in this folder\n";
		}
		else {
			//Defines the first file as the largest, and then compares it to the other files
			File largestFile = files[0];
			int largestSize = files[0].getSize();

			for (int i = 0; i < fileAmount; i++) {
				std::cout << "The size of " << files[i].getName() << " is " << files[i].getSize() << "MB\n";
				//replaces the previous largest file with new information for the larger file
				if (largestSize < files[i].getSize()) {
					largestFile = files[i];
					largestSize = files[i].getSize();
				}
			}
			std::cout << "The largest File is " << largestFile.getName() << " with a size of " << largestSize << " MB\n";
		}
	}
	/// <summary>
	/// First prints information on current folder, before going into next folder. When there are no more folders to enter, instead prints information regarding files in the current folder and goes to previous folder, doing the same
	/// </summary>
	void printFolder() {
		//check if print should be plural (folder/folders)
		if (folderAmount != 1) {
			std::cout << name << " has a size of " << folderSize() << "MB, and was created " << std::put_time(localtime(&createDate), "%F %T") << "\n";
			std::cout << "it has " << folderAmount << " folders in it.\n";
		}
		else {
			std::cout << name << " has a size of " << folderSize() << "MB, and was created " << std::put_time(localtime(&createDate), "%F %T") << "\n";
			std::cout << "It has has 1 folder in it\n";
		}
		//Runs the printfolder on all folders in the folder
		for (int i = 0; i < folderAmount; i++) {
			folders[i]->printFolder();
		}
		//check if print should be plural (file/files)
		if (fileAmount != 1) {
			std::cout << "Folder " << name << " has " << fileAmount << " files in it\n";
		}
		else {
			std::cout << "Folder " << name << " has 1 file in it\n";
		}
		//checks information on all files in the folder
		for (int i = 0; i < fileAmount; i++) {
			files[i].printFile();
		}

		std::cout << "Exiting Folder\n";
	}
	/// <summary>
	/// prints out the current folders in the active folder. For each empty space in the folder, instead prints out <empty space>.
	/// </summary>
	/// <returns>How many folders in the currently active folder</returns>
	int showFolders() {
		for (int i = 0; i < 5; i++) {
			if (i < folderAmount) {
				std::cout << i+1 << ". " << folders[i]->folderGetName() << "\n";
			}
			else {
				std::cout << i+1 << ". <Empty space>\n";
			}
		}
		return folderAmount;
	}
	/// <summary>
	/// finds name of folder
	/// </summary>
	/// <returns>name of currently active folder</returns>
	std::string folderGetName() {
		return name;
	}
	/// <summary>
	/// runs the program. enters a main folder, from which you can create more folders to go into; create files in the folder; enter newly created folders and do the same in them; find the largest file in the current folder and exit program.
	/// </summary>
	/// parameter is based on how many folders have been created before running the program
	/// <param name="matrix">0</param>
	void runProgram(int matrix = 0) {
		int layers = matrix;
		layers++;
		bool notBoredYet = true;
		//loop for the switch case
		while (notBoredYet) {
			if (layers == 1) {
				std::cout << "Select an option by writing its number (you are " << layers << " layer deep)\n";
			}
			else {
			std::cout << "Select an option by writing its number (you are " << layers << " layers deep)\n";
			}
			//shows the first 5 options
			int folderNum = showFolders();
			std::cout <<"6. Information on files.\n7. Create new file\n8. Create new folder\n9. Find largest file\n10. Exit folder.\n\n\t";
			int choiceInt;
			//where switch case is chosen
			std::cin >> choiceInt;
			std::cout << "\n";
			//error checking
			if (std::cin.fail()) {
				while (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore();
				}
				std::cout << "You entered an incorrect value. Try again\n\n";
				std::cin >> choiceInt;
			}
			//case 1-5 goes deeper into the code, unless there is no folder, in which case nothing happens
			switch (choiceInt) {
			case(1):
				if (folderNum >= 1) {
					folders[0]->runProgram(layers);
				}
				break;
			case(2):
				if (folderNum >= 2) {
					folders[1]->runProgram(layers);
				}
				break;
			case(3):
				if (folderNum >= 3) {
					folders[2]->runProgram(layers);
				}
				break;
			case(4):
				if (folderNum >= 4) {
					folders[3]->runProgram(layers);
				}
				break;
			case(5):
				if (folderNum >= 5) {
					folders[4]->runProgram(layers);
				}
				break;
				//options 6-9 lets you create files and folders, in addition to checking their information
			case(6):
				for (int i = 0; i < fileAmount; i++) {
					files[i].printFile();
				}
				std::cout << "\n";
				break;
			case(7):
				createFile();
				break;
			case(8):
				createFolder();
				break;
			case(9):
				largestFile();
				break;
				//ends the program, either going up to a parentfolder, or exiting the program if there is no parentfolder
			case(10):
				notBoredYet = false;
				return;
				//error checking
			default:
				std::cout << "Please write a valid number (1-10)\n";
				break;
			}
		}
	}
};

