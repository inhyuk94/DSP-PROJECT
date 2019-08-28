#include "header.h"
unsigned char** B_spline_col(double**ori, int oripixel, int newpixel)
{

	int i, j; double  t;

	double **newbuf = double_makememory(oripixel, newpixel);
	unsigned char **output = char_makememory(oripixel, newpixel);

	double ns = (double)(oripixel - 1) / (newpixel - 1);

	for (i = 0; i < oripixel; i++) //가로 scaling
	{
		for (j = 0; j < newpixel; j++)
		{

			t = ns*j - (int)(ns*j);

			if ((int)(ns*j) == oripixel - 1)
			{
				newbuf[i][j] = ((2.0 / 3.0) + 0.5*t*t*t - t*t)*(ori[i][(int)(ns*j)])
					         + ((1.0/6.0)*(1 - t)*(1 - t)*(1 - t)) * (ori[i][(int)(ns*j) - 1])
					         + ((2.0 / 3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*(ori[i][(int)(ns*j) - 1])
					         + ((1.0 / 6.0)*t*t*t) * (ori[i][(int)(ns*j) - 2]);
			}
			else if ((int)(ns*j) == oripixel - 2)
			{
				newbuf[i][j] = ((2.0 / 3.0) + 0.5*t*t*t - t*t)*(ori[i][(int)(ns*j)])
					         + ((1.0 / 6.0)*(1 - t)*(1 - t)*(1 - t)) * (ori[i][(int)(ns*j) - 1])
					         + ((2.0 / 3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*(ori[i][(int)(ns*j) + 1])
					         + ((1.0 / 6.0)*t*t*t) * (ori[i][(int)(ns*j)]);
			}
			else if ((int)(ns*j) == 0)
			{
				newbuf[i][j] = ((2.0 / 3.0) + 0.5*t*t*t - t*t)*(ori[i][(int)(ns*j)])
					         + ((2.0 / 3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*(ori[i][(int)(ns*j) + 1])
					         + ((1.0 / 6.0)*(1 - t)*(1 - t)*(1 - t)) * (ori[i][(int)(ns*j) + 1])
					         + ((1.0 / 6.0)*t*t*t) * (ori[i][(int)(ns*j) + 2]);
			}
			else
			{
				newbuf[i][j] = ((2.0/3.0)+0.5*t*t*t-t*t)*(ori[i][(int)(ns*j)])
					         + ((1.0/6.0)*(1-t)*(1-t)*(1-t)) * (ori[i][(int)(ns*j) - 1])
					         + ((2.0/3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*(ori[i][(int)(ns*j) + 1])
					         + ((1.0/6.0)*t*t*t) * (ori[i][(int)(ns*j) + 2]);
			}

			output[i][j] = clipping(roundup(newbuf[i][j])); //클리핑->반올림한후 저장
		}
	}

	return output;

}
unsigned char** B_spline_row(double**ori, int oripixel, int newpixel)
{
	int i, j; double  t;

	double **newbuf = double_makememory(newpixel, newpixel);
	unsigned char **output = char_makememory(newpixel, newpixel);

	double ns = (double)(oripixel - 1) / (newpixel - 1);
	
	for (j = 0; j < newpixel; j++) //세로 scaling
	{
		for (i = 0; i < newpixel; i++)
		{
			t = ns*i - (int)(ns*i);


			if ((int)(ns*i) == oripixel - 1)
			{
				newbuf[i][j] = ((2.0/3.0) + 0.5*t*t*t - t*t)*ori[(int)(ns*i)][j]
					         + ((1.0/6.0)*(1 - t)*(1 - t)*(1 - t))  * ori[(int)(ns*i) - 1][j]
					         + ((2.0/3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*ori[(int)(ns*i) - 1][j]
				             + ((1.0 / 6.0)*t*t*t)  * (ori[(int)(ns*i) - 2][j]);
			}
			else if ((int)(ns*i) == oripixel - 2)
			{
				newbuf[i][j] = ((2.0/3.0) + 0.5*t*t*t - t*t)*ori[(int)(ns*i)][j]
					         + ((1.0/6.0)*(1 - t)*(1 - t)*(1 - t)) * ori[(int)(ns*i) - 1][j]
					         + ((2.0/3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))* ori[(int)(ns*i) + 1][j]
					         + ((1.0 / 6.0)*t*t*t) * (ori[(int)(ns*i)][j]);
			}
			else if ((int)(ns*i) == 0)
			{
				newbuf[i][j] = ((2.0/3.0) + 0.5*t*t*t - t*t)*ori[(int)(ns*i)][j]
					         + ((2.0/3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*ori[(int)(ns*i) + 1][j]
					         + ((1.0 / 6.0)*(1 - t)*(1 - t)*(1 - t))  * (ori[(int)(ns*i) + 1][j])
					         + ((1.0 / 6.0)*t*t*t) * ori[(int)(ns*i) + 2][j];
			}
			else
			{
				newbuf[i][j] = ((2.0/3.0) + 0.5*t*t*t - t*t)*(ori[(int)(ns*i)][j])
					         + ((1.0/6.0)*(1 - t)*(1 - t)*(1 - t)) * (ori[(int)(ns*i) - 1][j])
					         + ((2.0/3.0) + 0.5*(1 - t)*(1 - t)*(1 - t) - (1 - t)*(1 - t))*(ori[(int)(ns*i) + 1][j])
					         + ((1.0 / 6.0)*t*t*t)* (ori[(int)(ns*i) + 2][j]);
			}

			output[i][j] = clipping(roundup(newbuf[i][j]));
		}
	}

	return output;
}
double** col_Pre_emphasis(double **ori, int row, int col)
{
	int i, j;
	double **buf = double_makememory(row, col);
	//pre emphasis 필터 계수 11탭을 사용했음
	double Sk[11] = { -0.002390, 0.008920,-0.033296,0.124284,-0.463918,1.731684,-0.463918,0.124284,-0.033296,0.008920,-0.002390 };

	for (i = 0; i < row; i++) // 미러링 적용
	{
		for (j = 0; j < col; j++)
		{
			if (j == col - 1)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i) + j - 5))*2.0 + *(Sk + 1)*(*(*(ori + i) + j - 4))*2.0 
					                + *(Sk + 2)*(*(*(ori + i) + j - 3))*2.0 + *(Sk + 3)*(*(*(ori + i) + j - 2))*2.0 
					                + *(Sk + 4)*(*(*(ori + i) + j - 1))*2.0
					                + *(Sk + 5)*(*(*(ori + i) + j));

			}
			else if (j == col - 2)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i) + j - 5)) + *(Sk + 1)*(*(*(ori + i) + j - 4)) 
					                + *(Sk + 2)*(*(*(ori + i) + j - 3)) + *(Sk + 3)*(*(*(ori + i) + j - 2))
					                + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j)) 
					                + *(Sk + 6)*(*(*(ori + i) + j + 1))
					                + *(Sk + 7)*(*(*(ori + i) + j)) + *(Sk + 8)*(*(*(ori + i) + j - 1)) //미러링부분
					                + *(Sk + 9)*(*(*(ori + i) + j - 2)) + *(Sk + 10)*(*(*(ori + i) + j - 3));//미러링부분
			}
			else if (j == col - 3)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i) + j - 5)) + *(Sk + 1)*(*(*(ori + i) + j - 4)) 
					                + *(Sk + 2)*(*(*(ori + i) + j - 3)) + *(Sk + 3)*(*(*(ori + i) + j - 2))
					                + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i) + j + 1)) + *(Sk + 7)*(*(*(ori + i) + j + 2))
					                + *(Sk + 8)*(*(*(ori + i) + j + 1)) + *(Sk + 9)*(*(*(ori + i) + j)) + *(Sk + 10)*(*(*(ori + i) + j - 1)); //미러링부분
			}
			else if (j == col - 4)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i) + j - 5)) + *(Sk + 1)*(*(*(ori + i) + j - 4)) 
					                + *(Sk + 2)*(*(*(ori + i) + j - 3)) + *(Sk + 3)*(*(*(ori + i) + j - 2))
					                + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j)) 
					                + *(Sk + 6)*(*(*(ori + i) + j + 1)) + *(Sk + 7)*(*(*(ori + i) + j + 2)) 
					                + *(Sk + 8)*(*(*(ori + i) + j + 3))
					                + *(Sk + 9)*(*(*(ori + i) + j + 2)) + *(Sk + 10)*(*(*(ori + i) + j + 1)); //미러링부분
			}
			else if (j == col - 5)
			{

				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i) + j - 5)) + *(Sk + 1)*(*(*(ori + i) + j - 4)) 
					                + *(Sk + 2)*(*(*(ori + i) + j - 3)) + *(Sk + 3)*(*(*(ori + i) + j - 2))
					                + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j)) 
					                + *(Sk + 6)*(*(*(ori + i) + j + 1)) + *(Sk + 7)*(*(*(ori + i) + j + 2)) 
					                + *(Sk + 8)*(*(*(ori + i) + j + 3)) + *(Sk + 9)*(*(*(ori + i) + j + 4))
					                + *(Sk + 10)*(*(*(ori + i) + j + 3)); //미러링부분
			}
			else if (j == 0)
			{
				*(*(buf + i) + j) = + *(Sk + 5)*(*(*(ori + i) + j)) + *(Sk + 6)*(*(*(ori + i) + j + 1))*2.0
					                + *(Sk + 7)*(*(*(ori + i) + j + 2))*2.0 + *(Sk + 8)*(*(*(ori + i) + j + 3))*2.0 
					                + *(Sk + 9)*(*(*(ori + i) + j + 4))*2.0 + *(Sk + 10)*(*(*(ori + i) + j + 5))*2.0;
			}
			else if (j == 1)
			{
				*(*(buf + i) + j) = + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i) + j + 1)) + *(Sk + 7)*(*(*(ori + i) + j + 2)) 
					                + *(Sk + 8)*(*(*(ori + i) + j + 3)) + *(Sk + 9)*(*(*(ori + i) + j + 4)) 
					                + *(Sk + 10)*(*(*(ori + i) + j + 5))
					                + *(Sk + 3)*(*(*(ori + i) + j)) + *(Sk + 2)*(*(*(ori + i) + j + 1)) //미러링부분
					                + *(Sk + 1)*(*(*(ori + i) + j + 2)) + *(Sk + 0)*(*(*(ori + i) + j + 3)); //미러링부분
			}
			else if (j == 2)
			{
				*(*(buf + i) + j) = + *(Sk + 3)*(*(*(ori + i) + j - 2)) + *(Sk + 4)*(*(*(ori + i) + j - 1)) 
					                + *(Sk + 5)*(*(*(ori + i) + j))		+ *(Sk + 6)*(*(*(ori + i) + j + 1))
					                + *(Sk + 7)*(*(*(ori + i) + j + 2)) + *(Sk + 8)*(*(*(ori + i) + j + 3)) 
					                + *(Sk + 9)*(*(*(ori + i) + j + 4)) + *(Sk + 10)*(*(*(ori + i) + j + 5))
					                + *(Sk + 2)*(*(*(ori + i) + j - 1)) + *(Sk + 1)*(*(*(ori + i) + j)) + *(Sk + 0)*(*(*(ori + i) + j + 1)); //미러링부분
			}
			else if (j == 3)
			{
				*(*(buf + i) + j) = + *(Sk + 2)*(*(*(ori + i) + j - 3)) + *(Sk + 3)*(*(*(ori + i) + j - 2)) 
					                + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i) + j + 1)) + *(Sk + 7)*(*(*(ori + i) + j + 2)) 
					                + *(Sk + 8)*(*(*(ori + i) + j + 3)) + *(Sk + 9)*(*(*(ori + i) + j + 4)) 
					                + *(Sk + 10)*(*(*(ori + i) + j + 5))
					                + *(Sk + 1)*(*(*(ori + i) + j - 2)) + *(Sk + 0)*(*(*(ori + i) + j - 1)); //미러링부분
			}
			else if (j == 4)
			{
				*(*(buf + i) + j) = + *(Sk + 1)*(*(*(ori + i) + j - 4)) + *(Sk + 2)*(*(*(ori + i) + j - 3)) 
					                + *(Sk + 3)*(*(*(ori + i) + j - 2)) + *(Sk + 4)*(*(*(ori + i) + j - 1))
					                + *(Sk + 5)*(*(*(ori + i) + j))  	+ *(Sk + 6)*(*(*(ori + i) + j + 1)) 
					                + *(Sk + 7)*(*(*(ori + i) + j + 2)) + *(Sk + 8)*(*(*(ori + i) + j + 3))
					                + *(Sk + 9)*(*(*(ori + i) + j + 4)) + *(Sk + 10)*(*(*(ori + i) + j + 5))
					                + *(Sk + 0)*(*(*(ori + i) + j - 3)); //미러링부분
			}

			else
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i) + j - 5)) + *(Sk + 1)*(*(*(ori + i) + j - 4)) 
					                + *(Sk + 2)*(*(*(ori + i) + j - 3)) + *(Sk + 3)*(*(*(ori + i) + j - 2))
					                + *(Sk + 4)*(*(*(ori + i) + j - 1)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i) + j + 1)) + *(Sk + 7)*(*(*(ori + i) + j + 2)) 
					                + *(Sk + 8)*(*(*(ori + i) + j + 3)) + *(Sk + 9)*(*(*(ori + i) + j + 4)) 
					                + *(Sk + 10)*(*(*(ori + i) + j + 5));
			}
		}
	}

	return buf;
}
double** row_Pre_emphasis(double **ori, int row, int col)
{
	int i, j;
	double **buf = double_makememory(row, col);
	//pre emphasis 필터 계수 11탭을 사용했음
	double Sk[11] = { -0.002390, 0.008920,-0.033296,0.124284,-0.463918,1.731684,-0.463918,0.124284,-0.033296,0.008920,-0.002390 };

	for (j = 0; j < col; j++) // 미러링 적용
	{
		for (i = 0; i < row; i++)
		{
			if (i == row - 1)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i - 5) + j))*2.0 + *(Sk + 1)*(*(*(ori + i - 4) + j))*2.0
					                + *(Sk + 2)*(*(*(ori + i - 3) + j))*2.0 + *(Sk + 3)*(*(*(ori + i - 2) + j))*2.0 
					                + *(Sk + 4)*(*(*(ori + i - 1) + j))*2.0
					                + *(Sk + 5)*(*(*(ori + i) + j));

			}
			else if (i == row - 2)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i - 5) + j)) + *(Sk + 1)*(*(*(ori + i - 4) + j))
					                + *(Sk + 2)*(*(*(ori + i - 3) + j)) + *(Sk + 3)*(*(*(ori + i - 2) + j))
					                + *(Sk + 4)*(*(*(ori + i - 1) + j)) + *(Sk + 5)*(*(*(ori + i) + j)) 
					                + *(Sk + 6)*(*(*(ori + i + 1) + j))
					                + *(Sk + 7)*(*(*(ori + i) + j)) + *(Sk + 8)*(*(*(ori + i - 1) + j)) //미러링부분
					                + *(Sk + 9)*(*(*(ori + i - 2) + j)) + *(Sk + 10)*(*(*(ori + i - 3) + j));//미러링부분
			}
			else if (i == row - 3)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i - 5) + j)) + *(Sk + 1)*(*(*(ori + i - 4) + j)) 
					                + *(Sk + 2)*(*(*(ori + i - 3) + j)) + *(Sk + 3)*(*(*(ori + i - 2) + j))
					                + *(Sk + 4)*(*(*(ori + i - 1) + j)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i + 1) + j)) + *(Sk + 7)*(*(*(ori + i + 2) + j))
					                + *(Sk + 8)*(*(*(ori + i + 1) + j)) + *(Sk + 9)*(*(*(ori + i) + j)) + *(Sk + 10)*(*(*(ori + i - 1) + j)); //미러링부분
			}
			else if (i == row - 4)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i - 5) + j)) + *(Sk + 1)*(*(*(ori + i - 4) + j)) 
					                + *(Sk + 2)*(*(*(ori + i - 3) + j)) + *(Sk + 3)*(*(*(ori + i - 2) + j))
					                + *(Sk + 4)*(*(*(ori + i - 1) + j)) + *(Sk + 5)*(*(*(ori + i) + j)) 
					                + *(Sk + 6)*(*(*(ori + i + 1) + j)) + *(Sk + 7)*(*(*(ori + i + 2) + j)) 
					                + *(Sk + 8)*(*(*(ori + i + 3) + j))
					                + *(Sk + 9)*(*(*(ori + i + 2) + j)) + *(Sk + 10)*(*(*(ori + i + 1) + j)); //미러링부분
			}
			else if (i == row - 5)
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i - 5) + j)) + *(Sk + 1)*(*(*(ori + i - 4) + j))
					                + *(Sk + 2)*(*(*(ori + i - 3) + j)) + *(Sk + 3)*(*(*(ori + i - 2) + j))
					                + *(Sk + 4)*(*(*(ori + i - 1) + j)) + *(Sk + 5)*(*(*(ori + i) + j)) 
					                + *(Sk + 6)*(*(*(ori + i + 1) + j)) + *(Sk + 7)*(*(*(ori + i + 2) + j)) 
					                + *(Sk + 8)*(*(*(ori + i + 3) + j)) + *(Sk + 9)*(*(*(ori + i + 4) + j))
					                + *(Sk + 10)*(*(*(ori + i + 3) + j)); //미러링부분
			}
			else if (i == 0)
			{
				*(*(buf + i) + j) = + *(Sk + 5)*(*(*(ori + i) + j)) + *(Sk + 6)*(*(*(ori + i + 1) + j))*2.0
					                + *(Sk + 7)*(*(*(ori + i + 2) + j))*2.0 + *(Sk + 8)*(*(*(ori + i + 3) + j))*2.0 
					                + *(Sk + 9)*(*(*(ori + i + 4) + j))*2.0	+ *(Sk + 10)*(*(*(ori + i + 5) + j))*2.0;
			}
			else if (i == 1)
			{
				*(*(buf + i) + j) = + *(Sk + 4)*(*(*(ori + i - 1) + j)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i + 1) + j)) + *(Sk + 7)*(*(*(ori + i + 2) + j)) 
					                + *(Sk + 8)*(*(*(ori + i + 3) + j)) + *(Sk + 9)*(*(*(ori + i + 4) + j)) 
					                + *(Sk + 10)*(*(*(ori + i + 5) + j))
					                + *(Sk + 3)*(*(*(ori + i) + j)) + *(Sk + 2)*(*(*(ori + i + 1) + j)) //미러링부분
					                + *(Sk + 1)*(*(*(ori + i + 2) + j)) + *(Sk + 0)*(*(*(ori + i + 3) + j)); //미러링부분
			}
			else if (i == 2)
			{
				*(*(buf + i) + j) = + *(Sk + 3)*(*(*(ori + i - 2) + j)) + *(Sk + 4)*(*(*(ori + i - 1) + j)) 
					                + *(Sk + 5)*(*(*(ori + i) + j))  	+ *(Sk + 6)*(*(*(ori + i + 1) + j)) 
					                + *(Sk + 7)*(*(*(ori + i + 2) + j)) + *(Sk + 8)*(*(*(ori + i + 3) + j)) 
					                + *(Sk + 9)*(*(*(ori + i + 4) + j)) + *(Sk + 10)*(*(*(ori + i + 5) + j))
					                + *(Sk + 2)*(*(*(ori + i - 1) + j)) + *(Sk + 1)*(*(*(ori + i) + j)) + *(Sk + 0)*(*(*(ori + i + 1) + j)); //미러링부분
			}
			else if (i == 3)
			{
				*(*(buf + i) + j) = + *(Sk + 2)*(*(*(ori + i - 3) + j)) + *(Sk + 3)*(*(*(ori + i - 2) + j))
					                + *(Sk + 4)*(*(*(ori + i - 1) + j)) + *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i + 1) + j)) + *(Sk + 7)*(*(*(ori + i + 2) + j)) 
					                + *(Sk + 8)*(*(*(ori + i + 3) + j)) + *(Sk + 9)*(*(*(ori + i + 4) + j))
					                + *(Sk + 10)*(*(*(ori + i + 5) + j))
					                + *(Sk + 1)*(*(*(ori + i - 2) + j)) + *(Sk + 0)*(*(*(ori + i - 1) + j)); //미러링부분
			}
			else if (i == 4)
			{
				*(*(buf + i) + j) = + *(Sk + 1)*(*(*(ori + i - 4) + j)) + *(Sk + 2)*(*(*(ori + i - 3) + j))
					                + *(Sk + 3)*(*(*(ori + i - 2) + j)) + *(Sk + 4)*(*(*(ori + i - 1) + j)) 
					                + *(Sk + 5)*(*(*(ori + i) + j))   	+ *(Sk + 6)*(*(*(ori + i + 1) + j)) 
					                + *(Sk + 7)*(*(*(ori + i + 2) + j)) + *(Sk + 8)*(*(*(ori + i + 3) + j))
					                + *(Sk + 9)*(*(*(ori + i + 4) + j)) + *(Sk + 10)*(*(*(ori + i + 5) + j))
					                + *(Sk + 0)*(*(*(ori + i - 3) + j)); //미러링부분
			}

			else
			{
				*(*(buf + i) + j) = + *(Sk + 0)*(*(*(ori + i - 5) + j)) + *(Sk + 1)*(*(*(ori + i - 4) + j)) 
					                + *(Sk + 2)*(*(*(ori + i - 3) + j)) + *(Sk + 3)*(*(*(ori + i - 2) + j))
					                + *(Sk + 4)*(*(*(ori + i - 1) + j))	+ *(Sk + 5)*(*(*(ori + i) + j))
					                + *(Sk + 6)*(*(*(ori + i + 1) + j)) + *(Sk + 7)*(*(*(ori + i + 2) + j)) 
					                + *(Sk + 8)*(*(*(ori + i + 3) + j)) + *(Sk + 9)*(*(*(ori + i + 4) + j)) 
					                + *(Sk + 10)*(*(*(ori + i + 5) + j));
			}

		}
	}
	return buf;

}
void test1(double **ori_buf, unsigned char**original)
{
	// 512*512 ->1000*1000 ->512*512 

	FILE *op;
	double **buf1, **buf2, **buf3, **buf4, **buf5, **buf6, **buf7;
	unsigned char** output1, ** output2, ** output3, ** output4;

	buf1    = col_Pre_emphasis(ori_buf, 512, 512); //가로 pre-emphasis필터
	output1 = B_spline_col(buf1, 512, 1000); //가로보간-> 512*1000

	buf2    = change_double(output1, 512, 1000); //가로보간 끝난것을 double형으로 변환

	buf3    = row_Pre_emphasis(buf2, 512, 1000); //세로 pre - emphasis필터
	output2 = B_spline_row(buf3, 512, 1000); //세로보간 ->1000*1000 으로 확대함

	// 512*512로 다시 축소

	buf4   = change_double(output2, 1000, 1000);
	buf5    = col_Pre_emphasis(buf4, 1000, 1000);
	output3 = B_spline_col(buf5, 1000, 512); //가로보간 -> 1000*512

	buf6    = change_double(output3, 1000, 512);
	buf7    = row_Pre_emphasis(buf6, 1000, 512);
	output4 = B_spline_row(buf7, 1000, 512); //세로보간 ->512*512
													//------------------------------------
	fopen_s(&op, "B_spline_test1_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("B_spline TEST1 : MSE값 : %.1lf\n", MSE(original, output4));

	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	double_freememory(buf4, 1000);
	double_freememory(buf5, 1000);
	double_freememory(buf6, 1000);
	double_freememory(buf7, 1000);
	char_freememory(output1, 512);
	char_freememory(output2, 1000);
	char_freememory(output3, 1000);
	char_freememory(output4, 512);
	fclose(op);
}
void test2(double **ori_buf, unsigned char**original)
{
	// 512*512 ->400*400 ->512*512 * LPF사용 

	FILE *op; 
	double **buf1, **buf2, **buf3, **buf4, **buf5, **buf6, **buf7,**buf8,**buf9;
	unsigned char** output1, ** output2, ** output3, ** output4;

	buf1    = colLPF(ori_buf, 512, 512, lpf1); //가로 LPF
	buf2    = col_Pre_emphasis(buf1, 512, 512); //가로 pre-emphasis필터 
	output1 = B_spline_col(buf2, 512, 400); //가로보간-> 512*400

	buf3    = change_double(output1, 512, 400); //가로보간 끝난것을 double형으로 변환
	buf4    = rowLPF(buf3, 512, 400, lpf1); //세로 LPF
	buf5    = row_Pre_emphasis(buf4, 512, 400); //세로 pre-emphasis필터
	output2 = B_spline_row(buf5, 512, 400); //세로보간 ->400*400 으로 축소함
										  
	// 400*400 -> 512*512 다시 확대

	buf6   = change_double(output2, 400, 400);
	buf7   = col_Pre_emphasis(buf6, 400, 400);
	output3= B_spline_col(buf7, 400, 512); //가로보간 -> 400*512

    buf8   = change_double(output3, 400, 512);
	buf9   = row_Pre_emphasis(buf8, 400, 512);
    output4 = B_spline_row(buf9, 400, 512); //세로보간 ->512*512
	
									   //------------------------------------
	fopen_s(&op, "B_spline_test2_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("B_spline TEST2 : MSE값 : %.1lf\n", MSE(original, output4));
	
	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	double_freememory(buf4, 512);
	double_freememory(buf5, 512);
	double_freememory(buf6, 400);
	double_freememory(buf7, 400);
	double_freememory(buf8, 400);
	double_freememory(buf9, 400);
	char_freememory(output1, 512);
	char_freememory(output2, 400);
	char_freememory(output3, 400);
	char_freememory(output4, 512);
	fclose(op);

}
void test3(double **ori_buf, unsigned char**original)
{
	// 512*512 ->400*400 ->512*512  * LPF사용안함 
	FILE *op; 
	double **buf1, **buf2, **buf3, **buf4, **buf5, **buf6, **buf7;
	unsigned char** output1, ** output2, ** output3, ** output4;

	buf1   = col_Pre_emphasis(ori_buf, 512, 512);
	output1= B_spline_col(buf1, 512, 400); //가로보간-> 512*400

	buf2   = change_double(output1, 512, 400); //가로보간 끝난것을 double형으로 변환
    buf3   = row_Pre_emphasis(buf2, 512, 400);
	output2= B_spline_row(buf3, 512, 400); //세로보간 ->400*400 으로 축소함
								
	// 400*400 -> 512*512 다시 확대

	buf4    = change_double(output2, 400, 400); //축소된것을 더블형데이터로 변환
	buf5    = col_Pre_emphasis(buf4, 400, 400);
	output3 = B_spline_col(buf5, 400, 512); //가로보간 -> 400*512

	buf6    = change_double(output3, 400, 512); //가로보간한것을 더블형데이터로 변환
	buf7    = row_Pre_emphasis(buf6, 400, 512);
	output4 = B_spline_row(buf7, 400, 512); //세로보간 ->512*512
	
												   
	fopen_s(&op, "B_spline_test3_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("B_spline TEST3 : MSE값 : %.1lf\n", MSE(original, output4));

	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	double_freememory(buf4, 400);
	double_freememory(buf5, 400);
	double_freememory(buf6, 400);
	double_freememory(buf7, 400);
	char_freememory(output1, 512);
	char_freememory(output2, 400);
	char_freememory(output3, 400);
	char_freememory(output4, 512);
	fclose(op);

}
void test4(double **ori_buf)
{
	// 512*512->945*945 확대
	FILE *op; 
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2;

	buf1    = col_Pre_emphasis(ori_buf, 512, 512);
	output1 = B_spline_col(buf1, 512, 945); //가로보간 512*945

	buf2    = change_double(output1, 512, 945); //가로보간 끝난것을 double형으로 변환
	buf3    = row_Pre_emphasis(buf2, 512, 945);
	output2 = B_spline_row(buf3, 512, 945); //945*945으로 축소함

	fopen_s(&op, "B_spline_test4_result.img", "wb");
	output2 = write(output2, op, 945);

	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 945);
	
	fclose(op);
}
void test5(double **ori_buf)
{
	// 512*512 ->298*298  * LPF사용
	FILE *op; 
	double **buf1, **buf2, **buf3, **buf4, **buf5;
	unsigned char** output1, ** output2;

	buf1    = colLPF(ori_buf, 512, 512, lpf2); //가로 LPF
	buf2    = col_Pre_emphasis(buf1, 512, 512);
	output1 = B_spline_col(buf2, 512, 298); //가로보간-> 512*298

	buf3    = change_double(output1, 512, 298); //가로보간 끝난것을 double형으로 변환
	buf4    = rowLPF(buf3, 512, 298, lpf2); //세로 LPF
	buf5    = row_Pre_emphasis(buf4, 512, 298);
	output2 = B_spline_row(buf5, 512, 298); //세로보간 ->298*298 으로 축소함

	fopen_s(&op, "B_spline_test5_result.img", "wb");
	output2 = write(output2, op, 298);

	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	double_freememory(buf4, 512);
	double_freememory(buf5, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 298);
	fclose(op);
}
void test6(double **ori_buf)
{
	// 512*512 ->298*298  * LPF사용안함
	FILE *op;
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2;


	buf1    = col_Pre_emphasis(ori_buf, 512, 512);
	output1 = B_spline_col(buf1, 512, 298); //가로보간-> 512*298

	buf2    = change_double(output1, 512, 298); //가로보간 끝난것을 double형으로 변환
	buf3    = row_Pre_emphasis(buf2, 512, 298); //
	output2 = B_spline_row(buf3, 512, 298); //세로보간 ->298*298 으로 축소함

	fopen_s(&op, "B_spline_test6_result.img", "wb");
	output2 = write(output2, op, 298);

	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 298);
	
	fclose(op);
}