#define _DEFAULT_SOURCE
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defer.h"

int main(int argc, char **argv)
{
    int verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
    int deleted = 0;
    char tmpdir[] = "/tmp/myapp-XXXXXX";
    mkdtemp(tmpdir);

    /* ... scratch files written into tmpdir during normal work ... */

    defer {
        int rm_cb(const char *path, const struct stat *sb,
                  int typeflag, struct FTW *ftwbuf)
        {
            if (remove(path) == 0) {
                deleted++;
                if (verbose) printf("removed %s\n", path);
            }
            return 0;
        }
        nftw(tmpdir, rm_cb, 16, FTW_DEPTH | FTW_PHYS);
        if (verbose) printf("cleaned %d files from %s\n", deleted, tmpdir);
    };

    return 0;
}

// #include <stdio.h>
// #include "defer.h"

// int main(void)
// {
//     printf("Hello, World!\n");

//     defer { printf("defer #1\n"); }
//     defer { printf("defer #2\n"); }
//     defer { printf("defer #3\n"); }

//     printf("Goodbye, World!\n");

//     return 0;
// }