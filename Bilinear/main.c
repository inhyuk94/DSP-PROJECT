#include "header.h"

void main()
{
	
	FILE *fp;
	fopen_s(&fp, "lena.img", "rb");
	if (fp == NULL)
	{
		printf("파일오픈실패!!!\n");
		exit(1);
	}

	unsigned char ** original=char_makememory(512,512);

	original = read(original, fp, 512); //파일 읽어옴
	double ** ori_buf = change_double(original, 512, 512); // double형으로 변환

	//-----------------------------------------------------------------------------------------------//
	test1(ori_buf, original);
	test2(ori_buf, original);
	test3(ori_buf, original);
	test4(ori_buf);
	test5(ori_buf);
	test6(ori_buf);

	double_freememory(ori_buf, 512);
	char_freememory(original, 512);
	fclose(fp);

}

