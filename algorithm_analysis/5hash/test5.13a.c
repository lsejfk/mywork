#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashquad.h"

char puzzle[][4] = {
	{'t','h','i','s'},
	{'w','a','t','s'},
	{'o','a','h','g'},
	{'f','g','d','t'}
};

char *getword(int x,int y,int dir,int len,char *word){
	int i;
	i = 0;
	if(x < 0 || y < 0 || x > 3 || y > 3){
		word[0] = '\0';
		return NULL;
	}
	word[i++] = puzzle[x][y];
	while(i < len){
		if(x < 0 || y < 0 || x > 3 || y > 3){
			word[0] = '\0';
			return NULL;
		}
		switch(dir){
			case 0:	//north
				x--;
				break;
			case 1:	//north-east
				x--;
				y++;
				break;
			case 2:	//east
				y++;
				break;
			case 3:	//east-south
				x++;
				y++;
				break;
			case 4:	//south
				x++;
				break;
			case 5:	//south-west
				y--;
				x++;
				break;
			case 6:	//west
				y--;
				break;
			case 7:	//west-north
				y--;
				x--;
				break;
			default:
				return NULL;
		}//switch
		word[i++] = puzzle[x][y];
	}//while
	word[i] = '\0';
	return word;
}

int main(){
	char word[32];
	int i,j,len,dir,pos;
	HashTQ H;
	H = hashtq_initializeTable(100);
	while(scanf("%s",word) != EOF){
		int k;
		k = strlen(word);
		hashtq_insert(word,Legal,H);
		while(k > 1){
			word[--k] = '\0';
			hashtq_insert(word,Prefix,H);
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			for(dir=0;dir<8;dir++){
				for(len=1;len<= 11;len++){
					getword(i,j,dir,len,word);
					pos = hashtq_find(word,H);
					if(hashtq_getstatus(pos,H) == Legal){
						printf("res:%s\n",word);
						continue;
					}
					
					if(hashtq_getstatus(pos,H) != Prefix){
						break;
					}
				}//for len
			}//for dir
		}//for j
	}//for i
	return 0;
}
