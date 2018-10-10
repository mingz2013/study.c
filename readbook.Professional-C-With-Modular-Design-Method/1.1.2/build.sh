gcc -c src/param.c -o obj/param.o
gcc -c -Iinc src/test_main.c -o obj/test_main.o
gcc obj/param.o obj/test_main.o -o bin/test_main
bin/test_main
echo $? # 用于检测最近一个执行操作的返回。
bin/test_main 1 2
echo $?
bin/test_main 1 2 3
echo $?
gcc -Iinc src/test_main.c -E -P # 查看预编译代码
