#include "header.h"
unsigned char** samplehold_col(double **ori, int oripixel, int newpixel)
{
	int i, j;

	double **newbuf=double_makememory(oripixel, newpixel);
	unsigned char **output = char_makememory(oripixel, newpixel);
	double ns = (double)(oripixel-1 ) / (newpixel-1);

	for (i = 0; i < oripixel; i++) //가로 scaling
	{
		for (j = 0; j < newpixel; j++)
		{
			newbuf[i][j] = ori[i][(int)(ns*j)];
			output[i][j] = clipping(roundup(newbuf[i][j])); //클리핑->반올림한후 저장
		}
		
	}

	return output;
}
unsigned char** samplehold_row(double **ori, int oripixel, int newpixel)
{
	int i, j;
	double **newbuf = double_makememory(newpixel, newpixel);
	unsigned char **output = char_makememory(newpixel, newpixel);

	double ns = (double)(oripixel-1) / (newpixel-1);
	for (j = 0; j < newpixel; j++) //세로 scaling
	{
		for (i = 0; i < newpixel; i++)
		{
			newbuf[i][j] = ori[(int)(ns*i)][j];
			output[i][j] = clipping(roundup(newbuf[i][j])); //클리핑->반올림한후 저장
		}

	}	
	return output;
}
void test1(double **ori_buf, unsigned char**original)
{
	// 512*512 ->1000*1000 ->512*512 

	FILE *op; 
	double **buf1,**buf2,**buf3;
	unsigned char** output1, ** output2, ** output3, ** output4;

	output1 = samplehold_col(ori_buf, 512, 1000); //가로보간-> 512*1000

	buf1    = change_double(output1, 512, 1000); //가로보간 끝난것을 double형으로 변환
											
	output2 = samplehold_row(buf1, 512, 1000); //세로보간 ->1000*1000 으로 확대함

	// 512*512 다시 축소

	buf2    = change_double(output2, 1000, 1000);
	output3 = samplehold_col(buf2, 1000, 512); //가로보간 -> 1000*512

	buf3    = change_double(output3, 1000, 512);
	output4 = samplehold_row(buf3, 1000, 512); //세로보간 ->512*512
											 //------------------------------------
	fopen_s(&op, "S&H_test1_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("TEST1 : MSE값 : %.1lf\n", MSE(original, output4));
	
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
	double **buf1, **buf2, **buf3, **buf4,**buf5;
	unsigned char** output1, ** output2, ** output3, ** output4;

	buf1    = colLPF(ori_buf, 512, 512,lpf1); //가로 LPF
	output1 = samplehold_col(buf1, 512, 400); //가로보간-> 512*400

	buf2    = change_double(output1, 512, 400); //가로보간 끝난것을 double형으로 변환
	buf3    = rowLPF(buf2, 512, 400,lpf1); //세로 LPF
	output2 = samplehold_row(buf3, 512, 400); //세로보간 ->400*400 으로 축소함

	// 400*400 -> 512*512 다시 확대

	buf4    = change_double(output2, 400, 400);
	output3 = samplehold_col(buf4, 400, 512); //가로보간 -> 400*512

	buf5    = change_double(output3, 400, 512);
	output4 = samplehold_row(buf5, 400, 512); //세로보간 ->512*512
											//------------------------------------
	fopen_s(&op, "S&H_test2_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("TEST2 : MSE값 : %.1lf\n", MSE(original, output4));

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
void test3(double **ori_buf,unsigned char**original)
{
	// 512*512 ->400*400 ->512*512 * LPF 사용안함 
	FILE *op; 
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2, ** output3, ** output4;


	output1 = samplehold_col(ori_buf, 512, 400); //가로보간-> 512*400
	
	buf1    = change_double(output1, 512, 400); //가로보간 끝난것을 double형으로 변환
	output2 = samplehold_row(buf1, 512, 400); //세로보간 ->400*400 으로 축소함

	// 400*400 -> 512*512 다시 확대

	buf2    = change_double(output2, 400, 400);
	output3 = samplehold_col(buf2, 400, 512); //가로보간 -> 400*512

	buf3    = change_double(output3, 400, 512);
	output4 = samplehold_row(buf3, 400, 512); //세로보간 ->512*512
											
	fopen_s(&op, "S&H_test3_result.img", "wb");
	output4 = write(output4, op, 512);

	printf("TEST3 : MSE값 : %.1lf\n", MSE(original, output4));
	
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
	// 512*512->945*945 확대
	FILE *op; 
	double **buf1;
	unsigned char** output1, ** output2;

	output1 = samplehold_col(ori_buf, 512, 945); //가로보간 512*945

	buf1    = change_double(output1, 512, 945); //가로보간 끝난것을 double형으로 변환
	output2 = samplehold_row(buf1, 512, 945); //세로보간 945* 945 로 확대

	fopen_s(&op, "S&H_test4_result.img", "wb");
	output2 = write(output2, op, 945);

	double_freememory(buf1, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 945);
	fclose(op);
}
void test5(double **ori_buf)
{
	//512*512 -> 298*298 축소  * LPF사용
	FILE *op; 
	double **buf1, **buf2, **buf3;
	unsigned char** output1, ** output2;

	buf1    = rowLPF(ori_buf, 512, 512, lpf2); //가로 LPF
	output1 = samplehold_col(buf1, 512, 298); //가로보간-> 512*298

	buf2    = change_double(output1, 512, 298); //가로보간 끝난것을 double형으로 변환
	buf3    = colLPF(buf2, 512, 298, lpf2); //세로 LPF
	output2 = samplehold_row(buf3, 512, 298); //세로보간 ->298*298 으로 축소함

	fopen_s(&op, "S&H_test5_result.img", "wb");
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
	//512*512 -> 298*298 축소  * LPF 사용안함
	FILE *op; 
	double **buf1;
	unsigned char** output1, ** output2;

	output1 = samplehold_col(ori_buf, 512, 298); //가로보간-> 512*298

	buf1 = change_double(output1, 512, 298); //가로보간 끝난것을 double형으로 변환
	output2 = samplehold_row(buf1, 512, 298); //세로보간 ->298*298 으로 축소함

	fopen_s(&op, "S&H_test6_result.img", "wb");
	output2 = write(output2, op, 298);

	double_freememory(buf1, 512);
	char_freememory(output1, 512);
	char_freememory(output2, 298);
	fclose(op);
}