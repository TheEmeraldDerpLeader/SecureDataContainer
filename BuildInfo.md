# Build Info
Overview of this project's dependencies, build configuration, etc...

Main dependency is [7-Zip](https://www.7-zip.org), which is licensed under GNU LGPL. This project doesn't directly include any 7Zip files, but note that builds of this software must be packaged with a 7Zip executable.

## Build Environment
This project will be built and tested for Windows, Mac, and Linux. However, specific build related files won't necessarily be provided. Instead, developers need to use this specification to figure out how to configure their own build environment.

The project will be built for 64-bit executables for the mentioned operating systems.

The code in this project should follow C++14 standards, though might not necessarily use modern C++ features. This projects uses \#pragma once, so developer's compilers must support that. Besides that, there are no other limitations on the C++ environment.

## Build Configuration
This project's library dependencies is solely std. Not sure what version or whatever, but it's probably fine.

Additionally, this project requires the [7-Zip](https://www.7-zip.org) executable to be stored near the built executable. Specifically, 7Zip needs to be stored with the built executable at ./7Zip/(7Zip install). The console executable which is downloaded from [here](https://www.7-zip.org/download.html) using the entries marked 64-bit. Probably only 7z.exe and 7z.dll need to be stored for it to work. The latest version at this document's time was 24.09.

## Source File Structure
All source files are in the same folder

No extra include directories

### Example Config
For a project in Visual Studio with the following file structure:<br>
- (SolutionDir)
	- Depends
		- 7Zip
			- (7Zip install)
			- 7z.exe
			- 7z.dll
			- (other files, like the license)
	- (ProjectName)
		- 7Zip
			- (7Zip install)
		- Source
	- x64
		- Debug
			- (output exe)
			- 7Zip
				- (7Zip install)
				- 7z.exe
				- 7z.dll
				- (other files, like the license)
		- Release
			- (similar to Debug)

Add this line to Project Properties BuildEvents => Post-Build Event => Command Line

xcopy "$(SolutionDir)Depends\7Zip" "$(OutputPath)7Zip" /i /e /y

To copy the 7Zip folder from Depends to the respective output directory so it can be used by the .exe and testing environment