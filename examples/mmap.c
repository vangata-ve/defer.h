#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "defer.h"

int main(void)
{
    int fd = open("/etc/hostname", O_RDONLY);
    if (fd < 0) return 1;
    defer { close(fd); };

    off_t sz = lseek(fd, 0, SEEK_END);
    if (sz < 0) return 1;

    void *p = mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) return 1;
    defer { munmap(p, sz); };

    fwrite(p, 1, sz, stdout);

    return 0;
}