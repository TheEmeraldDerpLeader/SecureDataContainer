#pragma once

#include <iostream>
#include <vector>
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
/Singleton? It's literally got module in the name
*/
class EncryptionModule
{
public:
	
	//---error handling can be done within these functions, or you can return an error int and let me know to add error handling on the SDCSoftware side for that
	
	//archiveName is just a simple string file for the name. Could be a path.
	void TryCreateArchive(std::string archiveName);

	void EncryptAndAddFiles(AccessControlMatrix& acm);

	//accessKeysOut is a 4 element vector of strings. The first string should be set to the admin's access key, second is privleged user, etc...
	void EncryptAndAddACM(AccessControlMatrix& acm, std::vector<std::string>& accessKeysOut);
};