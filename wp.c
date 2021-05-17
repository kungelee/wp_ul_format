/*
读取文本文件，输出HTML文档
<ul>
<li> ... </li>
...
<li> ...</li>
</ul>
2021年5月17日18:56:43  by jefflee.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 256  /*缓冲区大最大值*/


int main(void)
{
	FILE *fp_input           = NULL;             /*读取文件指针*/
	FILE *fp_output          = NULL;             /*写入文件指针*/
	const char  input_file[] = {"input.txt"};    /*读取文件名*/
	const char output_file[] = {"output.txt"};   /*生成文件名*/
	char  line_buf[BUF_SIZE] = {0};              /*按行读取缓冲区*/
	
	fp_input  = fopen(input_file, "r");
	fp_output = fopen(output_file, "w+");
	
	if (NULL == fp_input || NULL == fp_output) {
		perror("Open or Write error!");
		exit(1);
	}
	
	fprintf(fp_output, "%s", "<ul>\n");
	while (!feof(fp_input)) {
		memset(line_buf, 0, BUF_SIZE);          /*缓冲区清零，非必要*/
		fgets(line_buf, BUF_SIZE, fp_input);
		for (int i = 0; i < BUF_SIZE; ++i) {    /*格式美化，将换行去掉*/
			if ('\n' == line_buf[i]) {
				line_buf[i] = '\0';
				break;
			}
		}
		fprintf(fp_output, "<li>%s</li>\n", line_buf);
	}
	fprintf(fp_output, "%s", "</ul>");
	
	fclose(fp_input);
	fclose(fp_output);
	
	char cmd[BUF_SIZE] = {0};
	const char app[] = {"notepad"};
	strcpy(cmd, app);
	strcat(cmd, " ");
	strcat(cmd, output_file);
	system(cmd);                                /*用计事本打开生成文件*/  

	return 0;
}