#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // 创建内存映射区
    int fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    int size = lseek(fd, 0, SEEK_END);
    void *ptr  = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }
    // 写数据
    strcpy((void *)ptr, "hello, world!\n");
    // 关闭内存映射区
    munmap(ptr, size);

    return 0;
}