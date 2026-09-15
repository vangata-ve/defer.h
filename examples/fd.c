#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "defer.h"

int main(void)
{
    int fd = open("/etc/hostname", O_RDONLY);
    if (fd < 0) { perror("open"); return 1; }
    defer { close(fd); };

    char buf[256];
    ssize_t n = read(fd, buf, sizeof buf - 1);
    if (n < 0) { perror("read"); return 1; }
    buf[n] = '\0';

    fputs(buf, stdout);
    return 0;
}