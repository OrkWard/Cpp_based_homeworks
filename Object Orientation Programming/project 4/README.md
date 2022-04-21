This project contains four programs, now specify the usage. 
 - `pdadd`: none parameter. Output a single file, file format:
   - Base on character
   - Each entity of diaries is formed with 1. Date; 2. Content, all in a single line, separated by two spaces.
   - No empty line between or after
 - `pdlist`: one or two parameter: range, use like `pdlist [start] [end]`. Output the diary from start to end. If only one parameter specified, treat it as start defautly and add option [-r] to reverse. As for the date format, treat the first four digit as year, the next two as month, the next two as day, and the input number can be 4-digits, 6-digits or 8-digits. Add [-a] to any parameters specified after and list all the entity.
 - `pdshow`: one parameter: date. Must be an 8-digits .
 - `pdremove`: one parameter: date. The same format as before.

the batch script is tested under Windows cmd.exe, cannot run on PowerShell.