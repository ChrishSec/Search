## Search

`Search` searches for a specific file or folder within the file system. It starts from the root directory ("/" for Linux systems or "C:\" for Windows systems) and looks through all directories to find the specified file or folder.

### Build Instructions

- Compile it using [MinGW](https://www.mingw-w64.org/) For Windows:

```gcc search.c -o search.exe```

- Compile it using [GCC](https://gcc.gnu.org/install/) For Linux:

```gcc search.c -o search```

- OR

You can download the latest compiled version from the [releases page]().

### Usage

- #### Windows

```
<file> OR <folder>: The name of the file or folder you are searching for.

[path]: (Optional) If not specified, the search starts from C:\ on Windows systems. It is recommended to specify a starting directory to reduce search time.

-v: (Optional) Enables verbose mode, providing detailed output of the search process.
```

```
C:\Users\User\Documents\Projects\Search>search.exe

 DEVELOPED BY >> ChrishSec

 Usage: search.exe <file> OR <folder> [path] -v


C:\Users\User\Documents\Projects\Search>search.exe flag.txt C:\Users\User\Desktop

Found 5 occurrence(s) of 'flag.txt':
  1) FILE = C:\Users\User\Desktop\1\flag.txt | Attributes: ARCHIVE
  2) FILE = C:\Users\User\Desktop\2\flag.txt | Attributes: ARCHIVE
  3) FILE = C:\Users\User\Desktop\3\flag.txt | Attributes: ARCHIVE
  4) FILE = C:\Users\User\Desktop\4\flag.txt | Attributes: ARCHIVE
  5) FILE = C:\Users\User\Desktop\flag.txt | Attributes: ARCHIVE

C:\Users\User\Documents\Projects\Search>search.exe ChrishSec C:\Users\User\Desktop

Found 4 occurrence(s) of 'ChrishSec':
  1) DIR = C:\Users\User\Desktop\1\ChrishSec | Attributes: DIRECTORY
  2) DIR = C:\Users\User\Desktop\2\ChrishSec | Attributes: DIRECTORY
  3) DIR = C:\Users\User\Desktop\3\ChrishSec | Attributes: DIRECTORY
  4) DIR = C:\Users\User\Desktop\4\ChrishSec | Attributes: DIRECTORY

C:\Users\User\Documents\Projects\Search>
```

- #### Linux

```
<file> OR <folder>: The name of the file or folder you are searching for.
```

```
$ ./search
Usage: ./search <file> OR <folder>

$ ./search findme.xt
Found FILE: /home/user/Downloads/FindMe/findme.xt
Found FILE: /home/user/Music/FindMe/findme.xt
Found FILE: /home/user/Documents/FindMe/findme.xt

$ cat /home/user/Documents/FindMe/findme.xt
YOu gOt it!

$ ./search FindMe
Found DIR: /home/user/Downloads/FindMe
Found DIR: /home/user/Music/FindMe
Found DIR: /home/user/Documents/FindMe

$ cat /home/user/Documents/FindMe/findme.xt
YOu gOt it!
```

## Disclaimer

This program is for educational and research purposes only. Use it at your own risk. The author is not responsible for any damage caused by the use or misuse of this program.

## License

This program is released under the GNU General Public License v3.0. Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.

## Author

This program was developed by [ChrishSec](https://github.com/ChrishSec). Feel free to fork, modify, and distribute it. If you have any questions or suggestions, please reach out to the author on [Telegram](https://t.me/ChrishSec).