# UNO

UNO is a replica of the card based game UNO by Ubisoft. 

## Installation 

Simply git clone into repository. I am using Visual Studio Code for running and debugging. Follow the instructions here for C++ VS code support: https://code.visualstudio.com/docs/cpp/config-linux

Modify tasks.json to compile multiple C++ files by doing the following:

You can modify your tasks.json to build multiple C++ files by using an argument like "${workspaceFolder}/*.cpp" instead of ${file}. You can also modify the output filename by replacing "${fileDirname}/${fileBasenameNoExtension}" with a hard-coded filename (for example 'helloworld.out').


