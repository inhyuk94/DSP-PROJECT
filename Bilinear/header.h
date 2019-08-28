#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>


static double lpf1[11] = { -0.0015, -0.0051 ,   0.0373, -0.1067 ,   0.1846 ,   0.7829  ,  0.1846, -0.1067 ,   0.0373 ,-0.0051 ,-0.0015 }; //cut of frequency 0.390625
//static double lpf1[11] = { 0.0051  , -0.0126  ,  0.0340 ,  -0.0635 ,   0.0893 ,   0.8956  ,  0.0893  , -0.0635   , 0.0340  , -0.0126   , 0.0051 };//0.45
//static double lpf1[11] = { -0.0051  ,  0.0079  ,  0.0131, -0.1038 ,   0.2361 ,   0.7036  ,  0.2361, -0.1038 ,   0.0131  ,  0.0079, -0.0051 }; //0.35
static double lpf2[11] = { 0.0014 , 0.0114 ,-0.0302, -0.0534  ,  0.2802   , 0.5810 ,   0.2802 ,-0.0534 ,-0.0302 ,   0.0114  ,  0.0014 };


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
double** colLPF(double **ori, int row, int col,double*lpf);
double** rowLPF(double **ori, int row, int col,double*lpf);


unsigned char** Bilinear_col(double**ori, int oripixel, int newpixel); 
unsigned char** Bilinear_row(double **ori, int oripixel, int newpixel);
void test1(double **ori_buf, unsigned char**original);
void test2(double **ori_buf, unsigned char**original);
void test3(double **ori_buf, unsigned char**original);
void test4(double **ori_buf);
void test5(double **ori_buf);
void test6(double **ori_buf);

#endif
