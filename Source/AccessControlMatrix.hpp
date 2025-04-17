#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdio>

/*
//AccessControlMatrix
- Description:
/Stores the file structure of the archive
/Provides functions to add files, change access level, and everything else involving the
actual layout of the archive
/Has a function to generate the csv files for the physical ACM in the archive

- Tasks:
/Data structure to associate file names to file paths (pre-archive), access permission, and encryption keys
/Add files to this data structure
/Generate csv files to be added to archive
/Generate keys for the role permissions and files (must be true random keys)
*/

//access level bit flags, admin access is implied
#define SDC_ADMIN 0
#define SDC_PRIVUSER 1
#define SDC_USER 2
#define SDC_GUEST 4

class FileEntry
{
public:
	std::string filePath;
	std::string fileName;
	int access = 0; //0 = admin, 1 = privleged user, 2 = user, 3 = guest
	std::string key;

	FileEntry() {}
	FileEntry(std::string filePathString, int accessInt, std::string keyString) : filePath(filePathString), access(accessInt), key(keyString)
	{
		//get last name in file path
		for (int i = filePath.size()-1; i >= 0; i--)
		{
			if (filePath[i] == '/' || filePath[i] == '\\')
				break;;
			fileName.push_back(filePath[i]);
		}

		//reverse order
		int j = fileName.size()-1;
		for (int i = 0; i < fileName.size(); i++)
		{
			if (i >= j) //lazy way
				break;
			char hold = fileName[i];
			fileName[i] = fileName[j];
			fileName[j] = hold;
			j--;
		}
	}
};

int randI(int firstInt, int secondInt, std::mt19937& rng); ///inclusive

class AccessControlMatrix
{
public:
	std::vector<FileEntry> files;
	std::vector<std::string> csvKeys;

	std::mt19937 rng;

	std::string GenerateKey();

	AccessControlMatrix();

	void GenerateCSVFiles();
	void DeleteCSVFiles();

	void AddFile(int accessLevel, std::string& filePath);
};