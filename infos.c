#include "infos.h"

T_Record* infos[MAX_MEMBERS]; // 음식점 정보 데이터
int _count = 0;

int info_is_available(){
	int i;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]==NULL){
			#ifdef DEBUG
				printf("%d spaces are empty\n",MAX_MEMBERS-i);
			#endif
			return 1;
		}
	return 0;
}

int info_first_available(){
	int i;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]==NULL){
			#ifdef DEBUG
				printf("%dth space is used for first available space\n",i+1);
			#endif
			return i;
		}
	return -1;
}

int info_count(){
 return _count;
}

void info_create(char* n, char* ph, char* c, char* t){
	int index = info_first_available();
	infos[index] = (T_Record*)malloc(sizeof(T_Record));
	T_Record* p = infos[index];
	strcpy(p->name, n);
	strcpy(p->phone, ph);
	strcpy(p->ctgr, c);
	strcpy(p->time, t);
	_count++;
#ifdef DEBUG
	printf("%d record is created!\n", info_count());
#endif
}

T_Record* info_search_by_name(char* n){
	int i;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]!=NULL && strcmp(infos[i]->name, n)==0){
			#ifdef DEBUG
				printf("Searching the %s clear\n", infos[i]->name);
			#endif
			return infos[i];
		}
	return NULL;
}

void info_update(T_Record* p, char* ph, char* c, char* t){
	strcpy(p->phone, ph);
	strcpy(p->ctgr, c);
	strcpy(p->time, t);
	#ifdef DEBUG
		printf("Phone: %s..updated clear\n", p->phone);
		printf("Category: %s..updated clear\n", p->ctgr);
		printf("Time: %s..updated clear\n", p->time);
	#endif
}

void info_delete(T_Record* p){
	int i, index;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]==p){
			index=i;
			break;
		}
	free(p);
	infos[index] = NULL;
	_count--;

	for(i=index+1; i<MAX_MEMBERS; i++)
		infos[i-1] = infos[i];
}

char* info_to_string(T_Record* p){
	static char str[100];
	sprintf(str, "[%s] %s / %s / call: %s", p->name, p->ctgr, p->time, p->phone);
	#ifdef DEBUG
		printf("struct info is changed like %s\n", str);
	#endif
	return str;
}

void info_gets_all(T_Record* a[]){
	int i, c=0;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]!=NULL){
			a[c] = infos[i];
			c++;
		}
	#ifdef DEBUG
		printf("we got %c infos!\n", c);
	#endif
}

int info_get_all_by_name(T_Record* a[], char* n){
	int i, c=0;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]!=NULL && strstr(infos[i]->name,n)){
			a[c]=infos[i];
			c++;
		}
	return c;
}

int info_get_all_by_ctgr(T_Record* a[], char* n){
	int i, c=0;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]!=NULL && (strcmp(infos[i]->ctgr, n)==0)){
			a[c] = infos[i];
			c++;
		}
	#ifdef DEBUG
		printf("We got %d infos\n", c);
	#endif
	return c;
}

int info_get_all_by_time(T_Record* a[], char* n){
	int i, c=0;
	for(i=0; i<MAX_MEMBERS; i++)
		if(infos[i]!=NULL && (strcmp(infos[i]->time, n)==0)){
			a[c] = infos[i];
			c++;
		}
	#ifdef DEBUG
		printf("We Got %d infos\n", c);
	#endif
	return c;
}

void info_init(){
	int i;
	for(i=0; i<MAX_MEMBERS; i++){
		if(infos[i]!=NULL){
			free(infos[i]);
		}
		infos[i] = NULL;
	}
	_count = 0;
}

char* info_to_string_save(T_Record* p){
	static char str[100];
	sprintf(str, "%s %s %s %s", p->name, p->phone, p->ctgr, p->time);
	#ifdef DEBUG
		printf("%s is saved clear\n", p->name);
	#endif
	return str;
}














