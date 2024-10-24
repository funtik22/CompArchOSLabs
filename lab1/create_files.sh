#!/bin/bash

function help() {
    cat << EOF
Usage: create_files.sh [directory] [numberFiles(default:5)] [fileSize(default:128)]

Creates the N files with M size in the specified folder

Parameters:
  directory         Path to the directory where files will be created (e.g. ./log)
  numberFiles       The number of files (e,g 3)
  fileSize 	    The size one file in MB (e.g 128)

Example:
  create_files.sh ./log 5 128
  This command creates a 5 files with size 128MB in directory ./log
EOF
}

if [[ "$1" == "--help" ]]; then
    help
    exit 0
fi

directory=${1:-"./"}
numberFiles=${2:-5}
fileSize=${3:-128}

if ! [ -d $directory ]; then
	"$directory is not a directory"
	exit 0
fi

if ! [[ "$numberFiles" =~ ^[1-9]+$ ]]; then
    echo "$numberFiles is not a number."
    exit 0
fi

if ! [[ "$fileSize" =~ ^[1-9]+$ ]]; then
    echo "$fileSize is not a number."
    exit 0
fi

for (( i=1; i<=$numberFiles; i++ ))
do
	dd if=/dev/zero of=$directory/file$i bs=1M count=$fileSize
done
