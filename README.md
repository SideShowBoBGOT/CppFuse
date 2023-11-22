# CppFuse - Thread-Safe Filesystem Implementation with FUSE Library
## Overview

CppFuse is a C++ implementation of a filesystem using the FUSE (Filesystem in Userspace) library. This filesystem provides a set of standard operations, including getattr, readlink, mknod, mkdir, unlink, rmdir, symlink, chmod, read, write, and readdir. The implementation is thread-safe, ensuring concurrent access is handled appropriately.

## Author

    Serhii Panchenko

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Features

    Thread-safe implementation
    Support for standard filesystem operations
    Ability to find full paths of stored files by their names

## Installation
Clone the repository:

    $ git clone https://github.com/SideShowBoBGOT/CppFuse

Build the project:

    $ cd CppFuse
    $ cmake -S . -B build
    $ cmake --build build

Create FIFO file for communication:
    
    $ mkfifo fifo
    $ chmod fifo 0775

Create folder for filesystem:

    $ mkdir /mnt/fuse
    $ chmode /mnt/fuse 0775

Mount the filesystem:

    $ mount -t /mnt/fuse
    $ fusermount -u /mnt/fuse

Run the filesystem:

    $ ./build/MainExecutable -f -d -m /mnt/fuse -p fifo

## Usage

Once the filesystem is mounted, you can interact with it using standard filesystem commands.

Go to the mounted directory:
    
    $ cd /mnt/fuse

Create subdirectory:

    $ mkdir bar

Write to file:

    $ echo "Hello, World!" > bar/file.txt

Read from file:

    $ cat bar/file.txt
>    Hello, World!

Create a symbolic link to file:

    ln -s bar/file.txt myLink

List the contents:

    $ ls -l
    total 0
    drwxrwxr-x 2 sideshowbobgot sideshowbobgot  0 Jan  1  1970 bar
    lrwxrwxr-x 2 sideshowbobgot sideshowbobgot 12 Jan  1  1970 myLink -> bar/file.txt

Find file by name:
    
    $ cd <DownloadPath>/CppFuse/build
    $ ./FindByName -p <DownloadPath>/CppFuse/fifo -f file.txt
    /bar/file.txt

Remove a file

    $ rm bar/file.txt

## Contribution

Contributions are welcome! Feel free to submit issues and pull requests.

## Acknowledgments

This project is built upon the FUSE library, and the contributions of the FUSE community are greatly appreciated.

## Contact

For any inquiries or support, please contact at:
### Email
    sideshowbobgot@gmail.com.
### Telegram
    @sideshowbobgot