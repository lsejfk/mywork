#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char puzzle[][4] = {
	{'t','h','i','s'},
	{'w','a','t','s'},
	{'o','a','h','g'},
	{'f','g','d','t'}
};

char *dit[4] = {"this","two","fat","that"};

int word_exist(int x,int y,int dir,int len,char *word,int pos[][2]){
	int i;
	i = 0;
	while(i < len){
		if(x < 0 || y < 0 || x >= 4 || y >= 4){
			return 0;
		}
		word[i] = puzzle[x][y];
		pos[i][0] = x;		//Store the x,y scalar
		pos[i][1] = y;
		i++;
		switch(dir){
			case 0:
				x--;
				break;
			case 1:		//north-east
				x--;
				y++;
				break;
			case 2:		//east
				y++;
				break;
			case 3:		//east-south
				y++;
				x++;
				break;
			case 4:		//south
				x++;
				break;
			case 5:		//south-west
				x++;
				y--;
				break;
			case 6:		//west
				y--;
				break;
			case 7:		//north-west
				x--;
				y--;
				break;
			default:
				return 0;
		}//switch dir
	}//while i < len
	word[i] = '\0';
	for(i=0;i<4;i++){
		if(strcmp(word,dit[i]) == 0){
			return 1;
		}
	}
	return 0;
}

void print_word(int pos[][2],char *word){
	int len = strlen(word);
	int i;
	for(i=0;i<len;i++){
		printf("(%d,%d,%c),",pos[i][0],pos[i][1],word[i]);
	}
	printf("%s\n",word);
}

int main(){
	int x,y,len,dir;
	char word[5];
	int pos[4][2];
	for(x=0;x<4;x++){
		for(y=0;y<4;y++){
			for(dir=0;dir<8;dir++){		//8 directions
				for(len=3;len<5;len++){
					if(word_exist(x,y,dir,len,word,pos)){
						print_word(pos,word);
					}
				}
			}
		}
	}
	return 0;
}
