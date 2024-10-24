### create_folder.sh
**Usage:** create_folder.sh [folder] [size] [dataFileName]

Creates a zero-filled disk file, formats it as ext4, and mounts it to a specified directory.

Parameters:
  - **folder**            The name limit directory (e.g. log)
  - **size**              Size of the limit directory. (e.g. 1024)
  - **dataFileName**      Path to the file to be created (e.g. ./dataFile)

Example:
  - create_folder.sh log 1024 dataFile\
This command creates a 1024 MB file named 'dataFile', formats it as ext4, and mounts it to the directory './log'.
### create_files.sh
**Usage:** create_files.sh [directory] [numberFiles(default:5)] [fileSize(default:128)]

Creates the N files with M size in the specified folder

Parameters:
  - **directory**         Path to the directory where files will be created (e.g. ./log)
  - **numberFiles**       The number of files (e,g 3)
  - **fileSize** 	    The size one file in MB (e.g 128)

Example:
  create_files.sh ./log 5 128\
  This command creates a 5 files with size 128MB in directory ./log
### create_folder.sh
**Usage:** check.sh [folder] [limit(default:50)] [numberFilesZip(default:3)]

Аrchives the N oldest files from the specified folder, deleting them from it and archiving them in a new folder "backup"

Parameters:
 - **folder**            Path to the limited directory with files (e.g., /log).
 - **limit**     	    Size of the directory at which the script will be executed (e.g., 50).
 - **numberFilesZip(N)** The number files which will be archives.

Example:
  check.sh ./log 50 3\
  This command archives a 3 files from directory log to directory backup and delete them if log.size > 50%.
