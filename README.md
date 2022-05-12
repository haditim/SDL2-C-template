# C and SDL2 project starter template
I use this template to create C projects.

## Directory structure
I recommend you use the following structure:

``` shell
.
├── Makefile
├── README.md
└── src
    ├── canvas
    │   ├── canvas.c
    │   └── canvas.h
    ├── main.c
    └── player
        ├── player.c
        └── player.h
```
In this case, after compilation (`make`), you'll get:

``` shell
.
├── bin
│   └── main
├── Makefile
├── obj
│   ├── canvas
│   │   └── canvas.o
│   ├── main.o
│   └── player
│       └── player.o
├── README.md
└── src
    ├── canvas
    │   ├── canvas.c
    │   └── canvas.h
    ├── main.c
    └── player
        ├── player.c
        └── player.h
```

## Makefile
Makefile has wildcards, allowing sub-directory source file discovery.

## Requirements
You need to have `time` installed on your system.
