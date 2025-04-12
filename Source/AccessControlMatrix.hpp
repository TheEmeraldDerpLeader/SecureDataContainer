#pragma once

#include <string>
#include <iostream>
#include <fstream>
//true random number generation

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
class AccessControlMatrix
{
public:
	void AddFile(int permission, std::string& filePath);


};