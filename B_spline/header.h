#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>

//512*512 ->400*400

static double lpf1[11] = { -0.0015, - 0.0051 ,   0.0373, - 0.1067 ,   0.1846 ,   0.7829  ,  0.1846, - 0.1067 ,   0.0373 ,- 0.0051 ,- 0.0015 }; //0.390625
//static double lpf1[11] = { 0.0051  , -0.0126  ,  0.0340 ,  -0.0635 ,   0.0893 ,   0.8956  ,  0.0893  , -0.0635   , 0.0340  , -0.0126   , 0.0051 };//0.45
//static double lpf1[11] = { -0.0051  ,  0.0079  ,  0.0131, -0.1038 ,   0.2361 ,   0.7036  ,  0.2361, -0.1038 ,   0.0131  ,  0.0079, -0.0051 }; //0.35
static double lpf2[11] = { 0.0014 , 0.0114 ,-0.0302, -0.0534  ,  0.2802   , 0.5810 ,   0.2802 ,-0.0534 ,-0.0302 ,   0.0114  ,  0.0014 };


//512*512->200*200
//static double lpf1[11] = { -0.0007 ,-0.0130, -0.0216  ,  0.0686  ,  0.2723   , 0.3891   , 0.2723 ,   0.0686, -0.0216 ,-0.0130, -0.0007 }; //0.1953125 이상적인컷오브
//static double lpf1[11] = { -0.0052 ,-0.0080 ,   0.0134  ,  0.1057 ,   0.2405 ,   0.3072 ,  0.2405  ,  0.1057 ,   0.0134 ,-0.0080, -0.0052 }; //0.15 
//static double lpf1[11] = { 0.0051 ,- 0.0000 ,- 0.0419 ,   0.0000 ,   0.2885  ,  0.4968 ,   0.2885  ,  0.0000 ,- 0.0419, - 0.0000  ,  0.0051 }; //0.25 


double MSE(unsigned char** ori, unsigned char** rec); //MSE값 구하는 함수
void char_freememory(unsigned char** buf, int size); //unsigned char형 동적할당 해제
void double_freememory(double** abc, int size); // double형 동적할당 해제
int roundup(double insert); //반올림 함수
int clipping(int a); //클리핑 함수
unsigned char ** read(unsigned char **abc, FILE *fp, int size); //fread함수
unsigned char ** write(unsigned char **abc, FILE *fp, int size); //fwrite 함수
unsigned char ** char_makememory(int row, int col); //unsigned char형 2차원 동적배열을 만드는 함수
double ** double_makememory(int row, int col); //double 형 2차원동적배열 만드는함수
double ** change_double(unsigned char **abc, int row, int col); //unsigned char 2차원동적배열을 double 형으로 바꿔주는 함수
double** colLPF(double **ori, int row, int col,double*lpf); // 열 로패스필터(가로)
double** rowLPF(double **ori, int row, int col,double*lpf); // 행 로패스필터(세로)



unsigned char** B_spline_col(double**ori, int oripixel, int newpixel);
unsigned char** B_spline_row(double **ori, int oripixel, int newpixel);
double** col_Pre_emphasis(double **ori, int row, int col);
double** row_Pre_emphasis(double **ori, int row, int col);
void test1(double **ori_buf, unsigned char**original);
void test2(double **ori_buf, unsigned char**original);
void test3(double **ori_buf, unsigned char**original);
void test4(double **ori_buf);
void test5(double **ori_buf);
void test6(double **ori_buf);

#endif
