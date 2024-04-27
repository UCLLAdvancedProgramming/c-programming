# The C Programming Language: exercises

In these exercises, we'll see what C has to offer, like its easy access to hardware
and its high performance, but we'll also look at where C code can be difficult to get right.

## Getting set up

In order to make sure everything is set up correctly and uniformly, we'll be using
a dev container. You'll have to install and start [Docker](https://www.docker.com)
first if you haven't done so yet.

You can then clone this repository and open it in Visual Studio Code. Make sure
you install the
[Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
extension.

You can then use CTRL+SHIFT+P and choose "Dev Containers: Reopen in container". It will
then take a while to pull in and build the container.

Once we've reopened the project in our Dev Container, you'll see a menu option on the
left that looks like a triangle with a wrench. This refers to CMake, the build tool we'll
be using.

If you open that you can change the build preset (`Debug` or `RelWithDebInfo`) and launch and debug executables.

## 1. Efficiency

A major reason programmers use lower level languages is because they want to use
resources as efficiently as possible. When I say efficiency I don't necessarily
mean speed. There are all sorts of different resources we may want to optimize for,
e.g.:

- Time
- Memory usage
- Battery draw

Let's see how much faster C code can be than Python code.

Consider [factorial.c](./factorial.c), an implementation of the factorial function
that uses the [GMP](https://gmplib.org/) library.

Q1: Why do we need to use GMP, and we can't just use a normal `int` or `long`?

Now take a look at [factorial.py](./factorial.py).

Q2: Which of these two implementations is easiest to read?

Let's benchmark our two implementations. Make a release build of `factorial.c`
and time how long it takes to get the factorial of `10000`. You can use Bash's
built-in `time` function for that (just put `time` in front of your command).

Now time how long it takes to get the factorial of `10000` using `factorial.py`.

Now try the same thing with 100000.

Q3: How big is the difference in performance between the C version and the Python
version?

## 2. Pointers

Lower level languages like C give programmers direct access to memory. This is
often required to do things like interacting with hardware, and also gives the
programmer a lot of ability to optimize things. Changing where and how data is
stored in memory can make a huge difference in performance.

Higher level languages tend to hide how exactly they use memory from you. In Java
assigning a value to a variable causes you to copy the value if it's a primitive type
or copy a **reference*** if it's an `Object`. The programmer has no choice in the matter.

In C however, when you assign a value to a variable, it is always copied,
regardless of whether their type is primitive or user defined. How can we then
copy a reference to the value rather than copying the value itself?

**Pointers** are the answer to this. A pointer contains a memory address, so when
we copy a pointer, we don't copy the value it points to. We're only copying the address.

### Declaring a pointer

You can declare a pointer type with an asterisk (`*`):

```c
int* p = NULL;
```

The above code creates a pointer to an `int` and sets its value to `NULL`. This is
a special zero value to indicate that the pointer doesn't point to anything.

Q1: What do you think `p` contains if didn't assign the `NULL` value, and had just
declared it with `int* p;`? Note: C generally doesn't do anything you don't tell it
to do.

### Getting the address of a value

You can get a pointer to a value using `&`, the "address-of" operator:

```
// Creates an int with the value 12
int i = 12;
// Takes the address of i and stores it in p
p = &i;
```

### Getting the value from the address

If you want to follow the address of a pointer to its value, you can use `*`, the
"indirection" operator:

```
// Stores 5 in the location pointed to by p
*p = 5;
```

The asterisk can thus mean a few different things: when used in the type declaration like
`int*` it means "pointer to int". When used in an expression like `*p` it means: take the
value pointed to by `p`.

Q2: There's yet another meaning of the asterisk. What other meaning does it have that
you're used to from other programming languages?

Q3: What's the value of `i` after all of this code:

```c
int i = 12;
p = &i;
*p = 5;
```

### Writing a `swap` function

Consider the code in [swap.c](./swap.c). Try to write a swap function that exchanges
the value of `i` and `j` so that the output becomes `i = 5, j = 2`.

## 3. Malloc and free

Up until now, we've been putting things on the stack. We can't use the stack however,
when we want arbitrarily large amounts of memory or we want to keep the data around
when we return from our function. In these cases, we have to use the heap.

To **allocate** memory on the heap we can use the `malloc` function:

```c
// Allocates 5 bytes, chars is a pointer to the first byte
char* chars = malloc(5);
```

The `char` type (from character) is used to refer to a single byte. C calls these
`chars` because at the time that C was invented we were using character sets
where every character was less than one byte in size. This is no longer necessarily
true nowadays, but this is the reason why C refers to bytes as `char`s instead of
having a separate `byte` type.

C doesn't have a built-in garbage collector that will automatically free memory when
we're done with it, so we'll have to **free** it when we're done.

```c
free(chars);
```

If we don't free memory when we're done using it, we'll get a **memory leak**: as far as
the operating system is concerned we're still using the memory even if we don't have
any use for it anymore.

Q1: Are garbage collected languages immune to memory leaks?

Note that `free` does not change the value of `chars`, so `chars` now points to freed
memory. Trying to use that memory after we called `free` is called a "**use after free**"
error, and could result in a crash, or worse.

Q2: What's worse than a crash?

### Fixing memory issues

Consider the code in [memory.c](./memory.c). This code has some issues, see if you can spot
them. We've got:

- Multiple memory leaks
- An array index out of bounds error
- A double free

Errors like double free, array index out of bounds access, or use after free all result
in something we call **undefined behavior** in the C and C++ world. These are things that,
as far as the C standard is concerned, should not happen, and it's up to the programmer
to make sure they don't happen. The C standard does not specify what should happen if it
does.

Q1: Does Java have undefined behavior? What happens if we try to access an array outside of
its bounds?

Memory errors can be tricky to find and fix. Luckily we have tools to assist us. One
of those tools is called [Valgrind](https://valgrind.org/).

Put `valgrind --leak-check=full` before your executable, and see what it finds. Try
to fix all memory errors.

## 4. Inline assembly

Sometimes we can't sufficiently express exactly what we want to do in C code, or we can't
do it as optimally as we'd like to. Perhaps the processor we're building for has a special
instruction that we want to use.

In this case we can insert assembly code directly into our C programs.

See [`asm.c`](./asm.c) for an example.

Q1: Can the code in `asm.c` be written in plain C, without assembly instructions?

In general, you want to avoid handwritten assembly code and only use it
when you really need to.

Q2: What are the downsides of using handwritten assembly over normal C code?
