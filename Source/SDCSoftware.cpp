#include "SDCSoftware.hpp"

void ToLower(std::string& s)
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = 'a'+(s[i]-'A');
}

std::string helpMessage = R"(Commands:
Help - Displays this message
Exit - Closes software without creating an archive
AddFiles - Starts file adding prompt
GenerateArchive - Creates archive from added files

)";

void SDCSoftware::CommandInterfaceStart()
{

	std::cout << "\n----Secure Data Container Creation Interface----\n\n";
	std::cout << helpMessage;

	std::string input;
	while (true)
	{
		bool badCommand = true;
		std::cout << "Enter a command: ";
		std::cin >> input;
		ToLower(input);

		//terminate program without creating archive
		if (input == "exit")
		{
			std::cout << "Program terminated\n";
			badCommand = false;
			break;
		}

		//Print out commands message
		if (input == "help")
		{
			std::cout << '\n' << helpMessage;
			badCommand = false;
		}

		//Enter file adding state
		if (input == "addfiles")
		{
			AddFile();
			std::cout << "Added Files!\n";
			badCommand = false;
		}

		//Enter file generation state
		if (input == "generatearchive")
		{
			badCommand = false;
			
			int error = GenerateArchive();
			if (error == 0)
			{
				std::cout << "Generated Archive!\n";
				break;
			}
			if (error == 1)
				std::cout << "Cancelled Archive Generation!\n";
			
		}

		if (badCommand == true)
			std::cout << "\nInvalid command, use command Help to see availible commands, do not put spaces within a single command word\n";

	}
	//end of program
}

void SDCSoftware::SetPermissionFlag()
{
}

void SDCSoftware::AddFile() //may want to add local directory stuff commands so user doesn't have to type entire path everytime
{
	std::string input;
	
	std::cout << R"(Add files and their access levels here. Use the following format:
{Admin / PrivUser / User / Guest} "file1" "file2" etc...

The first word should be a access level specifier. When files are added, they use the latest access specifier. If no access level is specified when adding a file, the input command will error and nothing will be added.
Use command Stop to stop adding files

)";

	std::getline(std::cin, input); //clear empty string from calling std::cin >> input in previous state
	while (true)
	{
		std::cout << "Enter command or sequence of commands:\n";

		//Get sequence of commands until new line character
		input.clear();
		std::getline(std::cin, input);

		std::string word;
		int currentAccess = -1; //-1 = invalid, 0 = admin, 1 = privleged user, 2 = user, 3 = guest
		
		input.push_back(' '); //handle final word at end of string
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == ' ' && word.size() == 0) //skip over starting whitespace
				continue;

			//File name input
			else if (input[i] == '"')
			{
				if (currentAccess == -1)
				{
					std::cout << "Trying to add a file while permission isn't set! Please set a permission level before specifying files\n";
					break; //goes back to start of while loop
				}

				//create file path in word
				bool validPath = false;
				int j = i+1;
				for (; j < input.size(); j++)
				{
					if (input[j] == '"')
					{
						validPath = true;
						j++;
						break;
					}
					else
						word.push_back(input[j]);
				}

				//Add file to ACM
				acm.AddFile(currentAccess, word); //maybe return an error code, but could very well just have acm class print stuff out instead
				std::cout << "Added File: " << word << " with access " << currentAccess << '\n';

				i = j;
				word.clear();
			}


			else if (input[i] != ' ') //gradually create nonfile word
				word.push_back(input[i]);

			//Handle word
			else if (input[i] == ' ')
			{
				bool validWord = false;
				ToLower(word);
				if (word == "admin")
				{
					currentAccess = 0;
					validWord = true;
				}
				else if (word == "privuser")
				{
					currentAccess = 1;
					validWord = true;
				}
				else if (word == "user")
				{
					currentAccess = 2;
					validWord = true;
				}
				else if (word == "guest")
				{
					currentAccess = 3;
					validWord = true;
				}
				if (word == "stop")
					return; //terminate this state

				if (validWord == false)
					std::cout << "Invalid command: " << word << '\n';

				word.clear();
					
			}
		}
	}
}

int SDCSoftware::GenerateArchive()
{
	std::cout << "----Generating Archive----\n";
	//std::cout << "Do you want randomized file names? Y or N: ";
	//If Y, call function on acm which randomizes the file names in it's data structure

	std::cout << "Enter STOP to cancel...\nSpecify archive name: ";
	std::string name;
	std::getline(std::cin, name); //clear empty string from calling std::cin >> input in previous state
	
	while (true)
	{
		std::getline(std::cin, name);
		if (name == "STOP")
			return 1;
		if (name.size() >= 3)
		{
			if (name[name.size()-3] != '.' || name[name.size()-2] != '7' || name[name.size()-1] != 'z')
				name += ".7z";
		}
		std::cout << "Is \"" << name << "\" a good name for the archive? Y or N:";
		std::string input;
		std::getline(std::cin, input);
		if (input.size() > 0 && (input[0] == 'Y' || input[0] == 'y'))
			break;
		else
			std::cout << "Specify a new archive name: ";
	}

	std::vector<std::string> accessKeys;
	accessKeys.resize(4);

	EncryptionModule em;
	em.TryCreateArchive(name);
	em.CreateArchiveAndAddACM(acm, accessKeys);

	std::cout << "Archive Created!\n";
	std::cout << "Admin access key: " << accessKeys[0] << '\n';
	std::cout << "Privleged User access key: " << accessKeys[1] << '\n';
	std::cout << "User access key: " << accessKeys[2] << '\n';
	std::cout << "Guest access key: " << accessKeys[3] << '\n';
	std::cout << "\n\n Enter anything to quit the program\n";
	//std::cout << "Would you like these keys copied to a txt file? Y or N: ";
	//Output keys to keys.txt, maybe check if keysNN...NNN.txt exists before writing so nothing is overwritten


	std::cin.get();
	return 0;
}
