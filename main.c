#include "infos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create();
void read_all();
void update();
void delete();
void delete_con();
void delete_all();
void search_name();
void search_time();
void search_ctgr();
void load_file();
void save_file();

int main(){
	info_init();
	int menu;
	
	while(1){
		printf("\nMENU : 1.Create 2.Read 3.Update 4.Delete 5.Search(name) 6.Search(time) 7.Search(ctgr) 8.Delete(condition) 9.Delete(all) 10.Load 11.Save 0.Quit > ");
		scanf("%d", &menu);
		printf("\n");

		switch(menu){
		case 1:
			create();
			break;
		case 2:
			read_all();
			break;
		case 3:
			update();
			break;
		case 4:
			delete();
			break;
		case 5:
			search_name();
			break;
		case 6:
			search_time();
			break;
		case 7:
			search_ctgr();
			break;
		case 8:
			delete_con();
			break;
		case 9:
			delete_all();
			break;
		case 10:
			load_file();
			break;
		case 11:
			save_file();
			break;
		case 0:
		default:
			return 0;
		}
	}
	
	return 0;
}

void create(){
	if(!info_is_available()){
		printf("There is no space!\n");
		return;
	}
	char name[50], phone[20], ctgr[20], time[20];
	printf("Enter a new info.\n");
	printf("NAME > ");
	scanf("%s", name);
	if(info_search_by_name(name)){
		printf("Duplicated name!\n");
		return;
	}
	printf("PHONE > ");
	scanf("%s", phone);
	printf("Category > ");
	scanf("%s", ctgr);
	printf("TIME(빠름/보통/느림) > ");
	scanf("%s", time);
	info_create(name, phone, ctgr, time);
	
	printf("The information is created:)\n");
}

void read_all(){	
	int size = info_count();
	if(size==0)
		printf("There is no information available:(\n");
	else{
		printf("Here is all restaurants' information>>\n");
		T_Record* records[MAX_MEMBERS];
		info_gets_all(records);
		for(int i=0; i<size; i++){
			T_Record* p = records[i];
			printf("%d. %s\n", i+1, info_to_string(p));
		}
	}
}	

void update(){
	char name[50], phone[20], ctgr[20], time[20];
	printf("Enter a name > ");
	scanf("%s", name);

	T_Record* p = info_search_by_name(name);
	if(p){
		printf("Enter a updated info.\n");
		printf("Phone > ");
		scanf("%s", phone);
		printf("Category > ");
		scanf("%s", ctgr);
		printf("Time(빠름/보통/느림) > ");
		scanf("%s", time);

		info_update(p, phone, ctgr, time);
		printf("The information is updated:)\n");
	}
	else
		printf("NO SUCH RESTAURANT!\n");
}

void delete(){
	char name[50];
	printf("Enter a name > ");
	scanf("%s", name);

	T_Record* p = info_search_by_name(name);
	if(p) {
		info_delete(p);
		printf("The restaurant is deleted!\n");
	}
	else
		printf("NO SUCH RESTAURANT!\n");
}

void delete_con(){
	int con;
	printf("\n Condition : 1.Category 2.Time 3.Quit > ");
	scanf("%d", &con);
	printf("\n");
	char ctgr[20], time[20];
	T_Record* records1[MAX_MEMBERS];
	T_Record* records2[MAX_MEMBERS];

	if(con == 1){
		printf("Enter a category > ");
		scanf("%s", ctgr);

		int size1 = info_get_all_by_ctgr(records1, ctgr);

		if(size1 > 0){
			for(int i=0; i<size1; i++){
				T_Record* p = records1[i];
				info_delete(p);
			}
			printf("Delete all %s succesed!\n", ctgr);
		}
		else
			printf("There is no %s restaurant:(\n", ctgr);
			
	}
	else if(con == 2){
		printf("enter a time(빠름/보통/느림) > ");
		scanf("%s", time);

		int size2 = info_get_all_by_time(records2, time);
		
		if(size2 > 0){
			for(int i=0; i<size2; i++){
				T_Record* p = records2[i];
				info_delete(p);
			}
			printf("Delete all %s succesed!\n", time);
		}
		else
			printf("There is no %s time restaurant:(\n", time);
			
	}
	else
		printf("Go back to menu.\n");	

}


void delete_all(){
	info_init();
	printf("CLEAR ALL THINGS\n");
}

void search_name(){
	char name[50];
	printf("Enter a name > ");
	scanf("%s", name);
	
	T_Record* p = info_search_by_name(name);
	
	if(p) 
		printf("SEARCHING INFO:\n%s\n", info_to_string(p));
	else
		printf("NO SUCH RESTAURANT!\n");
}

void search_time(){
	char time[20];
	printf("Enter a time(빠름/보통/느림) > ");
	scanf("%s", time);

	T_Record* records[MAX_MEMBERS];
	int size = info_get_all_by_time(records, time);
	if( size > 0 ){
		for(int i =0; i<size; i++){
			T_Record* p = records[i];
			printf("%d. %s\n", i+1,info_to_string(p));
		}
	}
	else
		printf("There is no %s time restaurant:(\n", time);
		
}

void search_ctgr(){
	char ctgr[20];
	printf("Enter a category > ");
	scanf("%s", ctgr);

	T_Record* records[MAX_MEMBERS];
	int size = info_get_all_by_ctgr(records, ctgr);
	if( size > 0){
		for(int i=0; i<size; i++){
			T_Record* p = records[i];
			printf("%d. %s\n", i+1, info_to_string(p));
		}
	}
	else
		printf("There is no %s restaurant:(\n", ctgr);
}

void load_file(){
	printf("All data will be deleted and new records will be reloaded.\n");
	printf("1.Yes 0.No > ");
	int yn;
	scanf("%d", &yn);
	if (yn == 0) return;
	info_init();

	FILE* f = fopen("infos.txt", "r");
	char name[20], phone[20], ctgr[20], time[20];
	while(!feof(f)){
		if(!info_is_available()) {
			printf("[Load] There is no space!\n");
			break;
		}
		int n = fscanf(f,"%s %s %s %s", name, phone, ctgr, time);
		if (n<4) break;
		if(info_search_by_name(name)) {
			printf("[Load] Duplicated name(%s)! loading.\n", name);
			continue;
		}
		info_create(name, phone, ctgr, time);
	}
	printf("%d records are read from file!\n", info_count());    
	fclose(f);
}

void save_file(){
	FILE* f = fopen("infos.txt", "w");
	printf("All records.\n");
	int size = info_count();
	T_Record* records[MAX_MEMBERS];
	info_gets_all(records);
	for(int i=0; i<size; i++){
		T_Record* p = records[i];
		fprintf(f,"%s\n", info_to_string_save(p));
	}
	printf("%d records are saved!\n", info_count());
	fclose(f);
}








