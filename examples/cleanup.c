#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defer.h"

static char *slurp(const char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) return NULL;
    defer { close(fd); };

    char *buf = malloc(4096);
    if (!buf) return NULL;
    defer { free(buf); };

    ssize_t n = read(fd, buf, 4095);
    if (n <= 0) return NULL;
    buf[n] = '\0';

    char *out = strdup(buf);
    return out;
}

int main(void)
{
    char *s = slurp("/etc/hostname");
    if (!s) return 1;
    fputs(s, stdout);
    free(s);
}