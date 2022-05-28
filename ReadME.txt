A MUD game, but with slots in ZJU. (Zombie Theme)
Please read the report first.
Recommend to enter "help" and "hint" frequently in game, "sudo" commands are not recommended. 

Only Support Windows System! (Not support linux or macOS)

File structure:
/src: the source files
/bin: executable file
/doc: files about game information. 
/report: project report
/.vscode: json settings about vscode, can be ignored if not used.

To run:
method 1；
Run MUD.exe (static link version) in bin directly

method 2 (recommended):
Enter command "make" in terminal and run the executable file in /bin

method 3:
Enter command "g++ src/*.cpp -o bin/MUD" in terminal and run the executable file in /bin

method 4:
open the folder with vscode and run using code runner 
