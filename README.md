# DigiGuide – Hash Table with Chaining

A menu based console application written in C that stores and manages Digimon records using a hash table of size 1000 with separate chaining. Completed as a course assignment using instructor-provided starter code. My contributions included Add, Delete, Search, Filter, Display, Dynamic memory allocation, and Hash Function.

## Features:
- Custom polynomial rolling hash function 
- Collision resolution using singly linked lists
- Load records from a pipe-delimited text file
- Add new Digimon
- Delete by name
- Search by name
- Filter by starting letter
- Display entire hash table
- Count total entries
- Proper dynamic memory allocation and cleanup

**#Compile and Run:**
gcc Code6_1002148516.c -o digiguide
./digiguide Code6_1002148516_InputFile.txt
