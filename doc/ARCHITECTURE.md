# ARCHITECTURE

## Modules

1. Main Module
2. Parser of PDB files

2. Parser of mmCIF files

3. 3D polygonal ribbon diagram generator

![Module Diagram](./module-diagram.png)

## Main Module

The main application that uses parser modules to read files, generate 3D modules and display them on the game scene using Unreal Engine APIs.

## Parser of PDB

`Source/ProteinViewer/parsers/pdb`<br>
Parses PDB files into internal atom structure. 

Reference Go implementation:
https://github.com/fogleman/ribbon/tree/master/pdb

## Parser of mmCIF files

`Source/ProteinViewer/parsers/mmCIF`<br>
Parses mmCIF files into internal atom structure. <br>
https://github.com/RBVI/readcif

## 3D polygonal ribbon diagram generator

`Source/ProteinViewer/ribbon`<br>
Reference Go implementation:
https://github.com/fogleman/ribbon/tree/master/ribbon