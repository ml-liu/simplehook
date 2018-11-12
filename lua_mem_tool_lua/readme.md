* 1、cd /data/app/server/bin
* 2、执行命令 ./luamem.sh Server > hook.lua 生成带地址的hook配置文件
* 3、LD_PRELOAD=./liblua_mem_tool.so ./Server 启动服务器
* 4、等到服务器启动完成后可抓取lua内存快照，使用命令 echo "dump" | nc -U /tmp/luameme.sock生成当前时间的一份快照
* 5、快照文件保存在/tmp/目录，每份快照有两个文件，分别为stack.pid.1.txt lualog.pid.1.txt，其中1表明第几次，如果执行dump命令多次，则生成多份快照
* 6、cd /tmp/目录，使用命令 python luamem.py pid.1 可分析第一份快照，执行完成后会生成一个html文件framegraph.pid.1.html
* 7、使用python diffadd.py pid.1 pid.2命令可以对比两份快照，其内容为pid.1到pid.2两份快照生成期间新增的lua内存，内容保存在diffadd.pid.1-pid.2.html中