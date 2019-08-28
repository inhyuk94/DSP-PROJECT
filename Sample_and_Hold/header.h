#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>

static double lpf1[11] = { -0.0015, -0.0051 ,   0.0373, -0.1067 ,   0.1846 ,   0.7829  ,  0.1846, -0.1067 ,   0.0373 ,-0.0051 ,-0.0015 }; //0.390625
//static double lpf1[11] = { 0.0051  , -0.0126  ,  0.0340 ,  -0.0635 ,   0.0893 ,   0.8956  ,  0.0893  , -0.0635   , 0.0340  , -0.0126   , 0.0051 };//0.45
//static double lpf1[11] = { -0.0051  ,  0.0079  ,  0.0131, -0.1038 ,   0.2361 ,   0.7036  ,  0.2361, -0.1038 ,   0.0131  ,  0.0079, -0.0051 }; //0.35
static double lpf2[11] = { 0.0014 , 0.0114 ,-0.0302, -0.0534  ,  0.2802   , 0.5810 ,   0.2802 ,-0.0534 ,-0.0302 ,   0.0114  ,  0.0014 };

double MSE(unsigned char** ori, unsigned char** rec); //MSE�� ���ϴ� �Լ�
void char_freememory(unsigned char** buf, int size); //unsigned char�� �����Ҵ� ����
void double_freememory(double** abc, int size); // double�� �����Ҵ� ����
int roundup(double insert); //�ݿø� �Լ�
int clipping(int a); //Ŭ���� �Լ�
unsigned char ** read(unsigned char **abc, FILE *fp, int size); //fread�Լ�
unsigned char ** write(unsigned char **abc, FILE *fp, int size); //fwrite �Լ�
unsigned char ** char_makememory(int row, int col); //unsigned char�� 2���� �����迭�� ����� �Լ�
double ** double_makememory(int row, int col); //double �� 2���������迭 ������Լ�
double ** change_double(unsigned char **abc, int row, int col); //unsigned char 2���������迭�� double ������ �ٲ��ִ� �Լ�
double** rowLPF(double **ori, int row, int col,double*lpf);
double** colLPF(double **ori, int row, int col,double*lpf);

unsigned char** samplehold_col(double**ori, int oripixel, int newpixel); //���� samplehold ����
unsigned char** samplehold_row(double **ori, int oripixel, int newpixel); //���� samplehold ����
void test1(double **ori_buf, unsigned char**original);
void test2(double **ori_buf, unsigned char**original);
void test3(double **ori_buf, unsigned char**original);
void test4(double **ori_buf);
void test5(double **ori_buf);
void test6(double **ori_buf);

#endif
