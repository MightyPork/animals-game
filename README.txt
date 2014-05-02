Animals Game
============

Released under the MIT license.


Usage
-----

    $ ./animals -h

    Animals Game
    usage: animals [-v] [-f DB_FILE] [-h]
    -v, --verbose  Enable extra debug messages
    -f, --file     Specify location of data file
    -h, --help     Show this help


Start without any flags to play with the default data file.


Data file
---------

The data file is PLAIN TEXT, so you can edit it with any text editor - just be 
careful about the syntax.

    <index> Q (<yes_index>,<no_index>): QUESTION TEXT?<newline> 
    <index> A: ANIMAL NAME<newline> 

Order does not matter, but all yes/no indexes must exist within the file!

It's possible to build weird stuff like circular references, be creative ^^.

(To start with clean sheet, delete the "animals.dat" file.)
