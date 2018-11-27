#ifndef AUDIOLIB_H
#define AUDIOLIB_H

int open_audio(void);
void close_audio(void);
int read_audio(char *buffer,int maxcnt);
int write_audio(char *buffer,int maxcnt);
int get_record_buffer_size(void);
#endif
