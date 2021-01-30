.gorgasset File
=================

Gorg uses special files, called asset files, which contain information about a given
asset. Instead of opening the asset file or the asset folder, gorg only opens these
meta files, which are much faster to parse through and contain the exact
information gorg requires to provide relevant search results.

The Payload
----------------------

A meta file is always located inside of a folder which contains the actual
asset payload. This maximises the probability that the payload and the asset
file remain together throughout the lifetime of the asset, regardless of which
software is used to manipulate the payload. The expected structure is the
following:

* :code:`<path to the folder asset>/<name of the folder asset>/.gorgasset`


Meta File Content
------------------------

The meta file is a human readable yaml file that contains information about
its asset. The file contains many fields which can be used to help find the
file that you are looking for. There are some fields which are mandatory.
If these fields are missing from the meta file, the asset will not be considered
by SAM. There are many more optional fields which do not need to be populated
but that will help SAM return more relevant search results.

Example Meta File
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is an example of a simple .gorgasset file. It contains a title and
a description, a series of keywords and a custom class field::

  title: Biology 101 - Second Assignement

  description: This assignment, on basic human biology, counted for 40%
    of our mark. It covered the anatomy of the brain and basic neural cell
    structure.

  keywords:
    biology
    assignment 
    brain
    neural
    neurons

  class: BIO101


    

Mandatory Fields
^^^^^^^^^^^^^^^^^^^^^

The meta file must contain at least the following fields:

* :code:`title`: The title of the given file
* :code:`description`: The description of the file, in plain text


Optional Fields
^^^^^^^^^^^^^^^^^^^^^^^^^

The meta file can contain any of the following fields, although
they are not necessary for the asset to be recognised

* :code:`keywords`: Keywords that can be added to help find a file. These may include common mispellings or abreviations and related terms.

Custom Fields
^^^^^^^^^^^^^^^^^^^^^^^^

Custom fields are not yet supported
