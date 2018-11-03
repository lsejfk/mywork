#include "apue.h"
#include "myerr.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#define OPT_DEPTH 1	//-d
#define OPT_RECUSE 2	//-r


struct find_option{
	int depth;	//the depth for searching
	char *mode;	//the module for searching
	char *path;	//the path where the work of searching start at
};

typedef int MatchString(const char *,const char *);

void init_find_option(struct find_option *opt);
char *buy_string(char *str);
int match_mode(const char *mode,const char *str);
void get_file_name(char *filename,char *pathname);
void find_mode(int option,struct find_option *opt,int depth,MatchString *match_mode);



int main(int argc,char *argv[]){
	struct find_option opt;
	int i;
	char ch;
	int option;
	int flag = 1;
	option = 0;
	init_find_option(&opt);
	for(i=1;i<argc;i++){
		if(*(argv[i]) == '-'){
			flag = 1;
			while(flag && (ch = *(++(argv[i])))){
				switch(ch){
					case 'd':option |= OPT_DEPTH;
						opt.depth = atoi(argv[++i]);
						if(opt.depth == 0){
							err_quit("usage:a.out -d <depth>");
						}else if(opt.depth < 0){
							err_quit("depth can not be negative");
						}
						flag = 0;
						break;
					case 'r':option |= OPT_RECUSE;break;
					default:err_quit("no such option");
				}//switch ch
			}//while ch
		}else{
			opt.mode = buy_string(argv[i]);
			++i;

			//get the start
			if(i < argc){
				opt.path = buy_string(argv[i]);
				if(opt.path[strlen(opt.path)-1] == '/'){
					opt.path[strlen(opt.path)-1] = '\0';	//erase the slash at end
				}
				break;	//break the loop
			}else{		//find at current path
				opt.path = buy_string("./");
			}
		}//if argv
	}//for
	if(argc == 1){
		err_quit("usage:a.out [-option] <str_mode> <str_path>");
	}

	find_mode(option,&opt,opt.depth,match_mode);
}

void init_find_option(struct find_option *opt){
	opt->depth = 0;
	opt->mode = NULL;
	opt->path = NULL;
}

char *buy_string(char *str){
	char *st;
	if((st = (char *)malloc(sizeof(char) * (strlen(str) + 1))) == NULL){
		err_sys("malloc failed for string %s",str);
	}
	strcpy(st,str);
	return st;
}

void find_mode(int option,struct find_option *opt,int depth,MatchString *match_mode){
	DIR *dp;
	struct dirent *dirp;
	struct stat buf;
	char pathname[PATH_MAX];
	char filename[NAME_MAX];
	int len;
	static int flag = 1;	//The first time
	if(flag){		//the first time
		if(chdir(opt->path) < 0){
			err_sys("chdir error for %s",opt->path);
		}
		if(getcwd(pathname,sizeof(pathname)) == NULL){
			err_sys("getcwd error");
		}
		opt->path = buy_string(pathname);	//get the abstract pathname
		flag = 0;	//more times
	}//if flag

	get_file_name(filename,opt->path);	//get filename from pathname
	if(lstat(opt->path,&buf) < 0){
		err_sys("cannot stat %s",opt->path);
	}
	if(S_ISDIR(buf.st_mode)){		//Is directory
		if((option & OPT_DEPTH) && depth == 0){
				return;
		}
		if(match_mode(opt->mode,filename)){
			printf("%s\n",opt->path);
		}
		len = strlen(opt->path);	//get the length of pathname
		if((dp = opendir(opt->path)) == NULL){
			err_sys("can't open dir %s",opt->path);
		}
		while((dirp = readdir(dp))){
			if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0){
				continue;
			}
			if((opt->path = (char *)realloc(opt->path,sizeof(char) * (len + strlen(dirp->d_name) + 2))) == NULL){
				err_sys("realloc failed for %s",opt->path);
			}
			sprintf(&opt->path[len],"/%s",dirp->d_name);
			find_mode(option,opt,depth-1,match_mode);
			opt->path[len] = '\0';	//erase the / and string at back
		}//while dirp
		if(closedir(dp) < 0){
			err_sys("closedir error");
		}
	}else{
		if(match_mode(opt->mode,filename)){
			printf("%s\n",opt->path);
		}
	}//if S_ISDIR
}


int match_mode(const char *mode,const char *str){
	return (strstr(str,mode) == NULL) ? 0 : 1;
}

void get_file_name(char *filename,char *pathname){
	int len;
	char *str;
	int flag;
	flag = 0;
	len = strlen(pathname);
	if(pathname[len-1] == '/'){
		pathname[len-1] = '\0';
		flag = 1;
	}
	if((str = strrchr(pathname,'/')) == NULL){	//pathname is the filename
		strcpy(filename,pathname);
	}else{
		strcpy(filename,str);
	}
	if(flag == 1){	//add '/' which delete at first
		pathname[len-1] = '/';
		pathname[len] = '\0';
	}
}
