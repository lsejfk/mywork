#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<string>
#define MAXN 105
 
void process_line(const char *filename);
 
int main(int argc, char **argv)
{
	process_line("string.h");
}
 
void process_line(const char *filename)
{
	static char opened[MAXN][MAXN];//已经打开的文档
	static int cnt = 0;
	FILE *fin;
	char line[MAXN];
 
	for (int i = 0; i < cnt; i++) {//此文档已经打开
		if (strcmp(opened[i], filename) == 0)
			return;
	}
	std::string s("d:\\");//要输入\得\\
	s += filename;
 
	fin = fopen(s.c_str(), "r");
 
	if (fin == NULL) {
		return;
	}
 
	strcpy(opened[cnt], filename);
	cnt++;
 
	printf("%s\n", filename);
	char * newfile;
	while (fgets(line, MAXN, fin)) {
		if (line[strlen(line) - 1] == '\n')//fgets会把回车读进来
			line[strlen(line) - 1] = '\0';
		if (newfile = strstr(line, "#include")) {
 
			char *start = strchr(line, '<');
			char temp[MAXN];
			strcpy(temp, start + 1);
 
			temp[strlen(temp) - 1] = '\0';//去掉结尾的>
 
			process_line(temp);
		}
	}
 
} 
