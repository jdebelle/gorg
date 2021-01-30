gorg generate
===================

Synopsis
------------------

gorg generate [-\\-root PATH ...]

Description
------------------

Creates a gorgindex.html file in the current directory that points towards
the specified root paths. If the root path is not specified, it is assumed
that the present working directory is also the root folder of the assets.

Options
------------------

-\\-root PATH ...
    Specifies the root of the asset folder that will be populated into the
    gorgindex.html file. If more than one root path is specified, they will all
    be populated into the index file. If no root path is specified, it is
    assumed that the current working directory is both the output folder
    and the current working directory.
    
