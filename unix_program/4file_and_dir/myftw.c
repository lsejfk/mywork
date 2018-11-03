#include "apue.h"
#include "myerr.h"
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

#define PATH_MAX_GUESS 1024
//function type that is called for each filename
typedef int Myfunc(const char *,const struct stat *,int);

static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static int dopath(Myfunc *);

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;


char *path_alloc(size_t *sizep){
	char *ptr;
	size_t size;

	if(posix_version == 0){
		posix_version = sysconf(_SC_VERSION);
	}
	if(xsi_version == 0){
		xsi_version = sysconf(_SC_XOPEN_VERSION);
	}

	if(pathmax == 0){
		errno = 0;
		if((pathmax = pathconf("/",_PC_PATH_MAX)) < 0){
			if(errno == 0){
				pathmax = PATH_MAX_GUESS;
			}else{
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		}else{
			pathmax++;
		}
	}

	if((posix_version < 200112L) && (xsi_version < 4)){
		size = pathmax + 1;
	}else{
		size = pathmax;
	}

	if((ptr = malloc(size)) == NULL){
		err_sys("malloc error for pathname");
	}

	if(sizep != NULL){
		*sizep = size;
	}
	return ptr;
}

int main(int argc,char *argv[]){
	int ret;
	clock_t start,end;
	if(argc != 2){
		err_quit("usage: myftw <starting-pathname>");
	}
	start = clock();
	ret = myftw(argv[1],myfunc);
	end = clock();
	printf("time:%f\n",(double)(end - start) / CLOCKS_PER_SEC);

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if(ntot == 0){
		ntot = 1;
	}
	printf("regular files=%7ld,%5.2f %%\n",nreg,nreg*100.0/ntot);
	printf("directories=%7ld,%5.2f %%\n",ndir,ndir*100.0/ntot);
	printf("block special=%7ld,%5.2f %%\n",nblk,nblk*100.0/ntot);
	printf("char special=%7ld,%5.2f %%\n",nchr,nchr*100.0/ntot);
	printf("FIFOs=%7ld,%5.2f %%\n",nfifo,nfifo*100.0/ntot);
	printf("symbolic links=%7ld,%5.2f %%\n",nslink,nslink*100.0/ntot);
	printf("sockets=%7ld,%5.2f %%\n",nsock,nsock*100.0/ntot);
	exit(ret);
}

//Descend through the hierarchy,starting at "pathname".
//The caller's func() is called for every file.

#define FTW_F 1		//file other than directory
#define FTW_D 2		//directory
#define FTW_DNR 3	//directory that can't be read
#define FTW_NS 4	//file that we can't stat

static char *fullpath;	//contains full pathname for every file
static size_t pathlen;

static int myftw(char *pathname,Myfunc *func){
	fullpath = path_alloc(&pathlen);

	if(pathlen <= strlen(pathname)){
		pathlen = strlen(pathname) * 2;
		if((fullpath = realloc(fullpath,pathlen)) == NULL){
			err_sys("realloc failed");
		}
	}
	strcpy(fullpath,pathname);
	return (dopath(func));

}

/*
//Descend through the hierarchy ,starting at "fullpath".
static int dopath(Myfunc *func){
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret,n;

	if(lstat(fullpath,&statbuf) < 0){
		return func(fullpath,&statbuf,FTW_NS);
	}
	if(S_ISDIR(statbuf.st_mode) == 0){
		return func(fullpath,&statbuf,FTW_F);
	}

	//If it's a directory
	if((ret = func(fullpath,&statbuf,FTW_D)) != 0){
		return ret;
	}

	n = strlen(fullpath);
	if(n + NAME_MAX + 2 > pathlen){
		pathlen *= 2;
		if((fullpath = realloc(fullpath,pathlen)) == NULL){
			err_sys("realloc failed");
		}	

	}
	fullpath[n++] = '/';
	fullpath[n] = '\0';
	if((dp = opendir(fullpath)) == NULL){
		return func(fullpath,&statbuf,FTW_DNR);
	}

	while((dirp = readdir(dp)) != NULL){
		if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0){
			continue;
		}
		strcpy(&fullpath[n],dirp->d_name);
		if((ret = dopath(func)) != 0){
			break;
		}

	}//while
	fullpath[n-1] = '\0';
	if(closedir(dp) < 0){
		err_ret("can't close directory %s",fullpath);
	}
	return ret;
}
*/

static int dopath(Myfunc *func){
	struct stat statbuf;
	int ret,n;
	DIR *dirp;
	struct dirent *dp;

	if(lstat(fullpath,&statbuf) < 0){
		return func(fullpath,&statbuf,FTW_NS);
	}
	if(S_ISDIR(statbuf.st_mode) == 0){
		return func(fullpath,&statbuf,FTW_F);
	}
	//It's a directory
	if((ret = func(fullpath,&statbuf,FTW_D)) != 0){
		return ret;
	}
	n = strlen(fullpath);
	if(n + NAME_MAX + 2 > pathlen){
		pathlen *= 2;
		if((fullpath = realloc(fullpath,pathlen)) == NULL){
			err_sys("realloc failed ");
		}
	}
	fullpath[n++] = '/';
	fullpath[n] = '\0';

	if((dirp = opendir(fullpath)) == NULL){
		return func(fullpath,&statbuf,FTW_DNR);
	}
	while((dp = readdir(dirp)) != NULL){
		if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0){
			continue;
		}
		strcpy(&fullpath[n],dp->d_name);
		if((ret = dopath(func)) != 0){
			return ret;
		}
	}
	fullpath[n-1] = '\0';
	if(closedir(dirp) < 0){
		err_ret("can't close directory %s",fullpath);
	}
	return ret;



}

static int myfunc(const char *pathname,const struct stat *statptr,int type){
	switch(type){
		case FTW_F:
			switch(statptr->st_mode & S_IFMT){
				case S_IFREG:nreg++;break;
				case S_IFBLK:nblk++;break;
				case S_IFCHR:nchr++;break;
				case S_IFIFO:nfifo++;break;
				case S_IFLNK:nslink++;break;
				case S_IFSOCK:nsock++;break;
				case S_IFDIR:
					err_dump("for S_IFDIR for %s",pathname);
				
			}
			break;
		case FTW_D:
			ndir++;
			break;
		case FTW_DNR:
			err_ret("can't read directory %s",pathname);
			break;
		case FTW_NS:
			err_ret("stat error for %s",pathname);
			break;
		default:
			err_dump("unknown typw %d for pathname %s",type,pathname);
	}
	return 0;
}



