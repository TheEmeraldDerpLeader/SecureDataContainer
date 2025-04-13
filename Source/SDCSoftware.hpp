#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "AccessControlMatrix.hpp"
#include "EncryptionModule.hpp"

//ToDo:
//Uncomment function calls for AccessControlMatrix and EncryptionModule
//Add reading a file from an archive?
//Local directory command for adding files?
//Error handling if not implemented in other classes

/*
//SDCSoftware
- Description:
/Manages the view in MVC for the entire application
/Implement user flow based on the sequence diagram and activity diagram here

- Tasks:
/Explicitly layout the progression of the command line interface
through comments (see Other Notes).
/Query input from user. Non-exhaustive list of potential input (* optional):
Encryption related:
/file names to add to archive
/file permissions
*remove file from archive
*view current files in archive
/Generate archive (output keys)

Post-archive related:
*Extract files for a given user key

/Write preliminary response handling where possible
/Once other modules are finalized:
/Input processing
/Other response handling

- Other Notes:
/There are many ways we could implement this. I'd personally do a state machine approach
*/

//For simplicity, this is basically just the main function, though for a real application it could be nice to extend this class to something that takes input periodically,
// allowing for something like a UI wrapper to be built using it.
class SDCSoftware
{
public:
	
	AccessControlMatrix acm;

	//main function, starts the state-based command line UI
	void CommandInterfaceStart();

	//substates of the main UI loop
	//attempts to set currentPermission
	void SetPermissionFlag();
	//attempts to add a File
	void AddFile();

	//final state, returns permission keys through stdout. Also can create a .txt file if user wants that too.
	//if return value is 1, then user cancled generation
	int GenerateArchive();
};