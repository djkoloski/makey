# Makey
Build simply

## Usage
**Compiling**
```
$ ninja
```
**Running**
```
$ Makey && ninja
```

## Directory Layout
Example:
```
Solution
|-- Project1
|   |-- Source1.c
|   |-- Source2.cc
|   |-- Source3.cpp
|   +-- Source4.cxx
|-- Project2
|   +-- Source.cpp
|-- Build (generated)
|   |-- Project1
|   |   |-- Source1.obj
|   |   |-- Source2.obj
|   |   |-- Source3.obj
|   |   +-- Source4.obj
|   +-- Project2
|       +-- Source.obj
+-- Bin (generated)
    |-- Project1.exe
	+-- Project2.exe
```