#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 5

typedef struct info{
	char name[20];
	char phone[20];
	char ctgr[20];
	char time [20];
}T_Record;

void info_init(); //모든 레코드 제거
int info_is_available(); // 새로운 데이터를 추가할 수 있는 공간이 있는지 확인
int info_first_available(); //추가 가능한 가장 빠른 포인터 인덱스 찾기
int info_count(); // 현재까지 저장되어 있는 음식점의 수 확인
void info_create(char* n, char* ph, char* c, char* t); //신규 음식점 정보 추가
T_Record* info_search_by_name(char* n); //음식점 이름이 일치하는 포인터 찾기
void info_update(T_Record* p, char* ph, char* c, char* t); // 특정 음식점 정보 업데이트
void info_delete(T_Record* p); // 특정 음식점 정보 삭제
void info_gets_all(T_Record* a[]); //정보가 들어있는 모든 record pointer 배열찾기
void info_gets_all2(T_Record* a[]); // 모든 레코드 포인터의 배열을 만들기 (for debug)
char* info_to_string(T_Record* p); // 특정 음식점의 정보 문자열로 가져오기
char* info_getname(T_Record* p);
char* info_getphone(T_Record* p);
char* info_getctgr(T_Record* p);
char* info_gettime(T_Record* p);
int info_get_all_by_name(T_Record* a[], char* n);
int info_get_all_by_ctgr(T_Record* a[], char* n);
int info_get_all_by_time(T_Record* a[], char* n);
char* info_to_string_save(T_Record* p); // 특정 회원 레코드의 내용을 파일저장용 문자열로 가져오기
