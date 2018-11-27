#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(){
     int n,i,my;
     int fd[2];
     char *str = "hello";
     char buf[10];
     if(pipe(fd) < 0){
          fprintf(stderr,"pipe error:%s\n",strerror(errno));
          exit(1);
     }
     if(dup2(fd[1],STDOUT_FILENO) < 0){
          fprintf(stderr,"dup2 error:%s\n",strerror(errno));
          exit(1);
     }
     if(dup2(fd[0],STDIN_FILENO) < 0){
          fprintf(stderr,"dup2 error:%s\n",strerror(errno));
          exit(1);
     }
     close(fd[0]);
     close(fd[1]);
     
     //n = write(STDOUT_FILENO,str,strlen(str));
     //if(n != strlen(str)){
     //     fprintf(stderr,"write error:%s\n",strerror(errno));
     //     exit(1);
     //}

     //if(read(STDIN_FILENO,buf,sizeof(buf)) < 0){
     //     fprintf(stderr,"read error:%s\n",strerror(errno));
     //     exit(1);
     //}
     //fprintf(stderr,"%s\n",buf);

    // for(i=0;i<10;i++){
    //      read(STDIN_FILENO,&my,sizeof(my));
    //      write(STDOUT_FILENO,&i,sizeof(i));
    //      fprintf(stderr,"%d\n",my);
    // }
    for(i=0;i<10;i++){
          printf("%d ",i);
          fflush(stdout);
          scanf("%d",&my);
          fprintf(stderr,"%d\n",my);
    }

     exit(0);
}
