# Protein Viewer

## Team Members

1. Konstantin Yurievich Mosklaenko (19213, k.moskalenko@g.nsu.ru) *
2. Maksim Borisovich Sharapov (19214, m.sharapov@g.nsu.ru)
3. Ekaterina Vladimirovna Verkhozina (19214, e.verkhozina@g.nsu.ru)

## Project Description

Proteins are large molecules that can be represented as 3D structures. The goal of the project is to create a protein rendering tool on top of a modern game engine. The project will be implemented as a desktop application that supports keyboard and mouse input. In addition, we plan to support real-time integration with third-party bioinformatics software.

## Risk Analysis

1. Not being able to parse a `Protein Data Bank (.pdb)` file format.  
   *Possible solution*: find an existing implementation of the file parser.
2. Not being able to visualize some preset styles of protein representations.  
   *Possible solution*: use simplified representations of protein structures.
3. Not being able to meet the performance requirents on some hardware.  
   *Possible solution*: reduce the number of polygons and disable some visual effects.

## MVP Deadlines

- **October, 15**: Render and move around a surface with some plain objects and a light source.
- **November, 1**: Parse a `Protein Data Bank` file and render its very basic features as a set of spheres in a 3D space.
- **December, 1:** Implement another (more complex) type of protein sturcture visualization.

## The First Release

At the end of semester we are going to present a desktop application, supporting importing and visualizing `Protein Data Bank` files, with convenient navigation in the 3D space and support of multiple rendering presets.

## Trello

The Trello board is available [here](https://trello.com/b/5427Hns8).

