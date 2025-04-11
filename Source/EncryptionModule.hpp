#pragma once

#include <iostream>

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

};