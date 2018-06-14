Underload
=========

(This document was converted from the public-domain
[HTML Underload specification][] in [The Esoteric File Archive][].)

Basics
------

Underload is a stack-based programming language that works along similar
lines to Muriel. Although not technically speaking a functional
language, its evaluation operator `^` (which is the only form of flow
control) makes programming in it functional in practice.

Reserved characters
-------------------

The bracket and angle bracket characters []<> are reserved; if these are
to appear anywhere in the program, they must be quoted by placing "
before them. This also applies to the " character itself. Other
characters must _not_ be quoted with " (in particular, this means that
Underload programs cannot output strings containing unmatched
parentheses). Parentheses are moderately reserved, in that any Underload
program must have matched parentheses to be legal.

Commands
--------

-   `~` Swap the top two elements of the stack.
-   `:` Duplicate the top element of the stack.
-   `!` Discard the top element of the stack.
-   `*` Concatenate the top element of the stack to the end of the second
    element of the stack.
-   `(` Push everything between the `(` and the matching `)` on top of
    the stack.
-   `)` Closes a `(` command.
-   `a` Encloses the top element of the stack in a pair of parentheses.
-   `^` When the `^` command is called, it includes the top element of the
    stack into the program, immediately after the `^` command, ready to be
    run next.
-   `S` Output the top element of the stack, popping it.

Exceptional circumstances
-------------------------

Pretty much anything whose behaviour isn't specifically given here (for
instance, running `*` on an empty stack) is an error.

Example programs
----------------

### Hello, world!

    (Hello, world!)S

### Fibonacci sequence

    (()(*))(~:^:S*a~^a~!~*~:(/)S^):^

### Infinite loop

    (:^):^

### Quine

    (:aSS):aSS

(The null program is also a quine. This program is more stack-based than
functional.)

[HTML Underload specification]: https://cdn.rawgit.com/graue/esofiles/7ca16941/underload/underload.html
[The Esoteric File Archive]: https://esolangs.org/wiki/The_Esoteric_File_Archive
