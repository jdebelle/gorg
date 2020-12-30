Commands
========================

This page covers the various commands that gorg has to offer. The general syntax
for the usage of gorg is the following::

    gorg [--version] <subcommand> [<args>]


Subcommands
^^^^^^^^^^^^^^^^^^

init *ASSET_PATH*
    Initialize a gorg asset. The asset can either be a file or a folder.
    This will create a template gorgasset file and will open a text editor
    to edit the file. Upon closing, basic validation of the gorgasset file
    will be done.


generate *GORGGEN_FILE*
    This will build an index which can then be used to easily search and
    find files on your system.


