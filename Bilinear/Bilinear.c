#include "header.h"

unsigned char** Bilinear_col(double**ori, int oripixel, int newpixel)
{
	int i, j; double t;
	double **newbuf = double_makememory(oripixel, newpixel);
	unsigned char** output = char_makememory(oripixel, newpixel);
	double ns = (double)(oripixel-1 ) / (newpixel-1 );

	for (i = 0; i < oripixel; i++) //���� scaling
	{
		for (j = 0; j < newpixel; j++)
		{
			t = ((ns*j) - (int)(ns*j)); //0<=t<1 
			if ((int)(ns*j) == oripixel - 1)
				newbuf[i][j] = ori[i][(int)(ns*j)];
			else
				newbuf[i][j] = ori[i][(int)(ns*j)] + ((ori[i][(int)(ns*j) + 1] - ori[i][(int)(ns*j)]) *t);
			
			output[i][j] = clipping(roundup(newbuf[i][j]));
		}
	}
	return output;
}
unsigned char** Bilinear_row(double **ori, int oripixel, int newpixel)
{
	int i, j;	double t;
	double **newbuf = double_makememory(newpixel, newpixel);
	unsigned char **output = char_makememory(newpixel, newpixel);
	double ns = (double)(oripixel-1 ) / (newpixel-1 );

	for (j = 0; j < newpixel; j++) //���� scaling
	{
		for (i = 0; i < newpixel; i++)
		{
			t = ((ns*i) - (int)(ns*i));
			if ((int)(ns*i) == oripixel - 1)
				newbuf[i][j] = ori[(int)(ns*i)][j];
			else
				newbuf[i][j] = ori[(int)(ns*i)][j] + ((ori[(int)(ns*i) + 1][j] - ori[(int)(ns*i)][j]) * t);
			
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

	output1 = Bilinear_col(ori_buf, 512, 1000); //����(��)����-> 512*1000

	buf1    = change_double(output1, 512, 1000); //���κ��� �������� double������ ��ȯ

	output2 = Bilinear_row(buf1, 512, 1000); //����(��)���� ->1000*1000 ���� Ȯ����

	 // 512*512�� �ٽ����

	buf2    = change_double(output2, 1000, 1000); 
	output3 = Bilinear_col(buf2, 1000, 512); //���κ��� -> 1000*512

	buf3   = change_double(output3, 1000, 512);
	output4 = Bilinear_row(buf3, 1000, 512); //���κ��� ->512*512
											 //------------------------------------
	fopen_s(&op, "Bilinear_test1_result.img", "wb");

	output4 = write(output4, op, 512);

	printf("Bilinear TEST1 : MSE�� : %.1lf\n", MSE(original, output4));

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
	// 512*512 ->400*400 ->512*512    * LPF��� 

	FILE *op; 
	double **buf1, **buf2, **buf3, **buf4, **buf5;
	unsigned char** output1, ** output2, ** output3, ** output4;

	buf1    = colLPF(ori_buf, 512, 512, lpf1); //���� LPF
	output1 = Bilinear_col(buf1, 512, 400); //���κ���-> 512*400

	buf2    = change_double(output1, 512, 400); //���κ��� �������� double������ ��ȯ
	buf3    = rowLPF(buf2, 512, 400, lpf1); //���� LPF
	output2 = Bilinear_row(buf3, 512, 400); //���κ��� ->400*400 ���� �����

	// 400*400 -> 512*512 �ٽ� Ȯ��

	buf4    = change_double(output2, 400, 400);
	output3 = Bilinear_col(buf4, 400, 512); //���κ��� -> 400*512

	buf5    = change_double(output3, 400, 512);
	output4 = Bilinear_row(buf5, 400, 512); //���κ��� ->512*512
											//------------------------------------
	fopen_s(&op, "Bilinear_test2_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("Bilinear TEST2 : MSE�� : %.1lf\n", MSE(original, output4));
	
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
	// 512*512 ->400*400 ->512*512   * LPF������ 
	FILE *op; 
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2, ** output3, ** output4;

	output1 = Bilinear_col(ori_buf, 512, 400); //���κ���-> 512*400

	buf1    = change_double(output1, 512, 400); //���κ��� �������� double������ ��ȯ
	output2 = Bilinear_row(buf1, 512, 400); //���κ��� ->400*400 ���� �����

	// 400*400 -> 512*512 �ٽ� Ȯ��
	buf2    = change_double(output2, 400, 400);
	output3 = Bilinear_col(buf2, 400, 512); //���κ��� -> 400*512

	buf3    = change_double(output3, 400, 512);
	output4 = Bilinear_row(buf3, 400, 512); //���κ��� ->512*512
											//----------------------------------
	fopen_s(&op, "Bilinear_test3_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("Bilinear TEST3 : MSE�� : %.1lf\n", MSE(original, output4));

	double_freememory(buf1, 512);
	double_freememory(buf2, 400);
	double_freememory(buf3, 400);
	char_freememory(output1, 512);
	char_freememory(output2, 400);
	char_freememory(output3, 400);
	char_freememory(output4, 512);
	fclose(op);


}
void test4(double **ori_buf)
{ 
	//512*512 -> 945*945 Ȯ��
	FILE *op; 
	double **buf1;
	unsigned char** output1, ** output2;

	output1 = Bilinear_col(ori_buf, 512, 945); //���κ��� 512*945

	buf1    = change_double(output1, 512, 945); //���κ��� �������� double������ ��ȯ
	output2 = Bilinear_row(buf1, 512, 945); //���κ��� 945*945 

	fopen_s(&op, "Bilinear_test4_result.img", "wb");

	output2 = write(output2, op, 945);

	double_freememory(buf1, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 945);
	fclose(op);
}
void test5(double **ori_buf)
{ 
	//512*512->298*298  * LPF���
	FILE *op;
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2;


	buf1    = colLPF(ori_buf, 512, 512, lpf2); //���� LPF
	output1 = Bilinear_col(buf1, 512, 298); //���κ���-> 512*298

	buf2    = change_double(output1, 512, 298); //���κ��� �������� double������ ��ȯ
	buf3    = rowLPF(buf2, 512, 298, lpf2); //���� LPF
	output2 = Bilinear_row(buf3, 512, 298); //���κ��� ->298*298 ���� �����

	fopen_s(&op, "Bilinear_test5_result.img", "wb");
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
	//512*512->298*298  * LPF ������
	FILE *op; 
	double **buf1;
	unsigned char** output1, ** output2;

	output1 = Bilinear_col(ori_buf, 512, 298); //���κ���-> 512*298

	buf1    = change_double(output1, 512, 298); //���κ��� �������� double������ ��ȯ
	output2 = Bilinear_row(buf1, 512, 298); //���κ��� ->298*298 ���� �����

	fopen_s(&op, "Bilinear_test6_result.img", "wb");
	output2 = write(output2, op, 298);

	double_freememory(buf1, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 298);
	fclose(op);
}