# SocialNetwork
Implementing server side of a local social network "SocioPath". some features are creating and validating users, sharing status with friends, searching for new friends and sending friend requests etc.

## How to compile and run
first initalize a server, by running the program with 3 arguments, path to logfile and path to output file and entering the mode.
then, initalize two instances of players by entering the following arguments: path to input, socket_port, player name, mode, and output file path.
an example is listed below:

### On Windows OS: 
1. download and install MinGW: https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/
2. download all project files into the same folder, insert the following command: cd /...your_file_path.../
3. insert the following command: gcc *.c -o Server
important: validation.txt and profile.txt must be in the same folder, review them to see relevant format for each text file. 


## IDE
Written and compiled in Visual Studio 2017

## License
[MIT](https://choosealicense.com/licenses/mit/)
