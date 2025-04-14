#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "AccessControlMatrix.hpp"

/*
//EncryptionModule
- Description:
/Responsible for using 7zip to create the archive
/Reads from an AccessControlMatrix object to figure out what files to encrypt and such
/Checks for errors in ACM (e.g. an added file was later deleted from the OS)

- Tasks:
/Verify that 7Zip is usable
/Determine output name (what if output already exists?)
/7zip an individual file + key from an ACM object's file structure data
/7zip all files from an ACM object
/7zip csvs from an ACM object

- Other Notes:
/https://documentation.help/7-Zip/index5.htm
*/

class EncryptionModule
{
public:
	std::string archiveName;	
	//archiveName is just a simple string file for the name. Could be a path.
	void TryCreateArchive(std::string archiveNameString);

	//accessKeysOut is a 4 element vector of strings. The first string should be set to the admin's access key, second is privleged user, etc...
	void CreateArchiveAndAddACM(AccessControlMatrix& acm, std::vector<std::string>& accessKeysOut);
};