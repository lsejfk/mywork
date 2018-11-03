#include "apue.h"
#include "myerr.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/time.h>

#define OPT_LIST 1	//parameter with -l,list the detail of file
#define OPT_ALL 2	//parameter with -a,list all of the file and director
#define OPT_DIR 4 


struct file_info {
	char filetype;	//- regular,d-directory,b-block special file,c-character,f-FIFO,s-socket,l-symbolic link
	char file_permission[10];	//file access permission.rwxrwxrwx
	char *user;			//file owner
	char *group;			//group of file
	size_t filesize;		//size of file in byte
	char *atime;			//last access time
	char *mtime;			//last modify time
	char *ctime;			//last change time
	char *filename;			//filename
};


void init_file(struct file_info *file);
void clear_file(struct file_info *file);
void get_file_info(char *pathname,struct file_info *file);
void print_file(struct file_info *file);

int main(int argc,char *argv[]){
	int option,i;
	DIR *dp;
	char ch;
	struct dirent *dirp;
	struct file_info file;
	char filename[PATH_MAX];

	option = 0;
	init_file(&file);
	filename[0] = '\0';
	for(i=1;i<argc;i++){
		if(*argv[i] == '-'){
			while((ch = *(++(argv[i]))) != '\0'){
				switch(ch){
					case 'a':option |= OPT_ALL;break;
					case 'l':option |= OPT_LIST;break;
					case 'd':option |= OPT_DIR;break;
					default:err_quit("usage:a.out [-ald] <filename>");
				}//switch
			}//while
		}else{	//file
			strcpy(filename,argv[i]);
		}
	}//for


	if(argc == 1){	//no parameter or no filename
		if((dp = opendir("./")) == NULL){
			err_sys("opendir error when open ./");
		}
		while((dirp = readdir(dp)) != NULL){
			if(strcmp(dirp->d_name,".") != 0 && strcmp(dirp->d_name,"..") != 0){
				printf("%s\n",dirp->d_name);
			}
		}
	}else{
		if(strlen(filename) == 0){
			strcpy(filename,".");
		}
		get_file_info(filename,&file);		//get file information
		if(file.filetype == 'd'){	//not directory
			if(chdir(filename) < 0){		//change current directory
				err_sys("chdir error with %s",filename);
			}
			if((dp = opendir(filename)) == NULL){
				err_sys("opendir error for open %s",filename);
			}
			if(option & OPT_DIR){	//print the current directory
				if(option & OPT_LIST){
					print_file(&file);				//print file information
				}else{
					printf("%s\n",file.filename);
				}
			}//if
			while((dirp = readdir(dp)) != NULL){
				/*
				if(lstat(dirp->d_name,&buf) < 0){
					err_sys("lstat error for %s",dirp->d_name);
				}
				*/
				get_file_info(dirp->d_name,&file);
				if(strcmp(file.filename,".") == 0 || strcmp(file.filename,"..") == 0){
					if(option & OPT_ALL){	//print . and ..
						if(option & OPT_LIST){
							print_file(&file);	
						}else{
							printf("%s\n",file.filename);
						}
					}//if option
				}else{
					if(option & OPT_LIST){
						print_file(&file);
					}else{
						printf("%s\n",file.filename);
					}
				}
			}//while dirp
			if(closedir(dp) < 0){
				err_sys("cannot close dir %s",filename);
			}

		}else{
			if(option & OPT_LIST){
				print_file(&file);
			}else{
				printf("%s\n",file.filename);
			}
		}//if file.filetype
	}//if argc
}


//get file information
void get_file_info(char *pathname,struct file_info *file){
	struct stat buf;
	char *access,*first;
	char *str;
	struct group *grp;
	struct passwd *usr;
	char str_time[64];
	int len;
	if((access = (char *)calloc(10,sizeof(char))) == NULL){
		err_sys("calloc failed");
	}
	first = access;
	clear_file(file);	//clean the file object 
	if(lstat(pathname,&buf) < 0){
		err_sys("lstat error for %s",pathname);
	}
	//get the file type
	if(S_ISREG(buf.st_mode)){	//regular file
		file->filetype = '-';
	}else if(S_ISDIR(buf.st_mode)){
		file->filetype = 'd';
	}else if(S_ISCHR(buf.st_mode)){
		file->filetype = 'c';
	}else if(S_ISBLK(buf.st_mode)){
		file->filetype = 'b';
	}else if(S_ISFIFO(buf.st_mode)){
		file->filetype = 'f';
	}else if(S_ISLNK(buf.st_mode)){
		file->filetype = 'l';
	}else if(S_ISSOCK(buf.st_mode)){
		file->filetype = 's';
	}else{
		err_sys("unknow file type");
	}
	//get the access permission
	*(access++) = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	*(access++) = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	if(buf.st_mode & S_ISUID){
		*(access++) = 's';
	}else if(buf.st_mode & S_IXUSR){
		*(access++) = 'x';
	}else{
		*(access++) = '-';
	}

	*(access++) = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	*(access++) = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	if(buf.st_mode & S_ISGID){
		*(access++) = 's';
	}else if(buf.st_mode & S_IXGRP){
		*(access++) = 'x';
	}else{
		*(access++) = '-';
	}

	*(access++) = (buf.st_mode & S_IROTH) ? 'r' : '-';
	*(access++) = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	*(access++) = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	*access = '\0';
	strcpy(file->file_permission,first);

	//get the user name and group name
	usr = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	len = strlen(usr->pw_name);
	file->user = (char *)malloc(sizeof(char) * (len + 1));
	len = strlen(grp->gr_name);
	file->group = (char *)malloc(sizeof(char) * (len + 1));
	if(file->user == NULL || file->group == NULL){
		err_sys("malloc failed");
	}
	strcpy(file->user,usr->pw_name);
	strcpy(file->group,grp->gr_name);

	//get the size of file
	file->filesize = buf.st_size;
	
	//get the time of file
	strftime(str_time,sizeof(str_time),"%Y-%m-%d %H:%M:%S",localtime(&buf.st_atim.tv_sec));
	len = strlen(str_time);
	if((file->atime = (char *)malloc(sizeof(char)*(len + 1))) == NULL){
		err_sys("malloc failed for atime");
	}
	strcpy(file->atime,str_time);

	strftime(str_time,sizeof(str_time),"%Y-%m-%d %H:%M:%S",localtime(&buf.st_mtim.tv_sec));
	len = strlen(str_time);
	if((file->mtime = (char *)malloc(sizeof(char) * (len + 1))) == NULL){
		err_sys("malloc failed for mtime");
	}
	strcpy(file->mtime,str_time);

	strftime(str_time,sizeof(str_time),"%Y-%m-%d %H:%M:%S",localtime(&buf.st_ctim.tv_sec));
	len = strlen(str_time);
	if((file->ctime = (char *)malloc(sizeof(char) * (len + 1))) == NULL){
		err_sys("malloc failed for ctime");
	}
	strcpy(file->ctime,str_time);

	//get file name
	if(pathname[strlen(pathname)-1] == '/'){	//trim the last /
		pathname[strlen(pathname)-1] = '\0';
	}
	str = strrchr(pathname,'/');	//get the file name
	if(str == NULL){	//the pathname is the file name
		str = pathname;
	}
	len = strlen(str);
	if((file->filename = (char *)malloc(sizeof(char) * (len + 1))) == NULL){
		err_sys("malloc failed for filename");
	}
	strcpy(file->filename,str);
}

void clear_file(struct file_info *file){
	file->filetype = '-';
	file->file_permission[0] = '\0';
	if(file->user != NULL){
		free(file->user);
		file->user = NULL;
	}
	if(file->group != NULL){
		free(file->group);
		file->group = NULL;
	}
	file->filesize = 0;
	if(file->atime != NULL){
		free(file->atime);
		file->atime = NULL;
	}
	if(file->mtime != NULL){
		free(file->mtime);
		file->mtime = NULL;
	}
	if(file->ctime != NULL){
		free(file->ctime);
		file->ctime = NULL;
	}
	if(file->filename != NULL){
		free(file->filename);
		file->filename = NULL;
	}
}

void init_file(struct file_info *file){
	file->filetype = '-';
	file->file_permission[0] = '\0';
	file->user = NULL;
	file->group = NULL;
	file->filesize = 0;
	file->atime = NULL;
	file->mtime = NULL;
	file->ctime = NULL;
	file->filename = NULL;
}

void print_file(struct file_info *file){
	printf("%c%s %s %s %6ld %s %s\n",file->filetype,file->file_permission,file->user,file->group,file->filesize,
		file->atime,file->filename);
}
