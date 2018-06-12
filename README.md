stringie
========

This is the distribution for "stringie", an implementation of [Underload][] in
ANSI C.

[Underload]: http://esolangs.org/wiki/Underload

History
-------

Seeing that there was no _non_-pathological implementation of ais523's
beautiful Underload language in C, I undertook that project one evening.
(In the company of a bottle of really fine wine.  Why, it cost almost twelve
dollars.)  The result is one of the most pedantic and boring Underload
interpreters known to man.  Perhaps the most interesting property of it is its
name, "stringie", which was an accident.

Building
--------

    (cd src && make)

You can also pass `ANSI=yes` to `make` to have the C compiler treat the source
code as ANSI C, and this will work, because the source code is ANSI C.

It can also be build using DICE C under AmigaDOS 1.3; see the file
[build.seq](build.seq) for details.

Usage
-----

    ./bin/stringie '(Hello, world!)S'

From this we can see that the Underload program to be interpreted is passed
directly in the first command-line argument to the executable.

However, there is also a form by which the Underload program can be read from
a file:

    ./bin/stringie from eg/hello.ul

Included materials
------------------

This distribution also contains a description of the Underload language
in the `doc` directory, and a collection of example programs in the `eg`
directory.  These were taken from public-domain sources.

License
-------

The contents of this repository are in the public domain.  See the file
[UNLICENSE](UNLICENSE) for more information.

Acknowledgements
----------------

Thanks to [stasoid](https://github.com/stasoid) for finding, and describing a
fix for, [a heap-corrupting bug](https://github.com/catseye/Dipple/issues/2).
