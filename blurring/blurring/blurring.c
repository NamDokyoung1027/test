#define		_CRT_SECURE_NO_WARNINGS

#include	<stdio.h>
#include	<memory.h>
#include	"d:/V/first/fileio.h"
#define		IMGSIZ 256

main()
{
	int		status;
	int		i, j;
	float	a, w;

	char	fname[100];

	unsigned char	buf1[IMGSIZ][IMGSIZ];
	int	buf2[IMGSIZ][IMGSIZ];
	unsigned char	buf3[IMGSIZ][IMGSIZ];

	memset(fname, 0, 100);					//memset : 메모리를 어떤 값으로 리셋시키거나 넣어줄때 사용
	memset(buf1, 0, IMGSIZ*IMGSIZ);			// -> #include <memory.h> 사용
	memset(buf2, 128, IMGSIZ*IMGSIZ);		// buf2[256][256]을 0으로 초기화
	memset(buf3, 0, IMGSIZ*IMGSIZ);

	/* Data를 읽어오는 프로그램 */
	printf("Enter input file name: ");
	scanf("%s", fname);
	status = load_data(fname, buf1, 'b', IMGSIZ, IMGSIZ);	//하드디스크의 파일을 읽어와라

	if (status != SUCCESS)
		return;
	
	printf("a값을 입력하시오 : ");
	scanf("%f", &a);

	w = (9 * a) - 1;

	/* high-boost filtering */
	for (i = 1; i < IMGSIZ - 1; i++){
		for (j = 1; j < IMGSIZ - 1; j++){	

			buf2[i][j] = - buf1[i - 1][j - 1] - buf1[i - 1][j] - buf1[i - 1][j + 1]
						- buf1[i][j - 1] + (w * buf1[i][j]) - buf1[i][j + 1]
						- buf1[i + 1][j - 1] - buf1[i + 1][j] - buf1[i + 1][j + 1];

			if (buf2[i][j] > 255 || buf2[i][j] < 0){
				if (buf2[i][j] > 255)
					buf2[i][j] = 255;
				if (buf2[i][j] < 0)
					buf2[i][j] = 0;
			}

			buf3[i][j] = buf2[i][j];
		}
	}



	/* 결과를 저장하는 프로그램 */
	memset(fname, 0, 100);
	printf("Enter output file name: ");
	scanf("%s", fname);
	save_data(fname, buf3, 'b', IMGSIZ, IMGSIZ);
}



//Gaussian Smoothing
/*
buf2[i][j] = (buf1[i - 1][j - 1] + (2 * buf1[i - 1][j]) + buf1[i - 1][j + 1]
+ (2 * buf1[i][j - 1]) + (4 * buf1[i][j]) + (2 * buf1[i][j + 1])
+ buf1[i + 1][j - 1] + (2 * buf1[i + 1][j]) + buf1[i + 1][j + 1]) / 16;*/

// sharpening
/* 
if (buf2[i][j] > 255 || buf2[i][j] < 0){
	if (buf2[i][j] > 255)
		buf2[i][j] = 255;
	if (buf2[i][j] < 0)
		buf2[i][j] = 0;
}
buf3[i][j] = buf2[i][j];

// (a)
- buf1[i - 1][j] - buf1[i][j - 1] + (5*buf1[i][j]) - buf1[i][j + 1] - buf1[i + 1][j];

// (b)
- buf1[i - 1][j - 1] - buf1[i - 1][j] - buf1[i - 1][j + 1]
- buf1[i][j - 1] + (9 * buf1[i][j]) - buf1[i][j + 1]
- buf1[i + 1][j - 1] - buf1[i + 1][j] - buf1[i + 1][j + 1];

// (c)
buf1[i - 1][j - 1] - (2 * buf1[i - 1][j]) + buf1[i - 1][j + 1]
- (2 * buf1[i][j - 1]) + (5 * buf1[i][j]) - (2 * buf1[i][j + 1])
+ buf1[i + 1][j - 1] - (2 * buf1[i + 1][j]) + buf1[i + 1][j + 1];*/

/*blurring*/
/*			
//3x3
buf2[i][j] =  (buf1[i - 1][j - 1] + buf1[i - 1][j] + buf1[i - 1][j + 1] 
			+ buf1[i][j - 1] + buf1[i][j] + buf1[i][j + 1]
			+ buf1[i + 1][j - 1] + buf1[i + 1][j] + buf1[i + 1][j + 1]) / 9;

// 5x5
buf2[i][j] = (buf1[i - 2][j - 2] + buf1[i - 2][j - 1] + buf1[i - 2][j] + buf1[i - 2][j + 1] + buf1[i - 2][j + 2]
			+ buf1[i - 1][j - 2] + buf1[i - 1][j - 1] + buf1[i - 1][j] + buf1[i - 1][j + 1] + buf1[i - 1][j + 2] 
			+ buf1[i][j - 2] + buf1[i][j - 1] + buf1[i][j] + buf1[i][j + 1] + buf1[i][j + 2] 
			+ buf1[i + 1][j - 2] + buf1[i + 1][j - 1] + buf1[i + 1][j] + buf1[i + 1][j + 1] + buf1[i + 1][j + 2]
			+ buf1[i + 2][j - 2] + buf1[i + 2][j - 1] + buf1[i + 2][j] + buf1[i + 2][j + 1] + buf1[i + 2][j + 2]) / 25;*/



