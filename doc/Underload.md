Underload
=========

(This document was converted from the public-domain HTML Underload
specification in The Esoteric File Archive.)

Basics
------

Underload is a stack-based programming language that works along similar
lines to Muriel. Although not technically speaking a functional
language, its evaluation operator ^ (which is the only form of flow
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

-   ~ Swap the top two elements of the stack.
-   : Duplicate the top element of the stack.
-   ! Discard the top element of the stack.
-   * Concatenate the top element of the stack to the end of the second
    element of the stack.
-   ( Push everything between the ( and the matching ) on top of
    the stack.
-   ) Closes a ( command.
-   a Encloses the top element of the stack in a pair of parentheses.
-   ^ When the ^ command is called, it includes the top element of the
    stack into the program, immediately after the ^ command, ready to be
    run next.
-   S Output the top element of the stack, popping it.

Exceptional circumstances
-------------------------

Pretty much anything whose behaviour isn't specifically given here (for
instance, running * on an empty stack) is an error.

Unlambda to Underload
---------------------

The s, k, and i characters in Unlambda can all be translated directly
into Underload. Also, the ` character can be translated, but it has to
be moved to a postfix rather than prefix position, and .x can be
translated for most values of _x_.

-   s translates to ((:)~*(~)*a(~*(~^)*)):
    sx`y`z` = xz`yz`` (postfix notation)
    sx`y`   = (:x~y~^)
    sx`     = ((:x~)~*(~^)*)
    s       = ((:)~*(~)*a(~*(~^)*)*)
-   k translates to (a(!)~*)
-   i translates to ()
-   ` translates to ~^
-   .x translates to ((x)S)

These translations prove that Underload is Turing-complete, because it
can be compiled into from the Turing-complete `sk Unlambda.

Example programs
----------------

### Hello, world!

    (Hello, world!)S

### Fibonacci sequence

    (()(*))(~:^:S*a~^a~!~*~:(/)S^):^

(An ski`. Unlambda version is
 ```s``s``sii`ki`k.*``s``s`ks``s`k`s`ks``s``s`ks``s`k`s`k./``s`k`sikk`k``s`ksk,
which can also be loaded up in the interpreter below by clicking on it;
you can automatically convert it to Underload if you wish to run it.)

### Infinite loop

    (:^):^

(This is exactly equivalent to the ski`. Unlambda program  ```sii``sii;
if the Unlambda program is converted to Underload using the compiler
below and run for a while, it eventually ends up in the same state as
the previous Underload program (the only difference being ~~, which has
no effect, in the code derived from the Unlambda).

### Quine

    (:aSS):aSS

(The null program is also a quine. This program is more stack-based than
functional.)
