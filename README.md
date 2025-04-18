# SecureDataContainer
 Project to create a 7zip archive with files that have different access permissions. Users can use a key specific to their access privilege to obtain access to specific files in the archive. This project streamlines the process of generating keys and the access control matrix for users to obtain the random file keys.

## Developer Information
 See [BuildInfo](https://github.com/TheEmeraldDerpLeader/SecureDataContainer/blob/main/Build/BuildInfo.md) for compiling and building this project

## User Information
 Release build executables are currently provided for Windows and x86 Linux for 64-bit systems and can be obtained in the [release tab](https://github.com/TheEmeraldDerpLeader/SecureDataContainer/releases) on github. These builds also come with a copy of the command line executable for [7-Zip](https://www.7-zip.org), which is licensed under GNU LPGL, allowing us to package 7Zip with the release builds.
 
  The executable, SecureDataContainer.exe, should be run by double clicking it and not through a command line because the software relies on the effective local directory being at the .exe file.
 
  This project features a simple interactive command line interface. Start by entering AddFiles to begin specifying the files to add to the archive. You can then specify access levels as Admin, PrivUser, User, and Guest. Admins will be able to access all files, while the other roles will only be able to access the files specified to them. Multiple roles can be specified by using an & between roles, e.g. PrivUser&User "file1". It is recommended to first write out the command in a text editor, then copy it into the command line interface. This way, it is easier to edit mistakes, and you can keep a copy of the command in case it fails.
  
  After specifying files, type stop to exit the AddFiles interface. Type GenerateArchive to start creating the archive. Once an archive name is specified, the archive will be created and the main keys will be printed to the console. If these keys are lost, the data in the archive will be irretrievable. However, as long as you have the admin key, then all keys in the archive, including the other access level keys, can be obtained in __adminKeys.csv. Lastly, if 7zip fails to add any files to the archive, then there will be a message containing the files which couldn't be added.
  
  The created archive will sometimes keep the directory structure of the files. If a file path specified is local to the executable and doesn't have any ../ paths, then the folder structures of the files will be maintained. Otherwise, the file will just be stored at the top of the archive, next to the access key csv files.
  
  Each access key csv file contains names of files and their associated keys. To use your key to access files, find the correct access key csv, open it with your access level's key, then note the file names and keys. Each file can then be opened or extracted using their relevant key. Note that because 7Zip doesn't normally expect files with different keys, when accessing a different file, the 7Zip file viewer must be closed and reopened, otherwise it will try to use the last key instead of prompting the user for a new key.
  