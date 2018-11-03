#include "apue.h"
#include "myerr.h"
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define BUFSIZE 4096 

#ifndef NAME_MAX
#define NAME_MAX 256
#endif

void set_fl(int fd,int flags){		//flags are file status flags to turn on.
	int val;
	if((val = fcntl(fd,F_GETFL,0)) < 0){
		err_sys("fcntl F_GETFL error for fd %d",fd);
	}

	val |= flags;			//turn on the flags
	if(fcntl(fd,F_SETFL,val) < 0){
		err_sys("fcntl F_SETFL error for fd %d",fd);
	}
}


void normal_copy(const char *from,const char *to){	//copy file <from> to <to>
	int fd_from,fd_to,n;
	char filename[NAME_MAX];
	char *p;
	char buf[BUFSIZE];

	//get the filename from string <from>
	if((p = strrchr(from,'/')) == NULL){		//string <from> is filename
		strcpy(filename,from);
	}else{
		strcpy(filename,++p);
	}
	
	//open file
	if((fd_from = open(from,O_RDONLY)) < 0){
		err_sys("open file %s error",from);
	}


	if((fd_to = openat(AT_FDCWD,to,O_RDONLY)) < 0){
		err_sys("openat path %s error",to);
	}
	//creat file with read,write and execute by user mode
	if((fd_to = openat(fd_to,filename,O_RDWR|O_CREAT|O_TRUNC|O_SYNC,S_IRWXU)) < 0){
		err_sys("openat error filename %s,fd %d",filename,fd_to);
	}

	//set_fl(fd_to,O_SYNC);
	while((n = read(fd_from,buf,BUFSIZE)) > 0){
		if(write(fd_to,buf,n) != n){
			err_sys("write error fd %d",fd_to);
		}
	//	fsync(fd_to);
	}

	if(n < 0){
		err_sys("read error fd %d",fd_from);
	}
}

int main(int argc,char *argv[]){
	time_t start,end;
	double diff;
	if(argc != 3){
		err_quit("usage:%s <from> <to>",argv[0]);
	}
	start = time(NULL);		//start time
	normal_copy(argv[1],argv[2]);
	end = time(NULL);
	diff = difftime(end,start);
	printf("success %f\n",diff);
}
