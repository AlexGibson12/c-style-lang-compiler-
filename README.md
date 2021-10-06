# c-style-lang-compiler-
Trying to make a compiler that emits x64 assembly, maybe eventually make an assembler to emit elf files?

Work in Progress compiler experiment. 

Mainly using c syntax but I just assume everything is an integer so there are no type declarations. 

There are examples in a folder but only some of them work at the moment because while statements dont nest correctly

Clone the repository then run ./build to compile the compiler. Then use ./compiler filename to compile and execute a file.

Currently just using nasm for assembling after emitting x64 assembly.

Not optimized at all.

Examples:


Prints multiples of three below 100:
```
x = 0;
while(x<100){
        if(x%3 == 0){
                print(x);
        }
        x = x+1;
}
```

Prints the primes below 100: 
```
x = 2;
while(x < 100){
        f = 1;
        y = 2;
        while(y<x){
                if(x%y == 0){
                        f = 0;
                }
                y = y+1;
        
        }
        if(f){
                print(x);
        }
        


        x = x+1;
}


```
Prints the first one hundred fibonacci numbers:
```

x = 1;
y = 1;
num = 0;
while(num<100){
        print(x);
        y = x+y;
        x = y-x;
        num = num+1;
}


```
