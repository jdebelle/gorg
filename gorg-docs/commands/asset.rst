gorg asset
========================

Synopsis
------------------

gorg asset [-\\-init | -i] [-\\-validate] 

Description
------------------

Acts upon a gorg asset in order to initialize, update or validate it's 
searchable data.


Options
------------------

-\\-init or -i
    Initialize the current directory as a gorg asset. This will launch a text
    editor to a partially completed .gorgasset file. Upon saving, the file format
    will be validated and the user will be prompted if asset file is invalid.

-\\-validate
    Validate the current directory as a gorg asset. This will load and parse
    the contained .gorgasset file and will list any errors that it may
    contain.
