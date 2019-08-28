#include "header.h"

double MSE(unsigned char** ori, unsigned char** rec)
{
	double sum = 0.0;

	int i, j;
	for (i = 0; i < 512; i++)
	{
		for (j = 0; j < 512; j++)
     		sum += (double)( ((*(*(ori+i)+j)) - ( *(*(rec+i)+j))) * ((*(*(ori+i)+j)) - (*(*(rec+i)+j))) );		
	}
	sum= sum / (512 * 512);
	return sum;

}
void char_freememory(unsigned char** abc, int size)
{
	int i;
	for (i = 0; i < size; i++)
		free(*(abc+i));
	free(abc);
}
void double_freememory(double** abc, int size)
{
	int i;
	for (i = 0; i < size; i++)
		free(*(abc+i));
	free(abc);
}
int roundup(double insert)
{
	double roundup;
	int a;
	roundup = insert - (int)insert; //소수점만남김
	a = roundup >= 0.5 ? (int)insert + 1 : (int)insert; //반올림한거 입력
	return a;
}
int clipping(int a)
{
	if (a > 255)
		a = 255;
	else if (a < 0)
		a = 0;
	else
		a = a;

	return a;
}
unsigned char ** char_makememory(int row, int col)
{
	int i;
	unsigned char** abc=(unsigned char**)malloc(sizeof(unsigned char*) * row);
	for (i = 0; i < row; i++)
		*(abc + i) = (unsigned char*)malloc(sizeof(unsigned char) * col);
	return abc;
}
double ** double_makememory(int row, int col)
{
	int i;
	double** abc = (double**)malloc(sizeof(double*) * row);
	for (i = 0; i < row; i++)
		*(abc+i) = (double*)malloc(sizeof(double) * col);
	return abc;
}
double ** change_double( unsigned char **abc,int row,int col)
{
	int i,j;
	double** a = double_makememory(row, col);
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			*(*(a+i)+j) = (double)(*(*(abc+i)+j));
	}
	return a;
}
unsigned char ** read(unsigned char **abc, FILE *fp, int size)
{
	int i;
	for (i = 0; i < size; i++)
		fread(*(abc + i), sizeof(unsigned char), size, fp);
	return abc;
}
unsigned char ** write(unsigned char **abc, FILE *fp, int size)
{
	int i;
	for (i = 0; i < size; i++)
		fwrite(*(abc + i), sizeof(unsigned char), size, fp);
	return abc;
}
double** colLPF(double **ori, int row, int col, double *lpf) // 500x500 ->400x400 할때 가로방향 로패스필터 
{
	int i, j;
	double **buf = double_makememory(row, col);
	//11탭계수를 사용하였음 lpf[0]~[11]

	for (i = 0; i < row; i++) // 미러링 적용
	{
		for (j = 0; j < col; j++)
		{
			if (j == col - 1)
			{
				*(*(buf + i) + j) =  + *(lpf + 0)*(*(*(ori + i) + j - 5))*2.0 + *(lpf + 1)*(*(*(ori + i) + j - 4))*2.0 
					                 + *(lpf + 2)*(*(*(ori + i) + j - 3))*2.0 + *(lpf + 3)*(*(*(ori + i) + j - 2))*2.0
					                 + *(lpf + 4)*(*(*(ori + i) + j - 1))*2.0
					                 + *(lpf + 5)*(*(*(ori + i) + j));

			}
			else if (j == col - 2)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i) + j - 5)) + *(lpf + 1)*(*(*(ori + i) + j - 4)) 
					                + *(lpf + 2)*(*(*(ori + i) + j - 3)) + *(lpf + 3)*(*(*(ori + i) + j - 2))
					                + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j)) 
					                + *(lpf + 6)*(*(*(ori + i) + j + 1)) 
					                + *(lpf + 7)*(*(*(ori + i) + j)) + *(lpf + 8)*(*(*(ori + i) + j - 1)) //미러링부분
					                + *(lpf + 9)*(*(*(ori + i) + j - 2)) + *(lpf + 10)*(*(*(ori + i) + j - 3));//미러링부분
			}
			else if (j == col - 3)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i) + j - 5)) + *(lpf + 1)*(*(*(ori + i) + j - 4)) 
					                + *(lpf + 2)*(*(*(ori + i) + j - 3)) + *(lpf + 3)*(*(*(ori + i) + j - 2))
					                + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i) + j + 1)) + *(lpf + 7)*(*(*(ori + i) + j + 2))
					                + *(lpf + 8)*(*(*(ori + i) + j + 1)) + *(lpf + 9)*(*(*(ori + i) + j)) + *(lpf + 10)*(*(*(ori + i) + j - 1)); //미러링부분
			}
			else if (j == col - 4)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i) + j - 5)) + *(lpf + 1)*(*(*(ori + i) + j - 4)) 
					                + *(lpf + 2)*(*(*(ori + i) + j - 3)) + *(lpf + 3)*(*(*(ori + i) + j - 2))
					                + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j)) 
					                + *(lpf + 6)*(*(*(ori + i) + j + 1)) + *(lpf + 7)*(*(*(ori + i) + j + 2)) 
					                + *(lpf + 8)*(*(*(ori + i) + j + 3))
					                + *(lpf + 9)*(*(*(ori + i) + j + 2)) + *(lpf + 10)*(*(*(ori + i) + j + 1)); //미러링부분 
			}
			else if (j == col - 5)
			{

				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i) + j - 5)) + *(lpf + 1)*(*(*(ori + i) + j - 4)) 
					                + *(lpf + 2)*(*(*(ori + i) + j - 3)) + *(lpf + 3)*(*(*(ori + i) + j - 2))
					                + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i) + j + 1)) + *(lpf + 7)*(*(*(ori + i) + j + 2))
					                + *(lpf + 8)*(*(*(ori + i) + j + 3)) + *(lpf + 9)*(*(*(ori + i) + j + 4))
					                + *(lpf + 10)*(*(*(ori + i) + j + 3)); //미러링부분
			}
			else if (j == 0)
			{
				*(*(buf + i) + j) = + *(lpf + 5)*(*(*(ori + i) + j)) + *(lpf + 6)*(*(*(ori + i) + j + 1))*2.0
					                + *(lpf + 7)*(*(*(ori + i) + j + 2))*2.0 + *(lpf + 8)*(*(*(ori + i) + j + 3))*2.0 
					                + *(lpf + 9)*(*(*(ori + i) + j + 4))*2.0
					                + *(lpf + 10)*(*(*(ori + i) + j + 5))*2.0; //미러링부분
			}
			else if (j == 1)
			{
				*(*(buf + i) + j) = + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i) + j + 1)) + *(lpf + 7)*(*(*(ori + i) + j + 2)) 
					                + *(lpf + 8)*(*(*(ori + i) + j + 3)) + *(lpf + 9)*(*(*(ori + i) + j + 4)) 
					                + *(lpf + 10)*(*(*(ori + i) + j + 5))
					                + *(lpf + 3)*(*(*(ori + i) + j)) + *(lpf + 2)*(*(*(ori + i) + j + 1))  //미러링부분
					                + *(lpf + 1)*(*(*(ori + i) + j + 2)) + *(lpf + 0)*(*(*(ori + i) + j + 3)); //미러링부분
			}
			else if (j == 2)
			{
				*(*(buf + i) + j) = + *(lpf + 3)*(*(*(ori + i) + j - 2)) + *(lpf + 4)*(*(*(ori + i) + j - 1)) 
					                + *(lpf + 5)*(*(*(ori + i) + j)) + *(lpf + 6)*(*(*(ori + i) + j + 1))
					                + *(lpf + 7)*(*(*(ori + i) + j + 2)) + *(lpf + 8)*(*(*(ori + i) + j + 3)) 
					                + *(lpf + 9)*(*(*(ori + i) + j + 4)) + *(lpf + 10)*(*(*(ori + i) + j + 5))
					                + *(lpf + 2)*(*(*(ori + i) + j - 1)) + *(lpf + 1)*(*(*(ori + i) + j)) + *(lpf + 0)*(*(*(ori + i) + j + 1)); //미러링부분
			}
			else if (j == 3)
			{
				*(*(buf + i) + j) = + *(lpf + 2)*(*(*(ori + i) + j - 3)) + *(lpf + 3)*(*(*(ori + i) + j - 2)) 
					                + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i) + j + 1)) + *(lpf + 7)*(*(*(ori + i) + j + 2)) 
					                + *(lpf + 8)*(*(*(ori + i) + j + 3)) + *(lpf + 9)*(*(*(ori + i) + j + 4)) 
					                + *(lpf + 10)*(*(*(ori + i) + j + 5))
					                + *(lpf + 1)*(*(*(ori + i) + j - 2)) + *(lpf + 0)*(*(*(ori + i) + j - 1)); //미러링부분
			}
			else if (j == 4)
			{
				*(*(buf + i) + j) = + *(lpf + 1)*(*(*(ori + i) + j - 4)) + *(lpf + 2)*(*(*(ori + i) + j - 3))
					                + *(lpf + 3)*(*(*(ori + i) + j - 2)) + *(lpf + 4)*(*(*(ori + i) + j - 1))
					                + *(lpf + 5)*(*(*(ori + i) + j))     + *(lpf + 6)*(*(*(ori + i) + j + 1)) 
					                + *(lpf + 7)*(*(*(ori + i) + j + 2)) + *(lpf + 8)*(*(*(ori + i) + j + 3)) 
					                + *(lpf + 9)*(*(*(ori + i) + j + 4)) + *(lpf + 10)*(*(*(ori + i) + j + 5))
					                + *(lpf + 0)*(*(*(ori + i) + j - 3)); //미러링부분
			}

			else
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i) + j - 5)) + *(lpf + 1)*(*(*(ori + i) + j - 4)) 
					                + *(lpf + 2)*(*(*(ori + i) + j - 3)) + *(lpf + 3)*(*(*(ori + i) + j - 2))
					                + *(lpf + 4)*(*(*(ori + i) + j - 1)) + *(lpf + 5)*(*(*(ori + i) + j))
				                 	+ *(lpf + 6)*(*(*(ori + i) + j + 1)) + *(lpf + 7)*(*(*(ori + i) + j + 2)) 
					                + *(lpf + 8)*(*(*(ori + i) + j + 3)) + *(lpf + 9)*(*(*(ori + i) + j + 4)) 
					                + *(lpf + 10)*(*(*(ori + i) + j + 5));
			}
		}
	}

	return buf;
}
double** rowLPF(double **ori, int row, int col, double *lpf) //세로방향 로패스 필터
{
	int i, j;
	double **buf = double_makememory(row, col);

	for (j = 0; j < col; j++) // 미러링 적용
	{
		for (i = 0; i < row; i++)
		{
			if (i == row - 1)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i - 5) + j))*2.0 + *(lpf + 1)*(*(*(ori + i - 4) + j))*2.0 
					                + *(lpf + 2)*(*(*(ori + i - 3) + j))*2.0 + *(lpf + 3)*(*(*(ori + i - 2) + j))*2.0 
					                + *(lpf + 4)*(*(*(ori + i - 1) + j))*2.0
					                + *(lpf + 5)*(*(*(ori + i) + j));

			}
			else if (i == row - 2)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i - 5) + j)) + *(lpf + 1)*(*(*(ori + i - 4) + j)) 
					                + *(lpf + 2)*(*(*(ori + i - 3) + j)) + *(lpf + 3)*(*(*(ori + i - 2) + j))
					                + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j)) 
					                + *(lpf + 6)*(*(*(ori + i + 1) + j))
					                + *(lpf + 7)*(*(*(ori + i) + j)) + *(lpf + 8)*(*(*(ori + i - 1) + j)) //미러링부분
					                + *(lpf + 9)*(*(*(ori + i - 2) + j)) + *(lpf + 10)*(*(*(ori + i - 3) + j));//미러링부분
			}
			else if (i == row - 3)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i - 5) + j)) + *(lpf + 1)*(*(*(ori + i - 4) + j)) 
					                + *(lpf + 2)*(*(*(ori + i - 3) + j)) + *(lpf + 3)*(*(*(ori + i - 2) + j))
					                + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j)) 
					                + *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j))
					                + *(lpf + 8)*(*(*(ori + i + 1) + j)) + *(lpf + 9)*(*(*(ori + i) + j)) + *(lpf + 10)*(*(*(ori + i - 1) + j)); //미러링부분
			}
			else if (i == row - 4)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i - 5) + j)) + *(lpf + 1)*(*(*(ori + i - 4) + j)) 
					                + *(lpf + 2)*(*(*(ori + i - 3) + j)) + *(lpf + 3)*(*(*(ori + i - 2) + j))
					                + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j)) 
					                + *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j))
					                + *(lpf + 8)*(*(*(ori + i + 3) + j))
					                + *(lpf + 9)*(*(*(ori + i + 2) + j)) + *(lpf + 10)*(*(*(ori + i + 1) + j)); //미러링부분
			}
			else if (i == row - 5)
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i - 5) + j)) + *(lpf + 1)*(*(*(ori + i - 4) + j)) 
					                + *(lpf + 2)*(*(*(ori + i - 3) + j)) + *(lpf + 3)*(*(*(ori + i - 2) + j))
					                + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j)) 
					                + *(lpf + 8)*(*(*(ori + i + 3) + j)) + *(lpf + 9)*(*(*(ori + i + 4) + j))
					                + *(lpf + 10)*(*(*(ori + i + 3) + j)); //미러링부분
			}
			else if (i == 0)
			{
				*(*(buf + i) + j) = + *(lpf + 5)*(*(*(ori + i) + j)) + *(lpf + 6)*(*(*(ori + i + 1) + j))*2.0
					                + *(lpf + 7)*(*(*(ori + i + 2) + j))*2.0 + *(lpf + 8)*(*(*(ori + i + 3) + j))*2.0 
					                + *(lpf + 9)*(*(*(ori + i + 4) + j))*2.0
					                + *(lpf + 10)*(*(*(ori + i + 5) + j))*2.0;
			}
			else if (i == 1)
			{
				*(*(buf + i) + j) = + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j)) 
					                + *(lpf + 8)*(*(*(ori + i + 3) + j)) + *(lpf + 9)*(*(*(ori + i + 4) + j))
					                + *(lpf + 10)*(*(*(ori + i + 5) + j))
					                + *(lpf + 3)*(*(*(ori + i) + j)) + *(lpf + 2)*(*(*(ori + i + 1) + j)); //미러링부분
					                + *(lpf + 1)*(*(*(ori + i + 2) + j)) + *(lpf + 0)*(*(*(ori + i + 3) + j)); //미러링부분
			}
			else if (i == 2)
			{
				*(*(buf + i) + j) = + *(lpf + 3)*(*(*(ori + i - 2) + j)) + *(lpf + 4)*(*(*(ori + i - 1) + j)) 
					                + *(lpf + 5)*(*(*(ori + i) + j))  	+ *(lpf + 6)*(*(*(ori + i + 1) + j)) 
					                + *(lpf + 7)*(*(*(ori + i + 2) + j)) + *(lpf + 8)*(*(*(ori + i + 3) + j)) 
					                + *(lpf + 9)*(*(*(ori + i + 4) + j)) + *(lpf + 10)*(*(*(ori + i + 5) + j))
					                + *(lpf + 2)*(*(*(ori + i - 1) + j)) + *(lpf + 1)*(*(*(ori + i) + j)) + *(lpf + 0)*(*(*(ori + i + 1) + j)); //미러링부분
			}
			else if (i == 3)
			{
				*(*(buf + i) + j) = + *(lpf + 2)*(*(*(ori + i - 3) + j)) + *(lpf + 3)*(*(*(ori + i - 2) + j)) 
					                + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j))
				                 	+ *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j)) 
					                + *(lpf + 8)*(*(*(ori + i + 3) + j)) + *(lpf + 9)*(*(*(ori + i + 4) + j))
					                + *(lpf + 10)*(*(*(ori + i + 5) + j))
					                + *(lpf + 1)*(*(*(ori + i - 2) + j)) + *(lpf + 0)*(*(*(ori + i - 1) + j)); //미러링부분
			}
			else if (i == 4)
			{
				*(*(buf + i) + j) = + *(lpf + 1)*(*(*(ori + i - 4) + j)) + *(lpf + 2)*(*(*(ori + i - 3) + j)) 
					                + *(lpf + 3)*(*(*(ori + i - 2) + j)) + *(lpf + 4)*(*(*(ori + i - 1) + j))
					                + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j)) 
					                + *(lpf + 8)*(*(*(ori + i + 3) + j)) + *(lpf + 9)*(*(*(ori + i + 4) + j)) 
					                + *(lpf + 10)*(*(*(ori + i + 5) + j))
					                + *(lpf + 0)*(*(*(ori + i - 3) + j));//미러링부분
			}

			else
			{
				*(*(buf + i) + j) = + *(lpf + 0)*(*(*(ori + i - 5) + j)) + *(lpf + 1)*(*(*(ori + i - 4) + j)) 
					                + *(lpf + 2)*(*(*(ori + i - 3) + j)) + *(lpf + 3)*(*(*(ori + i - 2) + j)) 
					                + *(lpf + 4)*(*(*(ori + i - 1) + j)) + *(lpf + 5)*(*(*(ori + i) + j))
					                + *(lpf + 6)*(*(*(ori + i + 1) + j)) + *(lpf + 7)*(*(*(ori + i + 2) + j)) 
					                + *(lpf + 8)*(*(*(ori + i + 3) + j)) + *(lpf + 9)*(*(*(ori + i + 4) + j)) 
					                + *(lpf + 10)*(*(*(ori + i + 5) + j));
			}

		}
	}	
	return buf;

}
