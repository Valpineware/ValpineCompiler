# Valpine Compiler

The Valpine programming language is currently in the early stages of development. It is planned to be a general-purpose language like C++ that encourages cleaner and safer designs without compromising performance. The language will be mostly (if not entirely) compatible with C++ codebases which will make the transition process easy.

Initially, the Valpine Compiler will mock Valpine code directly into C++ and then compile as C++ using whatever compiler is desired (G++, MSVC, etc.). If C++ compatability is not desired, future versions may simply mock to C and then compile from there for potentially increased compile times.
