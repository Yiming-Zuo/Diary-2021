#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // execl("/bin/ps", "ps", "aux", NULL);  // 指定文件路径
        execlp("ls", "ls", "-h", NULL);  // 从环境变量中找可执行文件
        perror("execlp");  // 如果fork失败，错误信息存于error中
        // 执行成功后不会返回，子进程的内容(代码段、数据段、堆栈等)已经被可执行文件的新内容所取代
        // 执行完子程序退出
    }
    for (int i = 0; i < 3; i++) {
        printf("i = %d\n", i);
    }
    return 0;
}