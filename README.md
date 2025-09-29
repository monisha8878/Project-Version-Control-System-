
# Version Control System

This project is a C++ implementation of a simplified version control system. It provides functionality for creating and managing files, taking snapshots, updating content, rolling back to earlier versions, and tracking file history. The design uses multiple data structures such as **trees** for organizing versions, **heaps** for retrieving files with the largest version count or frequently updated files, and **hash maps** for fast indexing and lookup.

---

## Project Structure

The system is organized into multiple files:

- **filefunctions.cpp**  
  Handles file operations such as `create`, `read`, `insert`, `update`, `snapshot`, `rollback`, and `history`.

- **filestructure.cpp**  
  Defines core classes (`File`, `TreeNode`) and manages file data, content, and version details.

- **heap.cpp**  
  Manages files based on time and version counts using heap structures, supporting efficient retrieval of recent or largest versioned files.

- **map.cpp**  
  Implements hash maps for mapping file names and versions to file objects, ensuring fast access and storage.  
  Contains:
  - `version_map` – maps version IDs to `Version` (implemented via `Vector`)  
  - `file_map` – maps file names to `File` objects (implemented via HashMap)

- **mainfunction4.cpp**  
  Driver program for testing and demonstrating functionalities.  
  > **Note:** The program expects input in a specific layout. User should provide correct inputs only.  

---

## Usage Guide

### Automation Script
The project includes a batch script `run.bat` to automate tasks. It runs the compiled executable `mainfunction4.exe`, which contains all project files and functions.  

```bash
.\run.bat
```
Note: Ensure you have permission to run batch files and executables on your system.
---
### Features / Commands
-	CREATE <filename> [content] : Creates a new file with optional initial content.
  
-	READ <filename> : Displays the current content of the given file.

-	INSERT <filename> <extra_content> :  Appends new content to the file.

-	UPDATE <filename> <new_content> :  Replaces the file’s content with new content.

-	SNAPSHOT <filename> [message] :  Creates a snapshot (like a commit) of the file with a message.

-	ROLLBACK <filename> <version_id> :  Rolls back the file to a previous version by version ID.

-	HISTORY <filename> : Shows all snapshots of the file with version ID, content, message, and timestamp. Time stamp is shown in the local time of the users machine . 

-	RECENT_FILES <n> :  Displays the n most recently edited files. Note: If the time interval between two consecutive inputs is shorter than the resolution provided by the ctime library, the program may produce incorrect results, as it will be unable to distinguish between the two recorded timestamps.

-	BIGGEST_TREES <n> :  Shows the n files with the largest number of versions (biggest version trees). NOTE – The program might cause undefined behaviour if user has created k files only but commands BIGGEST_TREES <N> where N>k. In that case kill the terminal and run again.

-	END :  Ends the program and clears all stored data.

---

## Overall, the project demonstrates how fundamental data structures can be applied to build a functional version control system.


---
 Contribution & Permissions

This repository is for **personal learning use only**. 
Please **do not submit pull requests or edits**. This project is not accepting contributions.

---
Licence


This repository is intended for educational and personal learning use only.
If the course content is proprietary, this code is not for redistribution or commercial use.

