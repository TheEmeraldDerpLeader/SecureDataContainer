#include "EncryptionModule.hpp"

void EncryptionModule::TryCreateArchive(std::string archiveNameString)
{
	archiveName = archiveNameString;
	std::cout << "Trying to create an archive" << archiveName << '\n';
	std::cout.flush(); //so system calls don't get shown before cout buffer

	std::remove(archiveName.c_str()); //ignore error

	//no command line option to just create an archive. For simplicity, just don't make one here
}

void EncryptionModule::CreateArchiveAndAddACM(AccessControlMatrix& acm, std::vector<std::string>& accessKeysOut)
{
	acm.GenerateCSVFiles();
	accessKeysOut = acm.csvKeys;
	std::cout.flush(); //so system calls don't get shown before cout buffer

	std::string commandStart = "7Zip\\7z a -t7z \""; commandStart += archiveName; commandStart += '"';

	//command to be executed, calling 7zip to add and encrypt the files
	std::string command;

	//add csvFiles to directory

	//admnKeys.csv
	command = commandStart;  command += " \""; command += "__adminKeys.csv"; command += '"';
	//add password to file
	command += " -p"; command += acm.csvKeys[0];
	//redirect output to nul
	command += " > nul";
	std::system(command.c_str());
	
	//admnKeys.csv
	command = commandStart;  command += " \""; command += "__privUserKeys.csv"; command += '"';
	command += " -p"; command += acm.csvKeys[1];
	command += " > nul";
	std::system(command.c_str());

	//admnKeys.csv
	command = commandStart;  command += " \""; command += "__userKeys.csv"; command += '"';
	command += " -p"; command += acm.csvKeys[2];
	command += " > nul";
	std::system(command.c_str());

	//admnKeys.csv
	command = commandStart;  command += " \""; command += "__guestKeys.csv"; command += '"';
	command += " -p"; command += acm.csvKeys[3];
	command += " > nul";
	std::system(command.c_str());

	acm.DeleteCSVFiles();

	std::vector<std::string> failedFiles;

	//Add and encrypt files to archive
	for (int i = 0; i < acm.files.size(); i++)
	{
		command = commandStart;  command += " \""; command += acm.files[i].filePath; command += '"';
		//add password to file
		command += " -p"; command += acm.files[i].key;
		//redirect output to nul
		command += " > nul";
		int error = std::system(command.c_str());
		if (error != 0)
		{
			failedFiles.push_back(acm.files[i].filePath);
		}
	}

	//warn user of files which couldn't be added
	if (failedFiles.size() > 0)
	{
		std::cout << "Warning: the following files couldn't be added to the archive:\n";
		for (int i = 0; i < failedFiles.size(); i++)
			std::cout << failedFiles[i] << '\n';
		std::cout << '\n';
	}
	else
	{
		std::cout << "\nSuccessfully created an archive from all files!\n";
	}
}
