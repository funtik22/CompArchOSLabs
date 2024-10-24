#!/bin/bash
folder=${1:-"log"}
size=${2:-1024}
dataFileName=${3:-"dataFile"}

function help() {
        cat << EOF
Usage: create_folder.sh [folder] [size] [dataFileName]

Creates a zero-filled disk file, formats it as ext4, and mounts it to a specified directory.

Parameters:
  folder            The name limit directory (e.g. log)
  size              Size of the limit directory. (e.g. 1024)
  dataFileName      Path to the file to be created (e.g. ./dataFile)

Example:
  create_folder.sh log 1024 dataFile
  This command creates a 1024 MB file named 'dataFile', formats it as ext4,
  and mounts it to the directory './log'.
EOF
}
if [[ "$1" == "--help" ]]; then
    help
    exit 0
fi


if ! [[ "$size" =~ ^-?[0-9]+$ ]]; then
    echo "$size is not a number."
    exit 0
fi

mkdir ./$folder
dd if=/dev/zero of=./$dataFileName bs=1M count=$size
mkfs.ext4 ./$dataFileName
mount -o loop,rw,usrquota,grpquota ./$dataFileName ./$folder
echo "$(pwd ./$dataFileName)/$dataFileName /$folder ext4 loop,rw,usrquota,grpquota 0 0" > /etc/fstab
