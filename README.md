# getFilesC
Move specified files from one dir to another, I use it to move photos with dates in the filename.

This executable was tested on a Debian system, and will not work on Windows or MACOS.

## Required Dependencies
```
git
gcc
make
```
These packages are fairly common, and can be installed on Debian based systems using `apt`:
```
sudo apt install git gcc make
```

## Installation
Clone the repository and, with root access, run `make install` followed by `make clean` to install `getFiles`.

With root access run `make uninstall` to uninstall the `getFiles` executable.

If you are looking for a list of commands to run, here they are:
```
git clone https://github.com/amurph24/getFilesC.git
cd getFilesC
sudo make install
sudo make clean
```
To uninstall, navigate to the getFilesC directory and run:
```
sudo make uninstall
```

## Usage
Search directory tree (rooted at the current directory) recursively for files matching regex input,
and copy matching files into an './out' folder. Be wary of hard disk space.
```
getFiles [regex]
getFiles "22\-04\-2000"
```
If an `./out` folder doesn't exist one will be created, the script will exit if an `./out` file exists.

## Upcoming
The `-f` option prompts the script to iterate over a .csv file, using the strings in the `key` column as the regex.
```
getFiles -f [<file.csv>]
getFiles -f students.csv
```
Other planned flags/options:
 - `--first-only`: only copies the first file found, this is helpful if you are only expecting one file to match.
 - `--directory [<dirpath/>]`: relative path to the directory to search, files will still be copied to `./out`.
