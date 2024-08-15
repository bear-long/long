#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

float *func1(float a, float b) {
    int i;
    float *result;
    result = (float *)malloc(sizeof(float) * 2);
    for (i = 0; i < 1000000000; ++i) {
        result[0] = a + b;
        result[1] = a - b;
    }
    return result;
}

float *func2(float a, float b) {
    int i;
    float *result;
    result = (float *)malloc(sizeof(float) * 2);
    for (i = 0; i < 1000000000; ++i) {
        result[0] = a * b;
        result[1] = a / b;
    }
    return result;
}

typedef struct {
    float a;
    float b;
} Args;

void *thread_func1(void *arg) {
    Args *args = (Args *)arg;
    return func1(args->a, args->b);
}

void *thread_func2(void *arg) {
    Args *args = (Args *)arg;
    return func1(args->a, args->b);
}

int main() {
    float a = 1.14, b = 5.14, *result1, *result2, during;
    Args ab;
    ab.a = a;
    ab.b = b;
    result1 = (float *)malloc(sizeof(float) * 2);
    result2 = (float *)malloc(sizeof(float) * 2);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    void *r1, *r2;
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_func1, &ab);
    pthread_create(&tid2, NULL, thread_func2, &ab);
    pthread_join(tid1, &r1);
    pthread_join(tid2, &r2);
    result1 = (float *)r1;
    result2 = (float *)r2;
    gettimeofday(&end, NULL);
    during = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("result1[0] = %f\nresult1[1] = %f\n", result1[0], result1[1]);
    printf("result2[0] = %f\nresult2[1] = %f\n", result2[0], result2[1]);
    printf("during time = %f s\n", during);
    free(result1);
    free(result2);
    return 0;
}
//copy 大佬的代码：https://fuuzen.github.io/cs/parallel-programing/pthread/
