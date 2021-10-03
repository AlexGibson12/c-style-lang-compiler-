# c-style-lang-compiler-
Trying to make a compiler that emits x64 assembly, maybe eventually make an assembler to emit elf files?

Work in Progress compiler experiment. 

Mainly using c syntax but I just assume everything is an integer so there are no type declarations. 

There are examples in a folder but only some of them work at the moment because while statements dont nest correctly

Clone the repository then run ./build to compile the compiler. Then use ./compiler <filename> to compile and execute a file.

Currently just using nasm for assembling after emitting x64 assembly.

Not optimized at all.
