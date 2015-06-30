#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#define MAX 5

struct user
{
	char name[128];		//이름
	char address[128];	//주소
	char phonenum[128];	//전화번호
};

void Enter(user* arr){	//입력받는함수
	printf("이름 : ");
	gets(arr->name);
	fflush(stdin);
	printf("주소 : ");
	gets(arr->address);
	fflush(stdin);
	printf("전화번호 : ");
	gets(arr->phonenum);
	fflush(stdin);
}

void Print(user* arr){							//출력하는함수
	printf("이름 : %s\n", arr->name);
	printf("주소 : %s\n", arr->address);
	printf("전화번호 : %s\n\n", arr->phonenum);
}

void Input(user* arr, int* count, int a){		//입력하는 함수
	if ((*count) >= a){
		printf("자리없습니다.\n");
		return;
	}
	Enter(&arr[*count]);
	(*count)++;
}

void Output(user* arr,int count){				//출력함수
	for (int i = 0; i < count;i++){
		Print((arr + i));
	}
}

int SSearch(user* arr, int count){				//단일검색 기본 함수
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < count; i++){
		if (strcmp(sear, arr[i].name) == 0){
			return i;
		}
	}
	return MAX+1;
}

void SingleSearch(user* arr ,int count){		//단일검색함수
	printf("검색하고 싶은 사람의 정확한 이름 : ");
	if (SSearch(arr, count) == MAX + 1);
	else{
		Print(arr + SSearch(arr, count));
	}
}

void MultiSearch(user* arr, int count){			//다중검색함수
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < count; i++){
		if (strstr(arr[i].name, sear) != NULL){
			Print(arr + i);
		}
	}

}

void Change(user* arr, int count){		//수정함수( 정확히 일치하는 이름만 수정가능
	printf("수정하고 싶은 사람의 정확한 이름 : ");
	if (SSearch(arr, count) != MAX+1){
		printf("수정할 정보\n");
		Enter(arr + SSearch(arr, count));
	}
}

void Delete(user* arr, int* count){		//삭제함수
	printf("삭제하고 싶은 사람의 정확한 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < *count; i++){
		if (strstr(arr[i].name, sear) != NULL){
			strcpy(arr[i].name, arr[i + 1].name);
			strcpy(arr[i].address, arr[i + 1].address);
			strcpy(arr[i].phonenum, arr[i + 1].phonenum);
			*count -= 1;
			break;
		}
	}
}

void main()
{
	char mode=' ';// mode는 모드설정 변수
	user arr[MAX] = {' ',' ',' '};
	int count = 0; //개수를 알려주는 변수
	do{
		printf("\nmode 선택 ( 1 = 입력 , 2 = 출력 , 3 = 단일검색(정확한 이름), 4 = 다중검색(포함된 글자) , 5= 수정(정확한 이름), 6= 삭제(정확한 이름) ,7= 끝) \n");
		mode = getchar();
		fflush(stdin);
		switch (mode)
		{
		case '1': //입력
			Input(arr, &count, sizeof(arr) / sizeof(arr[0]));
			break;
		case '2': //출력
			Output(arr, count);
			break;
		case '3': //검색
			SingleSearch(arr, count);
			break;
		case '4':
			MultiSearch(arr, count);
			break;
		case '5':	// 수정
			Change(arr, count);
			break;
		case '6':	// 삭제
			Delete(arr, &count);
			break;
		default:
			mode = '7';
			break;
		}
	} while (mode != '7');
}