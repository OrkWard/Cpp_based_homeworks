This workspace is used to learn basic C++ language. Only single source files, perhaps.

### project 2
#### 界面
提示符：按1开始输入学生信息，按2输出表单，按3退出程序。  
在一行内输入信息，回车结束输入；输出表单后再次弹出提示框

#### 输入
学生信息：名字；课程（名字/代号）；分数。用空白符分隔

#### 数据结构
 - 类Student：存储了一个学生的所有数据，string类型的名字，链表形式的课程和分数
 - 数组Students，下标为学生no
 - 结构体Course，存储课程名-分数对和链表指针

### project 3
The procedure are listed below:
 - First, player enter the game, and see the lobby.
 - Second, choose a direction and go to the next room.
 - Recurtion, until find the princess or the monster.
 - If found the monster, the game end, and the player can choose to quit or replay; or if found the princess, communicate and begin to go back to lobby.
 - If back to the lobby, then player wins the game.

There are only one important object in the game, the map. The map is a matrix of rooms, which is a class containing a **flag** to show it's lobby, princess, monster or normal; four **direction** to show how go to the next room. 
How to construct the map? 
1. Set the lobby at the center;
2. Construct the princess and the monster room randomly; 
3. Construct the doors randomly(travel through the whole maps, check for each door and rondomly decide whether there is a door or not)
4. check if the princess and the monster are reachable, if not, reconstruct the map.

### project 4
#### Requirement
 - `pdadd` is used to add an entity to the diary for the date. If an entity of the same date is in the diary, the existing one would be replaced. `pdadd` reads lines of the diary from the stdin, line by line, until a line with a single `.` character or the `EOF` character (`<C-z>` in Windows)
 - `pdlist` list all entities in the diary ordered by date. If the `start` and `end` date are provided through command line parameters, it lists entities between start and end only. This program lists out to the stdout.
 - `pdshow` prints the content of the specified date out to the stdout.
 - `pdremove` removes one entity of the date. It return 0 on success and -1 on failure.
 The software stores the diary in one data file, and reads it to the memory at the beginning of each program, and stores it back to the file at the end of the process.


This project contains four programs, now specify the usage. 
 - `pdadd`: none parameter. Output a single file, file format:
   - Base on character
   - Each entity of diaries is formed with 1. Date; 2. Content, all in a single line, separated by two spaces.
   - No empty line between or after
 - `pdlist`: one or two parameter: range, use like `pdlist [start] [end]`. Output the diary from start to end. If only one parameter specified, treat it as start defautly and add option [-r] to reverse. As for the date format, treat the first four digit as year, the next two as month, the next two as day, and the input number can be 4-digits, 6-digits or 8-digits. Add [-a] to any parameters specified after and list all the entity.
 - `pdshow`: one parameter: date. Must be an 8-digits .
 - `pdremove`: one parameter: date. The same format as before.
#### Implementation
File structure:
```
pd.h
pd.cpp
	pdadd.cpp
	pdlist.cpp
	pdshow.cpp
	pdremove.cpp
```
pd.h implementation:
```
class Diary: store the whole diary, inherit from container map, date as key, String as value; a method to read an diary in, a method to print an diary.
```