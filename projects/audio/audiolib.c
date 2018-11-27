#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stropts.h>
#include <unistd.h>
#include <sys/ioctl.h>
//#include <sys/audio.h>
#include <sys/soundcard.h>
#define AUDIO "/dev/audio"

static int audio_fd = -1;

int open_audio(void){
     while(((audio_fd = open(AUDIO,O_RDWR)) == -1) && (errno == EINTR))
          ;
     if(audio_fd == -1){
          return -1;
     }
     return 0;
}

void close_audio(void){
     if(close(audio_fd) < 0){
          fprintf(stderr,"close audio error\n");
          exit(1);
     }
     audio_fd = -1;
}

int read_audio(char *buffer,int maxcnt){
     int n;
     n = read(audio_fd,buffer,maxcnt);
     if(n < 0){
          fprintf(stderr,"read_audio:read error %s\n",strerror(errno));
          exit(1);
     }
     return n;
}

int write_audio(char *buffer,int maxcnt){
     int n;
     n = write(audio_fd,buffer,maxcnt);
     if(n < 0){
          fprintf(stderr,"write_audio:write error-%s\n",strerror(errno));
          exit(1);
     }
     return n;
}

/*
int get_record_buffer_size(void){
     audio_info_t myaudio;
     if(audio_fd == -1){
          return -1;
     }
     if(ioctl(audio_fd,AUDIO_GETINFO,&myaudio) == -1){
          return -1;
     }else{
          return myaudio.record.buffer_size;
     }
}
*/
