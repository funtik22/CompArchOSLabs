#!/bin/bash

function help() {
    cat << EOF
Usage: check.sh [folder] [limit(default:50)] [numberFilesZip(default:3)]

Аrchives the N oldest files from the specified folder, deleting them from it and archiving them in a new folder "backup"

Parameters:
  folder            Path to the limited directory with files (e.g., /log).
  limit     	    Size of the directory at which the script will be executed (e.g., 50).
  numberFilesZip(N) The number files which will be archives.

Example:
  check.sh ./log 50 3
  This command archives a 3 files from directory log to directory backup and delete them if log.size > 50%.
EOF
}

if [[ "$1" == "--help" ]]; then
    help
    exit 0
fi

if [ $# -eq 0 ]; then
    echo "No arguments"
    exit 0
fi

path=$1
limit=${2:-50}
numberFilesZip=${3:-3}

if ! [[ "$limit" =~ ^-?[0-9]+$ ]]; then
    echo "$limit is not a number."
    exit 0
elif ! [[ "$numberFilesZip" =~ ^-?[0-9]+$ ]]; then
    echo "$numberFilesZip is not a number."
    exit 0
fi


if [ -d $path ]; then
        folderSize=$(df -h | grep $(basename $path) | grep -Po '([0-9]{1,2}%)' | grep -Po '([0-9]{1,2})')
        if [ -z $folderSize ]; then
                echo "The folder haven't limited size"
                exit
        fi
    
	if [ $(expr "$folderSize" + 0) -ge $limit ]
        then
                if ! [ -d ./backup ];
                then
                        mkdir ./backup
                fi

                for i in $(ls -1t $path | tail -n $numberFilesZip);
                do
                        tar -rf ./backup/backup.tar $path/$i
                        rm $path/$i
                done

                if [ -f ./backup/backup.tar ]; then
			gzip ./backup/backup.tar
			echo "Successful"
		else
			echo "There are not files to zip"
		fi
	else
		echo "the folder size is less than the limit"
        fi
elif [ -f "$path" ]; then
    echo "$path is a file, but a directory was expected"
    exit 0
else
    echo "Invalid path to directory"
fi


