#include "header.h"

unsigned char** Cubic_Convolution_col(double**ori, int oripixel, int newpixel)
{
	int i, j; double  t;

	double **newbuf = double_makememory(oripixel, newpixel);
	unsigned char **output = char_makememory(oripixel, newpixel);

	double ns = (double)(oripixel-1) / (newpixel-1);
	double a = -0.5;

	for (i = 0; i < oripixel; i++) //가로 scaling
	{
		for (j = 0; j < newpixel; j++)
		{

			t = ns*j - (int)(ns*j);

			if ((int)(ns*j) == oripixel - 1)
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*(ori[i][(int)(ns*j)])
				           	+ ((a*t*t*t) - (2.0 * a*t*t) + a*t) * (ori[i][(int)(ns*j) - 1])
				        	+ ((-(a + 2.0)*(t*t*t)) + ((2.0 * a + 3.0)*t*t) - (a*t))*(ori[i][(int)(ns*j) - 1])
				        	+ ((-a*t*t*t) + (a*t*t)) * (ori[i][(int)(ns*j) - 2]);
			}
			else if ((int)(ns*j) == oripixel - 2)
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*(ori[i][(int)(ns*j)])
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * (ori[i][(int)(ns*j) - 1])
					         + ((-(a + 2.0)*(t*t*t)) + ((2.0 * a + 3.0)*t*t) - (a*t))*(ori[i][(int)(ns*j) + 1])
					         + ((-a*t*t*t) + (a*t*t)) * (ori[i][(int)(ns*j)]);
			}
			else if ((int)(ns*j) == 0)
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*(ori[i][(int)(ns*j)])
					         + ((-(a + 2.0)*(t*t*t)) + ((2.0 * a + 3.0)*t*t) - (a*t))*(ori[i][(int)(ns*j) + 1])
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * (ori[i][(int)(ns*j) + 1])
					         + ((-a*t*t*t) + (a*t*t)) * (ori[i][(int)(ns*j) + 2]);
			}
			else
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*(ori[i][(int)(ns*j)])
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * (ori[i][(int)(ns*j) - 1])
					         + ((-(a + 2.0)*(t*t*t)) + ((2.0 * a + 3.0)*t*t) - (a*t))*(ori[i][(int)(ns*j) + 1])
					         + ((-a*t*t*t) + (a*t*t)) * (ori[i][(int)(ns*j) + 2]);
			}

			output[i][j] = clipping(roundup(newbuf[i][j])); //클리핑->반올림한후 저장
		}
	}

	return output;
}
unsigned char** Cubic_Convolution_row(double **ori, int oripixel, int newpixel)
{
	int i, j; double  t;

	double **newbuf = double_makememory(newpixel, newpixel);
	unsigned char **output = char_makememory(newpixel, newpixel);

	double ns = (double)(oripixel-1) / (newpixel-1);
	double a = -0.5;

	for (j = 0; j < newpixel; j++) //세로 scaling
	{
		for (i = 0; i < newpixel; i++)
		{
			t = ns*i - (int)(ns*i);


			if ((int)(ns*i) == oripixel - 1)
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*ori[(int)(ns*i)][j]
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * ori[(int)(ns*i) - 1][j]
					         + ((-(a + 2.0)*(t*t*t)) + ((2 * a + 3.0)*t*t) - (a*t))*ori[(int)(ns*i) - 1][j]
					         + ((-a*t*t*t) + (a*t*t)) * (ori[(int)(ns*i) - 2][j]);
			}
			else if ((int)(ns*i) == oripixel - 2)
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*ori[(int)(ns*i)][j]
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * ori[(int)(ns*i) - 1][j]
					         + ((-a*t*t*t) + (a*t*t))* ori[(int)(ns*i) + 1][j]
					         + ((-a*t*t*t) + (a*t*t)) * (ori[(int)(ns*i)][j]);
			}
			else if ((int)(ns*i) == 0)
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*ori[(int)(ns*i)][j]
					         + ((-(a + 2.0)*(t*t*t)) + ((2 * a + 3.0)*t*t) - (a*t))*ori[(int)(ns*i) + 1][j]
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * (ori[(int)(ns*i) + 1][j])
					         + ((-a*t*t*t) + (a*t*t))* ori[(int)(ns*i) + 2][j];
			}
			else
			{
				newbuf[i][j] = (((a + 2.0)*(t*t*t)) - ((3.0 + a)*t*t) + 1.0)*(ori[(int)(ns*i)][j])
					         + ((a*t*t*t) - (2.0 * a*t*t) + a*t) * (ori[(int)(ns*i) - 1][j])
					         + ((-(a + 2.0)*(t*t*t)) + ((2 * a + 3.0)*t*t) - (a*t))*(ori[(int)(ns*i) + 1][j])
					         + ((-a*t*t*t) + (a*t*t)) * (ori[(int)(ns*i) + 2][j]);
			}

			output[i][j] = clipping(roundup(newbuf[i][j]));
		}
	}
	return output;
}
void test1(double **ori_buf, unsigned char**original)
{
	// 512*512 ->1000*1000 ->512*512 

	FILE *op;
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2, ** output3, ** output4;

	output1 = Cubic_Convolution_col(ori_buf, 512, 1000); //가로보간-> 512*1000

	buf1    = change_double(output1, 512, 1000); //가로보간 끝난것을 double형으로 변환
											
	output2 = Cubic_Convolution_row(buf1, 512, 1000); //세로보간 ->1000*1000 으로 확대함

	// 512*512로 다시 축소

	buf2    = change_double(output2, 1000, 1000);
	output3 = Cubic_Convolution_col(buf2, 1000, 512); //가로보간 -> 1000*512

	buf3    = change_double(output3, 1000, 512);
	output4 = Cubic_Convolution_row(buf3, 1000, 512); //세로보간 ->512*512
											 //------------------------------------
	fopen_s(&op, "Cubic_Convolution_test1_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("Cubic_Convolution TEST1 : MSE값 : %.1lf\n", MSE(original, output4));
	double_freememory(buf1, 512);
	double_freememory(buf2, 1000);
	double_freememory(buf3, 512);
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
	double **buf1, **buf2, **buf3, **buf4, **buf5;
	unsigned char** output1, ** output2, ** output3, ** output4;
	
	buf1    = colLPF(ori_buf, 512, 512, lpf1); //가로 LPF
	output1 = Cubic_Convolution_col(buf1, 512, 400); //가로보간-> 512*400

	buf2    = change_double(output1, 512, 400); //가로보간 끝난것을 double형으로 변환
	buf3    = rowLPF(buf2, 512, 400, lpf1); //세로 LPF
	output2 = Cubic_Convolution_row(buf3, 512, 400); //세로보간 ->400*400 으로 축소함
	
    // 400*400 -> 512*512 다시 확대

	buf4    = change_double(output2, 400, 400);
	output3 = Cubic_Convolution_col(buf4, 400, 512); //가로보간 -> 512*400

	buf5   = change_double(output3, 400, 512); //
	output4= Cubic_Convolution_row(buf5, 400, 512); //세로보간 ->512*512
										//------------------------------------
	fopen_s(&op, "Cubic_Convolution_test2_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("Cubic_Convolution TEST2 : MSE값 : %.1lf\n", MSE(original, output4));
	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	double_freememory(buf4, 400);
	double_freememory(buf5, 400);
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
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2, ** output3, ** output4;

	output1= Cubic_Convolution_col(ori_buf, 512, 400); //가로보간-> 512*400

	buf1   = change_double(output1, 512, 400); //가로보간 끝난것을 double형으로 변환
	output2 = Cubic_Convolution_row(buf1, 512, 400); //세로보간 ->400*400 으로 축소함

	// 400*400 -> 512*512 다시 확대

	buf2    = change_double(output2, 400, 400); //축소된것을 더블형데이터로 변환
	output3 = Cubic_Convolution_col(buf2, 400, 512); //세로보간 -> 512*400

	buf3    = change_double(output3, 400, 512); //가로보간한것을 더블형데이터로 변환
	output4 = Cubic_Convolution_row(buf3, 400, 512); //가로보간 ->512*512
											
	fopen_s(&op, "Cubic_Convolution_test3_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("Cubic_Convolution TEST3 : MSE값 : %.1lf\n", MSE(original, output4));
	fclose(op);

}
void test4(double **ori_buf)
{
	// 512*512 ->945*945 확대
	FILE *op; 
	double **buf1;
	unsigned char** output1, ** output2;
	output1 = Cubic_Convolution_col(ori_buf, 512, 945); //가로보간 512*945

	buf1    = change_double(output1, 512, 945); //가로보간 끝난것을 double형으로 변환
	output2 = Cubic_Convolution_row(buf1, 512, 945); //400 400 으로 축소함

	fopen_s(&op, "Cubic_Convolution_test4_result.img", "wb");
	output2 = write(output2, op, 945);

	double_freememory(buf1, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 945);
	fclose(op);
}
void test5(double **ori_buf)
{
	//512*512->298*298  * LPF사용
	FILE *op;
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2;

	buf1    = colLPF(ori_buf, 512, 512, lpf2); //가로 LPF
	output1 = Cubic_Convolution_col(buf1, 512, 298); //가로보간-> 512*298

	buf2    = change_double(output1, 512, 298); //가로보간 끝난것을 double형으로 변환
	buf3    = rowLPF(buf2, 512, 298, lpf2); //세로 LPF
	output2 = Cubic_Convolution_row(buf3, 512, 298); //세로보간 ->298*298 으로 축소함

	fopen_s(&op, "Cubic_Convolution_test5_result.img", "wb");
	output2 = write(output2, op, 298);
	
	double_freememory(buf1, 512);
	double_freememory(buf2, 512);
	double_freememory(buf3, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 298);
	fclose(op);
}
void test6(double **ori_buf)
{
	//512*512->298*298  * LPF 사용안함
	FILE *op;
	double **buf1;
	unsigned char** output1, ** output2;


	output1 = Cubic_Convolution_col(ori_buf, 512, 298); //가로보간-> 512*298

	buf1    = change_double(output1, 512, 298); //가로보간 끝난것을 double형으로 변환
	output2 = Cubic_Convolution_row(buf1, 512, 298); //세로보간 ->298*298 으로 축소함

	fopen_s(&op, "Cubic_Convolution_test6_result.img", "wb");
	output2 = write(output2, op, 298);

	double_freememory(buf1, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 298);
	fclose(op);
}