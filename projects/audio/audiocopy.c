#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "audiolib.h"

#define BUFFSIZE 1024
int main(){
     char buffer[BUFFSIZE];
     int byte;

     if(open_audio() == -1){
          fprintf(stderr,"failed open audio device:%s\n",strerror(errno));
          exit(1);
     }

     for(;;){
          byte = read_audio(buffer,BUFFSIZE);
          if(byte < 0){
               break;
          }
          if(write_audio(buffer,byte) < 0){
               break;
          }
     }
     close_audio();
     return 0;
}
