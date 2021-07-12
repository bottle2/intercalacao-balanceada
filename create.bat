gcc -c fl-gen.c -o fl-gen.o
gcc fl-gen.o -o write.exe
.\write.exe teste 10000

gcc -c fl-rd.c -o fl-rd.o
gcc fl-rd.o -o read.exe
.\read.exe teste 