# RU-Language
## Introduction
RU-Language is a programming language written in C. It uses bytecode and VM to execute the instructions. RU-Lang is dynamically-typed and object-oriented language.

## Build
```
make
```
## Repl
```
./main
```
## File
```
./main <filename>.ru
```

## Documentation
### Print statement
```
chhaap "this is ru tutorial";
```
### Class Declaration
```
khaaka A {
    method() {
        chhaap "this is a class method";
    }
}
```
### Function Declaration
```
tafaaul loop(number) {
    chhaap "this is a function";
}
```
### Variable Declaration
```
elaan dard <- "this is pain";
```
### For Loop
```
shoro (elaan i <- 0; i < number; i <- i + 1) {
        chhaap i;
}
```
### If-else
```
agr (false) {
    chhaap "nouman";
}
warna {
    chhaap "amir";
}
```

### Return in functions
```
tafaaul loop(number) {
    shoro (elaan i <- 0; i < number; i <- i + 1) {
        chhaap i;
    }
    lautana "Done";
}
```
### While-loop
```
elaan i <- 0;
jbtk (i < 5) {
    chhaap i;
    i <- i + 1;
}
```
### Inheritance
```
khaaka A {
    method() {
        chhaap "A";
    }
}
khaaka B -> A {
    method() {
        chhaap "showing inheritance";
    }
}
```
### Method and fields
```
khaaka A {
    method() {
        chhaap "A";
    }
}

A.method();
A.name <- "ha ha ha";
```
### This
```
khaaka A {
    method() {
        chhaap this.name;
    }
}

elaan a = A();
a.name <- "ha ha ha";
a.method();
```
### Super
```
khaaka A {
    method() {
        chhaap "A";
    }
}

khaaka B -> A {
    method() {
        elaan closure <- super.method;
        closure();
    }
}

elaan b <- B();
b.method();
```
### True
```
durust
```
### False
```
glt
```