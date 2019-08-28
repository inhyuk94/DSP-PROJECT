#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <stdlib.h>

//7�ǰ��
//static double lpf1[7] = {+0.0074 ,- 0.0479 ,+ 0.1539 ,+ 0.7732 ,+ 0.1539 ,- 0.0479 ,+ 0.0074 };
//static double lpf2[7] = { 0.0074 ,-0.0479 ,+0.1539 ,+0.7732 ,+0.1539 ,-0.0479 ,+0.0074 };

//9�ǰ��
//static double lpf1[9] = { -0.0024, +0.0201, -0.0845, +0.1752, +0.7833, +0.1752  -0.0845, +0.0201, -0.0024 }; //512*512->400*400 �ҋ� LPF9�� ���
//static double lpf2[9] = { +0.0054, -0.0162, -0.0420, +0.2641, +0.5773, +0.2641, -0.0420, -0.0162, +0.0054 }; //512*512->298*298 �Ҷ� LPF9�� ���

//11�ǰ��
static double lpf1[11] = { -0.0015, -0.0051 ,   0.0373, -0.1067 ,   0.1846 ,   0.7829  ,  0.1846, -0.1067 ,   0.0373 ,-0.0051 ,-0.0015 }; //cut of frequency 0.390625
//static double lpf1[11] = { 0.0051  , -0.0126  ,  0.0340 ,  -0.0635 ,   0.0893 ,   0.8956  ,  0.0893  , -0.0635   , 0.0340  , -0.0126   , 0.0051 };//0.45
//static double lpf1[11] = { -0.0051  ,  0.0079  ,  0.0131, -0.1038 ,   0.2361 ,   0.7036  ,  0.2361, -0.1038 ,   0.0131  ,  0.0079, -0.0051 }; //0.35
static double lpf2[11] = { 0.0014 , 0.0114 ,-0.0302, -0.0534  ,  0.2802   , 0.5810 ,   0.2802 ,-0.0534 ,-0.0302 ,   0.0114  ,  0.0014 };

//512*512->200*200
//static double lpf1[11] = { -0.0007 ,- 0.0130, - 0.0216  ,  0.0686  ,  0.2723   , 0.3891   , 0.2723 ,   0.0686, - 0.0216 ,- 0.0130, - 0.0007 }; //0.1953125 �̻������ƿ���
//static double lpf1[11] = { -0.0052 ,- 0.0080 ,   0.0134  ,  0.1057 ,   0.2405 ,   0.3072 ,  0.2405  ,  0.1057 ,   0.0134 ,- 0.0080, - 0.0052 }; //0.15
//static double lpf1[11] = { 0.0051 ,-0.0000 ,-0.0419 ,   0.0000 ,   0.2885  ,  0.4968 ,   0.2885  ,  0.0000 ,-0.0419, -0.0000  ,  0.0051 }; //0.25 

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
double** colLPF(double **ori, int row, int col,double*lpf); //�� ���н�����
double** rowLPF(double **ori, int row, int col,double*lpf); //�� ���н�����

unsigned char** Cubic_Convolution_col(double**ori, int oripixel, int newpixel); 
unsigned char** Cubic_Convolution_row(double **ori, int oripixel, int newpixel);
void test1(double **ori_buf, unsigned char**original);
void test2(double **ori_buf, unsigned char**original);
void test3(double **ori_buf, unsigned char**original);
void test4(double **ori_buf);
void test5(double **ori_buf);
void test6(double **ori_buf);

#endif
