# Ubject - Object-Oriented Programming in C

**Ubject** is a minimalistic library for implementing object-oriented programming in C, providing a way to work with classes and objects in a C codebase. It allows you to define classes, create objects, and perform object-oriented operations in a structured manner.

## Table of Contents

- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Ubject provides a set of macros and functions to work with classes and objects. It allows you to create classes, define class methods, create objects, and perform object-oriented operations like constructor and destructor invocation.

Ubject is designed with simplicity and minimalism in mind. It does not introduce complex syntax or concepts rather it demonstrates object oriented pprograming in plain C.

## Features

- Define and create objects and classes in C.
- Support for constructors and destructors.
- Class inheritance and method overriding.
- Efficient memory management.
- Works on both Windows and Unix-like systems.

## Getting Started

### Prerequisites

- A C compiler
- A basic understanding of C programming

### Installation

Clone the repository:

```bash
git clone https://github.com/iudah/ubject.git
```

Include the necessary headers in your project:

```c
#include "Ubject.h"
#include "Ubject.r.h"
```

## Usage

### Defining a Class

To define a class, create a struct that extends `Ubject`. Here's an example:

```c
struct MyObject
{
    struct Ubject _;
    // Add your class-specific fields here.
    int my_int;
};
```

If your class requires some methods, create a struct that extends `TypeClass`. Here's an example:

```c
struct MyObjectClass
{
    struct TypeClass _;
    // Add your class-specific methods here.
    int (*myMethod)(int parameter_1, int parameter_2);
};
```

Then you declare the class handler in your header. This would be used to create instances of your class.

```c
extern const void *MyObject;
```

### Initializing the Class

To finish the class, you need a function to create an object that represents the class. Here's an example:

```c
const void *MyObject = 0;

void initMyObject(){
    if(!MyObject)
    MyObject = new(TypeClass, Ubject,
                    sizeof(struct MyObject),
                    ctor, MyObject_ctor,
                    dtor, MyObject_dtor,
                    className, "MyObject",
                    NULL);
}
```

If your class has it own methods, then you need to first initialize the meta-class.

```c
const void *MyObjectClass = 0;
const void *MyObject = 0;

void initMyObject(){
    if(!MyObjectClass)
    MyObjectClass = new(TypeClass, TypeClass,
                        sizeof(struct MyObjectClass),
                        ctor, MyObjectClass_ctor,
                        NULL);
    if(!MyObject)
    MyObject = new(MyObjectClass, Ubject,
                    sizeof(struct MyObject),
                    ctor, MyObject_ctor,
                    dtor, MyObject_dtor,
                    className, "MyObject",
                    myObjectMethod, myObjectMethodImpl,
                    NULL);
}
```

### Creating an Object

To create an object of a specific class, use the `new` function. Here's an example:

```c
struct MyObject *myObject = new(MyObject, /* constructor arguments */);
```

### Destructor

To release memory associated with an object, use the `delete` function. It will also call the destructor if defined.

```c
delete(myObject);
```

### Inheritance

Ubject supports class inheritance. When defining a new class, you can specify a superclass:

```c
struct SubObject
{
    struct MyObject _;
    // Add subclass-specific fields here.
};
```

### Method Overriding

You can override methods in subclasses by passing the subclass method when initializing the class.

```c
SubObject = new(MyObjectClass, MyObject,
                    sizeof(struct SubObject),
                    ctor, SubObject_ctor,
                    className, "SubObject",
                    myObjectMethod, subObjectMethodImpl,
                    NULL);
```

## Examples

Coming soon...

## Contributing

Contributions are welcome! If you have any improvements, or bug fixes, please open an issue or submit a pull request on [GitHub](https://github.com/iudah/ubject).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspiration from object-oriented programming languages.
- C programming language for its simplicity and power.
