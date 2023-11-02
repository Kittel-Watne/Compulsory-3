#pragma once
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

class Folder {
private:
	std::string name;
	time_t createDate;
	File files[10];
	int fileAmount = 0;
	Folder* folders[5];
	int folderAmount = 0;
	int size = 0;
public:
	Folder(std::string name) {
		this->name = name;
		this->createDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	void changeName() {
		std::string newName;
		std::cout << "Write the new name for the folder: \n";
		std::cin >> newName;
		name = newName;
	}

	void createFolder() {
		std::string newName;
		std::cout << "Write the name of the new folder: \n";
		std::cin >> newName;

		Folder* trist = new Folder(newName);
		if (folderAmount <= 4) {
			folders[folderAmount] = trist;
			folderAmount++;
		}
		else {
			std::cout << "ERROR! The parent folder is full.\n";
		}
	}
	File createFile() {
		std::string newName;
		std::cout << "Write the name of the new file: \n";
		std::cin >> newName;
		File file(newName);
		if (fileAmount <= 9) {
			files[fileAmount] = file;
			fileAmount++;
		}
		else {
			std::cout << "Error! The parent folder is full.\n";
		}
		return file;
	}

	int folderSize() {
		size = 0;
		if (fileAmount > 0) {
			for (int i = 0; i < fileAmount; i++) {
				size += files[i].getSize();
			}
			return size;
		}
		else {
			return 0;
		}
	}
	void storeFile(File file) {
		if (fileAmount > 4) {
			files[fileAmount] = file;
			folderAmount++;
		}
		else {
			std::cout << "ERROR! The parent folder is full.\n";
		}
	}
	void largestFile() {
		if (fileAmount < 1) {
			std::cout << "There are no files in this folder\n";
		}
		else {
			File largestFile = files[0];
			int largestSize = files[0].getSize();

			for (int i = 0; i < fileAmount; i++) {
				std::cout << "The size of " << files[i].getName() << " is " << files[i].getSize() << "MB\n";

				if (largestSize < files[i].getSize()) {
					largestFile = files[i];
					largestSize = files[i].getSize();
				}
			}
			std::cout << "The largest File is " << largestFile.getName() << " with a size of " << largestSize << " MB\n";
		}
	}
	void printFolder() {
		if (folderAmount != 1) {
			std::cout << name << " has a size of " << folderSize() << "MB, and was created " << std::put_time(localtime(&createDate), "%F %T") << "\n";
			std::cout << "it has " << folderAmount << " folders in it.\n";
		}
		else {
			std::cout << name << " has a size of " << folderSize() << "MB, and was created " << std::put_time(localtime(&createDate), "%F %T") << "\n";
			std::cout << "It has has 1 folder in it\n";
		}
		for (int i = 0; i < folderAmount; i++) {
			folders[i]->printFolder();
		}
		if (fileAmount != 1) {
			std::cout << "Folder " << name << " has " << fileAmount << " files in it\n";
		}
		else {
			std::cout << "Folder " << name << " has 1 file in it\n";
		}
		for (int i = 0; i < fileAmount; i++) {
			files[i].printFile();
		}

		std::cout << "Exiting Folder\n";
	}
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

	std::string folderGetName() {
		return name;
	}

	void runProgram(int matrix) {
		int layers = matrix;
		layers++;
		bool notBoredYet = true;
		while (notBoredYet) {
			if (layers == 1) {
				std::cout << "Select an option by writing its number (you are " << layers << " layer deep)\n";
			}
			else {
			std::cout << "Select an option by writing its number (you are " << layers << " layers deep)\n";
			}
			int folderNum = showFolders();
			std::cout <<"6. Information on files.\n7. Create new file\n8. Create new folder\n9. Find largest file\n10. Exit folder.\n\n\t";
			int choiceInt;
			std::cin >> choiceInt;
			std::cout << "\n";
			if (std::cin.fail()) {
				while (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore();
				}
				std::cout << "You entered an incorrect value. Try again\n\n";
				std::cin >> choiceInt;
			}
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
			case(10):
				notBoredYet = false;
				return;
			default:
				std::cout << "Please write a valid number (1-10)\n";
				break;
			}
		}
	}
};

