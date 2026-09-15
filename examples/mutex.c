#include <pthread.h>
#include <stdio.h>
#include "defer.h"

static pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
static int counter;

static void bump(int n)
{
    pthread_mutex_lock(&mu);
    defer { pthread_mutex_unlock(&mu); };

    for (int i = 0; i < n; i++)
        counter++;
}

int main(void)
{
    pthread_t a, b;
    pthread_create(&a, NULL, (void*)bump, (void*)1000);
    pthread_create(&b, NULL, (void*)bump, (void*)1000);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    printf("%d\n", counter);
}