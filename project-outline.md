# NetWord - Outline of the project

This document lists the project components as in a backlog-product from the [*SCRUM*](https://fr.wikipedia.org/wiki/Scrum_(d%C3%A9veloppement)#Glossaire) terminology.

NetWorld aims to become a KISS (keep it stupid simple) Game-engine in which the game entities interact on a world seen as a network of key positions (nodes).

The development is organized over several functionalities listed here from the most mandatory to the less important:
Each Functionnality groups several components to develop as UserStories under the responsibility of one or two main developers.

## Fct.1 - Project Framing.
---
- @MainDevelopers:
- @SecondaryDevelopers:
---

This functionality cover a framework for the team of developers.

- Developers can communicate with others (discord, ...)
- A developer can share a working directory (git, gitlab, ...)
- Hello World’s programmes can be completed and executed.
- Everyone can refer to documentation.
- A realize by merging contribution could be generated.
- A solution for Unit Test is operational.

## Fct.2 - NetWorld
---
- @MainDevelopers:
- @SecondaryDevelopers:
---

NetWorld represent the center piece of the game engine. It is the programme component that glue all the others. 
It is an environment for the game entities, viewed as a planar graph modelling all the possible movements. 

- A NetWorld is composed of nodes at specific position (x,y). **DONE**
- Nodes are connected to other with edges. **DONE**
- Nodes can contain entities.
- It is possible to generate NetWorld randomly (example: random nodes and Gabriel graph).
- An algorithm provides paths in the NetWorld between two positions (A*).
- Long edges are subdivided with intermediate nodes in order to generate an almost regular game tabletop.

## Fct.3 - Entities

---
- @MainDevelopers:
- @SecondaryDevelopers:
---

Entities are the game element capable of actions. This functionality mainly regroups the basic interactions of those entities between them and with the NetWorld.


- An entity is at a specific node.
- Entities see the different possible movements (edges from the nodes) and can try one. The movement succeed only if the node is not over populated.
- Entities can act on the NetWorld (change the colour of a node for instance).
- Entities can act over other entities (damaging them for instance).

@MainDevelopers:

@SecondaryDevelopers:

## Fct.4 - User Interface
---
- @MainDevelopers:
- @SecondaryDevelopers:
---

This functionality focus on a graphical rendering of the NetWold and to provide a control through the mouse and keyboard.

- The program starts on welcome menu
- It is possible to launch and visualize a NetWorld and its Entities
- Players can save and load a game 
- Players can select its own entities and provide them for an expected location.
- Animations are triggered when an entity move from a node to another.


## Fct.5 - Robust Development environment
---
- @MainDevelopers:
- @SecondaryDevelopers:
---

- All developers can refer to a good-practice doc for code.
- Developers would use a proper C unit-test framework.


## Fct.6 - Game-play
---
- @MainDevelopers:
- @SecondaryDevelopers:
---

It is time to define a game objectives and maybe change the name of the project.

## Fct.7 - Programme distributed programme
---
- @MainDevelopers:
- @SecondaryDevelopers:
---

The goal here is to distribute the game process.

- A player owns entities.
- The player process can be executed on an independent computer process (network)
- The NetWorld simulation can be distributed over processes.
- The game is reachable from a web interface.

## Fct.8 - Tanks

Nodes are defined with a collection of digital tanks where resources can be placed. (water for instance)

- Digit represent a discrete value in a fixed capacity tank.
- Node contain a collection of tanks as Digit.
