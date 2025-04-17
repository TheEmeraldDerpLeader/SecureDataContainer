#ifndef NOT_WINDOWS
#define WINDOWS
#endif

#include "AccessControlMatrix.hpp"

#include <ctime> //better to do this where possible, for simplicity not doing it tho

AccessControlMatrix::AccessControlMatrix()
{
	std::random_device trueRandom;
	try
	{
		rng.seed(trueRandom());
	}
	catch (...)
	{
		std::cout << "System lacks a true random number generator, defaulting to current time\n";
		rng.seed(std::time(0));
	}
}

int randI(int firstInt, int secondInt, std::mt19937& rng) ///inclusive
{
	if (firstInt > secondInt)
		std::swap(firstInt, secondInt);
	std::uniform_int_distribution<> dist(firstInt, secondInt);
	return dist(rng);
}

void AccessControlMatrix::AddFile(int accessLevel, std::string& filePath)
{
	//files starting with ./ won't get put in subfolders for the archive, so remove ./ if possible
	if (filePath.size() >= 2 && filePath[0] == '.' && (filePath[1] == '/' || filePath[1] == '\\'))
	{
		//remove first two characters
		for (int i = 0; i < filePath.size()-2; i++)
			filePath[i] = filePath[i+2];
		filePath.resize(filePath.size()-2);
	}

	files.push_back(FileEntry(filePath, accessLevel, GenerateKey()));
}

std::string AccessControlMatrix::GenerateKey()
{
	std::string key;
	for (int i = 0; i < 16; i++) //generate 16 random characters for key
	{
		//generate character from '0' to '9' and 'a' to 'z', subtract 1 cuz randI is inclusive 
		int a = randI(0,10+26-1,rng);
		if (a < 10) //'0' to '9'
			key.push_back('0' + a);
		else //'a' to 'z'
			key.push_back('a' + (a-10));
	}
	return key;
}

void AccessControlMatrix::GenerateCSVFiles()
{
	// open file streams, delete preexisting file contents
	std::ofstream csvStreams[4];
	csvStreams[0].open("__adminKeys.csv", std::ios::out | std::ios::trunc);
	csvStreams[1].open("__privUserKeys.csv", std::ios::out | std::ios::trunc);
	csvStreams[2].open("__userKeys.csv", std::ios::out | std::ios::trunc);
	csvStreams[3].open("__guestKeys.csv", std::ios::out | std::ios::trunc);

	//Generate csv keys
	csvKeys.resize(4);
	for (int i = 0; i < 4; i++)
		csvKeys[i] = GenerateKey();

	//column names
	for (int i = 0; i < 4; i++)
		csvStreams[i] << "File Name,Key\n";

	//Give admin the keys to access the other ACM csvs
	csvStreams[0] << "\"__privUserKeys.csv\"," << csvKeys[1] << '\n';
	csvStreams[0] << "\"__userKeys.csv\"," << csvKeys[2] << '\n';
	csvStreams[0] << "\"__guestKeys.csv\"," << csvKeys[3] << '\n';

	//Fill out csvs by iterating through all files
	for (int i = 0; i < files.size(); i++)
	{
		std::string* effectiveFileLocation = &(files[i].filePath);

		//check if filepath is an absolute file paths
#ifdef WINDOWS
		if (files[i].filePath.size() >= 2 && files[i].filePath[1] == ':') //check if path starts at a drive
#endif
#ifdef NOT_WINDOWS
		if (files[i].filePath.size() >= 1 && files[i].filePath[0] == '/') //check if path starts with /
#endif	
			effectiveFileLocation = &(files[i].fileName); //7z handles absolute file paths by storing the file at the root of the archive

		if (files[i].filePath.size() >= 3 && files[i].filePath[0] == '.' && files[i].filePath[1] == '.' && (files[i].filePath[2] == '/' || files[i].filePath[2] == '\\'))
			effectiveFileLocation = &(files[i].fileName); //similar if file path goes outside of initial directory (probably true whenever ../ is used, even if not at start)


		//admin can access all files
		csvStreams[0] << '"' << *effectiveFileLocation << "\"," << files[i].key << '\n';
		if ((files[i].access & SDC_PRIVUSER) != 0)
			csvStreams[1] << '"' << *effectiveFileLocation << "\"," << files[i].key << '\n';
		if ((files[i].access & SDC_USER) != 0)
			csvStreams[2] << '"' << *effectiveFileLocation << "\"," << files[i].key << '\n';
		if ((files[i].access & SDC_GUEST) != 0)
			csvStreams[3] << '"' << *effectiveFileLocation << "\"," << files[i].key << '\n';
		
	}

	for (int i = 0; i < 4; i++)
		csvStreams[i].close();
}

void AccessControlMatrix::DeleteCSVFiles()
{
	std::remove("__adminKeys.csv");
	std::remove("__privUserKeys.csv");
	std::remove("__userKeys.csv");
	std::remove("__guestKeys.csv");
}
