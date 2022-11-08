//
// Created by JakoError on 2021/4/22.
//

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#pragma warning(disable:4996)

/**
 * @discription 
 */
int main() {
    char str[19];
    str[18] = '\0';
    int k = rand();
    for (int i = 0; i < 18; ++i) {
        Sleep(rand()%10*10);
        srand((unsigned)time(NULL)+rand()+k);
        if (rand()%6==1) {
            srand((unsigned)time(NULL)+rand()+k);
            int a = rand()%10;
            str[i] = '0'+a;
        }else{
            srand((unsigned)time(NULL)+rand()+k);
            str[i] = 'A'+rand()%('Z'-'A');
        }
    }
    printf("%s",str);
    return EXIT_SUCCESS;
}