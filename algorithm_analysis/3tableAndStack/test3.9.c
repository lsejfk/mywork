#include <stdio.h>
#include <string.h>
#include "myerr.h"
#include <stdlib.h>

struct Interger{
	int exp;
	int num;
	struct Interger *next;
	struct Interger *front;
};

struct IntPage{
	struct Interger *head;
	struct Interger *rear;
};

void print(struct IntPage *pag);
void addInterger(const char *num1,const char *num2,struct IntPage *res);
void creatIntPage(struct IntPage *pag);
void chToInt(const char *str,struct IntPage *pag);
void print_int(struct IntPage *pag);
void adjustInt(struct IntPage *pag);
void subInterger(const char *num1,const char *num2,struct IntPage *res);
void rmSub(struct IntPage *pag);
void multiInterger(const char *num1,const char *num2,struct IntPage *res);

int main(int argc,char *argv[]){
	struct IntPage res,res1,res2;
	char *strnum1 = argv[1];
	char *strnum2 = argv[2];
	creatIntPage(&res);
	creatIntPage(&res1);
	creatIntPage(&res2);
	addInterger(strnum1,strnum2,&res);
	printf("%s\n%s\n",strnum1,strnum2);
	print_int(&res);
	printf("\nsub:\n");
	subInterger(strnum1,strnum2,&res1);
	print_int(&res1);
	printf("mult\n");
	multiInterger(strnum1,strnum2,&res2);
	print(&res2);
	print_int(&res2);
	return 0;
}



void creatIntPage(struct IntPage *pag){
	struct Interger *p,*q;
	p = (struct Interger *)malloc(sizeof(struct Interger));
	q = (struct Interger *)malloc(sizeof(struct Interger));
	
	if(p == NULL || q == NULL){
		err_sys("malloc failed");
	}
	p->next = q;
	p->front = NULL;
	p->num = 0;		//default positive number
	q->next = NULL;
	q->front = p;
	pag->head = p;
	pag->rear = q;
}

void chToInt(const char *str,struct IntPage *pag){
	int i,len,exp;
	struct Interger *s,*p;
	len = strlen(str);
	exp = 0;
	p = pag->rear;
	if(str[0] == '-'){
		pag->head->num = 1;	//negative number
	}else{
		pag->head->num = 0;
	}
	for(i=len-1;i>=0;i--,exp++){
		if(str[i] < '0' || str[i] > '9'){
			return;
		}
		if(str[i] == '0'){
			continue;
		}
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		s->exp = exp;
		s->num = str[i] - '0';	//char to int
		if(pag->head->num){
			s->num *= -1;
		}
		
		s->front = p->front;
		s->next = p;
		p->front->next = s;
		p->front = s;
		p = s;

	}
}


//add
void addInterger(const char *num1,const char *num2,struct IntPage *res){
	struct IntPage pnum1,pnum2;
	struct Interger *intNum1,*intNum2;
	struct Interger *p,*q,*s,*ptr,*k;
	creatIntPage(&pnum1);
	creatIntPage(&pnum2);
	chToInt(num1,&pnum1);
	chToInt(num2,&pnum2);

	intNum1 = pnum1.rear;
	intNum2 = pnum2.rear;
	//do add option
	for(p=intNum1->front,q=intNum2->front;p != pnum1.head && q != pnum2.head;){	
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}

		if(p->exp > q->exp){
			s->exp = q->exp;
			s->num = q->num;
			s->next = NULL;
			s->front = NULL;
			q = q->front;
		}else if(p->exp == q->exp){
			s->num = p->num + q->num;
			s->exp = p->exp;
			s->next = NULL;
			s->front = NULL;
			p = p->front;
			q = q->front;
		}else{
			s->exp = p->exp;
			s->num = p->num;
			s->next = NULL;
			s->front = NULL;
			p = p->front;
		}

		//find the location for inserting s node
		for(ptr=res->rear;ptr->front != res->head && ptr->front->exp < s->exp;ptr=ptr->front)
			;
		if(ptr->front == res->head || ptr->front->exp > s->exp){
			s->next = ptr;
			s->front = ptr->front;
			ptr->front->next = s;
			ptr->front = s;
		}else{
			ptr->front->num += s->num;
		}
	}//for
	while(p != pnum1.head){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		s->exp = p->exp;
		s->num = p->num;
		p = p->front;
		for(ptr=res->rear;ptr->front != res->head && ptr->front->exp < s->exp;ptr=ptr->front)
			;
		if(ptr->front == res->head || ptr->front->exp > s->exp){
			s->next = ptr;
			s->front = ptr->front;
			ptr->front->next = s;
			ptr->front = s;
		}else{
			ptr->front->num += s->num;
		}
	}//while

	while(q != pnum2.head){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		s->exp = q->exp;
		s->num = q->num;
		q = q->front;
		for(ptr=res->rear;ptr->front != res->head && ptr->front->exp < s->exp;ptr=ptr->front)
			;
		if(ptr->front == res->head || ptr->front->exp > s->exp){
			s->next = ptr;
			s->front = ptr->front;
			ptr->front->next = s;
			ptr->front = s;
		}else{
			ptr->front->num += s->num;
		}
	}//while

	rmSub(res);
	adjustInt(res);
}

void adjustInt(struct IntPage *pag){
	struct Interger *p,*q,*s;
	int flag;
	flag = 0;
	for(p=pag->rear->front;p != pag->head;p=p->front){
		flag = 0;
		if(p->num == 0){
			q = p;
			p->front->next = p->next;
			p->next->front = p->front;
			p = p->next;
			free(q);
			continue;
		}
		if(p->num >= 10){
			flag = p->num / 10;
			p->num = p->num % 10;
		
			if(p->exp + 1  == p->front->exp){
				p->front->num += flag;
			}else if(p->exp + 1 < p->front->exp){
				s = (struct Interger *)malloc(sizeof(struct Interger));
				if(s == NULL){
					err_sys("malloc failed");
				}
				s->num = flag;
				s->exp = p->exp + 1;
				s->next = p;
				s->front = p->front;
				p->front->next = s;
				p->front = s;
			}//if
		}
	}//for
	if(p == pag->head && flag > 0){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		s->num = flag;
		s->exp = p->next->exp + 1;
		s->next = p->next;
		s->front = p;
		p->next->front = s;
		p->next = s;
	}
}


void print(struct IntPage *pag){
	struct Interger *p;
	for(p=pag->head->next;p!=pag->rear;p=p->next){
		printf("%d*10^%d + ",p->num,p->exp);
	}
	printf("0\n");
}

void print_int(struct IntPage *pag){
	struct Interger *p;
	int i;
	if(pag->head->num){	//negative number
		printf("-");
	}
	for(p=pag->head->next;p!=pag->rear;p=p->next){
		printf("%d",p->num);
		if(p->next == pag->rear){
			for(i=p->exp-1;i>=0;i--){
				printf("0");
			}

		}else{
			for(i=p->exp-1;i>p->next->exp;i--){
				printf("0");
			}
		}
	}
	printf("\n");
}

void subInterger(const char *num1,const char *num2,struct IntPage *res){
	struct IntPage pnum1,pnum2;
	struct Interger *intNum1,*intNum2;
	struct Interger *p,*q,*s,*ptr,*k;
	creatIntPage(&pnum1);
	creatIntPage(&pnum2);
	chToInt(num1,&pnum1);
	chToInt(num2,&pnum2);

	intNum1 = pnum1.rear;
	intNum2 = pnum2.rear;
	ptr = res->rear;
	for(p=intNum1->front,q=intNum2->front;p!=pnum1.head && q!=pnum2.head;){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		if(p->exp == q->exp){
			if(p->num - q->num == 0){
				free(s);
				p = p->front;
				q = q->front;
				continue;
			}else{
				s->exp = p->exp;
				s->num = p->num - q->num;
				p = p->front;
				q = q->front;
			}
		}else if(p->exp > q->exp){
			s->num = (-1) * q->num;
			s->exp = q->exp;
			q = q->front;
		}else{
			s->num = p->num;
			s->exp = p->exp;
			p = p->front;
		}

		s->front = ptr->front;
		s->next = ptr;
		ptr->front->next = s;
		ptr->front = s;
		ptr = s;
	}

	while(p != pnum1.head){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		s->num = p->num;
		s->exp = p->exp;

		s->front = ptr->front;
		s->next = ptr;
		ptr->front->next = s;
		ptr->front = s;
		ptr = s;
		p = p->front;
	}
	while(q != pnum2.head){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		s->num = (-1) * q->num;
		s->exp = q->exp;

		s->front = ptr->front;
		s->next = ptr;
		ptr->front->next = s;
		ptr->front = s;
		ptr = s;
		q = q->front;
	}

	rmSub(res);
}

void rmSub(struct IntPage *pag){
	struct Interger *p,*q,*s;
	p = pag->head->next;
	if(p->num < 0){
		for(p=pag->head->next;p != pag->rear;p=p->next){
			p->num *= -1;
		}
		pag->head->num = 1;	//negative
	}//if

	for(p=pag->rear->front;p != pag->head;){
		if(p->num < 0){
			p->num += 10;
			if(p->exp + 1 == p->front->exp){
				p->front->num--;
			}else{
				s = (struct Interger *)malloc(sizeof(struct Interger));
				if(s == NULL){
					err_sys("malloc failed");
				}
				s->num = -1;
				s->exp = p->exp + 1;

				s->front = p->front;
				s->next = p;
				p->front->next = s;
				p->front = s;
			}
			p = p->front;
		}else if(p->num == 0){
			q = p;
			q->next->front = q->front;
			q->front->next = q->next;
			p = p->front;
			free(q);

		}else{
			p = p->front;
		}
	}
}


//multiplication
void multiInterger(const char *num1,const char *num2,struct IntPage *res){ 
	struct IntPage pnum1,pnum2;
	struct Interger *intNum1,*intNum2;
	struct Interger *p,*q,*s,*ptr,*k;
	creatIntPage(&pnum1);
	creatIntPage(&pnum2);
	chToInt(num1,&pnum1);
	chToInt(num2,&pnum2);

	intNum1 = pnum1.head;
	intNum2 = pnum2.head;

	for(p=intNum1->next;p!=pnum1.rear;p=p->next){
		for(q=intNum2->next;q!=pnum2.rear;q=q->next){
			s = (struct Interger *)malloc(sizeof(struct Interger));
			if(s == NULL){
				err_sys("malloc failed");
			}
			s->num = p->num * q->num;
			s->exp = p->exp + q->exp;

			for(k=res->head;k->next!=res->rear && k->next->exp > s->exp;k=k->next)
				;
			if(k->next == res->rear){
				s->next = k->next;
				s->front = k;
				k->next->front = s;
				k->next = s;
			}else if(k->next->exp == s->exp){
				k->next->num += s->num;
				if(k->next->num == 0){
					ptr = k->next;
					ptr->next->front = k;
					k->next = ptr->next;
					free(ptr);
				}
				free(s);
			}else{
				s->next = k->next;
				s->front = k;
				k->next->front = s;
				k->next = s;
			}
		}//for
	}//for
	rmSub(res);
	adjustInt(res);
}



/*

//add
void addInterger(const char *num1,const char *num2,struct IntPage *res){
	struct IntPage pnum1,pnum2;
	struct Interger *intNum1,*intNum2;
	struct Interger *p,*q,*s,*ptr,*k;
	creatIntPage(&pnum1);
	creatIntPage(&pnum2);
	chToInt(num1,&pnum1);
	chToInt(num2,&pnum2);

	intNum1 = pnum1.rear;
	intNum2 = pnum2.rear;

	for(p=intNum1->front,q=intNum2->front;q && p;){
		s = (struct Interger *)malloc(sizeof(struct Interger));
		if(s == NULL){
			err_sys("malloc failed");
		}
		if(p->exp > q->exp){
			s->exp = q->exp;
			s->num = q->num;
			s->next = NULL;
			s->front = NULL;
			q = q->front;
		}else if(p->exp == q->exp){
			s->num = p->num + q->num;
			s->exp = p->exp;
			s->next = NULL;
			s->front = NULL;
			p = p->front;
			q = q->front;
		}else{
			s->exp = p->exp;
			s->num = p->num;
			s->next = NULL;
			s->front = NULL;
			p = p->front;
		}
		//find the location for inserting node s
		for(ptr=res->rear;ptr->front != res->head && ptr->front->exp < s->exp;ptr=ptr->front)
			;
		if(s->num >= 10){
			if(ptr->front == res->head){
				k = (struct Interger *)malloc(sizeof(struct Interger));
				if(k == NULL){
					err_sys("malloc failed");
				}
				k->exp = s->exp + 1;
				k->num = 1;
				s->num -= 10;

				s->next = ptr;
				s->front = k;
				k->next = s;
				k->front = ptr->front;
				ptr->front->next = k;
				ptr->front = s;
			}else if(ptr->front->exp == s->exp){
				tmp = ptr->front->num + s->num;
				ptr->front->num = tmp % 10;
				tmp /= 10;
				for(m=ptr->front->front,i=s->exp+1;m != res->head && tmp > 0;m=m->front,i++){
					if(m->exp == i){		//
						if(m->num + tmp < 10){
							m->num += tmp;
							tmp = 0;
							break;
						}else{
							m->num = (m->num + tmp) % 10;
							tmp /= 10;
						}
					}else if(m->exp > i){
						k = (struct Interger *)malloc(sizeof(struct Interger));
						if(k == NULL){
							err_sys("malloc failed");
						}
						k->exp = i;
						k->num = tmp;
						tmp = 0;

						k->front = m;
						k->next = m->next;
						m->next->front  = k;
						m->next = k;
						break;
					}else{
						err_sys("error");
					}
				}
				if(m == res->head && tmp > 0){
					k = (struct Interger *)malloc(sizeof(struct Interger));
					if(k == NULL){
						err_sys("malloc failed");
					}
					k->exp = i;
					k->num = tmp;

					k->front = res->head;
					k->next = res->head->next;
					res->head->next->front = k;
					res->head->next = k;
				}
			}else{
				
			}
		}	
		if(ptr->next == NULL){
			
		}
	}
	
}
*/
