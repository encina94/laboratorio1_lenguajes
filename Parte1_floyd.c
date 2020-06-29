#define INF 99999999
#define nodos 16
#include <stdlib.h>
#include <stdio.h>

int main(){

printf("\nCreando la matriz");

    int matriz[nodos] [nodos] = { {0, 74, INF, INF, INF, INF, INF, INF,INF, 202, INF, INF, INF, INF, INF, 172},

                                        {74, 0, 108, 206, INF, INF, INF, INF, INF, 302, INF, 255, INF, INF, INF, 96},

                                        {INF, 108, 0, 103, INF, INF, INF, INF, INF, 219, INF, INF, 283, 322, INF, 76},

                                        {INF, 206, 103, 0, 51, 137, INF, INF,INF, INF, INF, INF, 260, 224, INF, 144},

                                        {INF, INF, INF, 51, 0, 88, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},

                                        {INF, INF, INF, 137, 88, 0, 50, 108, INF, INF, INF, INF, INF, 85, 55, 318},

                                        {INF, INF, INF, INF, INF, 50, 0, 74, INF, INF, INF, INF, INF, INF, 103, INF},

                                        {INF, INF, INF, INF, INF, 108, 74, 0, 51, INF, INF, INF, INF, INF, 98, 377},

                                        {INF, INF, INF, INF, INF, INF, INF, 51, 0, INF, INF, INF, INF, INF, INF, INF},

                                        {202, 203, 219, INF, INF, INF, INF, INF, INF, 0, 30, INF, INF, 195, 39, 155},

                                        {INF, INF, INF, INF, INF, INF, INF, INF, INF, 30, 0, 78, INF, INF, INF, INF},

                                        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 78, 0, 53, INF, INF, 167},

                                        {INF, INF, 283, 260, INF, INF, INF, INF, INF, INF, INF, 53, 0, 42, INF, 215},

                                        {INF, INF, 322, 224, INF, 85, INF, INF, INF, 195, INF, INF, 42, 0, 39, INF},

                                        {INF, INF, INF, INF, INF, 55, 103, 98, INF, 39, INF, INF, INF, 39, 0, INF},

                                        {172, 96, 76, 144, INF, 318, INF, 377, INF, 155, INF, 167, 215, INF, INF, 0}

    };
}
