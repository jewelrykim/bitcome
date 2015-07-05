#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
struct user
{
	char * name;		//이름
	char * address;	//주소
	char * phonenum;	//전화번호
};
void Nodememory(char* *data,char * title){
	char temp[1024];
	printf("%s",title);
	gets(temp);
	fflush(stdin);
	*data = (char *)malloc(strlen(temp) + 1);
	strcpy(*data, temp);
}
void Enter( user* arr){	//입력받는함수
	Nodememory(&arr->name, "이름 : ");
	Nodememory(&arr->address, "주소 : ");
	Nodememory(&arr->phonenum, "전화번호 : ");
}
void Killdata( user* arr){
	arr->name = NULL;
	arr->address = NULL;
	arr->phonenum = NULL;
	free(arr->name);
	free(arr->address);
	free(arr->phonenum);
}
void Print(const user* arr){							//출력하는함수
	printf("\n이름 : %s\n", arr->name);
	printf("주소 : %s\n", arr->address);
	printf("전화번호 : %s\n\n", arr->phonenum);
}
void Input(user* arr, int* count, int usermax){		//입력하는 함수
	if ((*count) >= usermax){
		printf("자리가 없습니다.\n");
		return;
	}
	Enter(&arr[*count]);
	(*count)++;
}
void Output( user* arr, int count){				//출력함수
	if (count == 0){
		printf("저장된 데이터가 없습니다."); 
	}
	else{
		for (int i = 0; i < count; i++){
			Print((arr + i));
		}
	}
}
int SSearch(const user* arr, int count, int *num, int max, char*sear){				//단일검색 기본 함수
	if (count == 0){
		return 1;
	}
	else{
		for (int i = 0; i < count; i++){
			if (strcmp(sear, arr[i].name) == 0){
				*num = i;
				return 0;
			}
		}
		return 2;
	}
}
int MSearch(const user* arr, int count, int *flag, char * sear){		//다중검색 기본 함수
	int num = 0;
	if (count == 0){
		return 1;
	}
	else{
		for (int i = 0; i < count; i++){
			if (strstr(arr[i].name, sear) != NULL){
				flag[num] = i;
				num++;
			}
		}
		flag[num] = -1;
		if (flag[0] == -1){
			return 2;
		}
		else{
			return 0;
		}
	}
}
void Movedata( user* arr, int *count, int num, int max){		//데이터삭제를 위한 datamove기본함수
		for (int i = num; i < *count; i++){
			Killdata(&arr[i]);
			arr[i].name = arr[i+1].name;
			arr[i].address = arr[i + 1].address;
			arr[i].phonenum = arr[i + 1].phonenum;
		}
		*count -= 1;
}
void SingleSearch(const user* arr, int count, int max, char* *SearchMsg){		//단일검색함수
	printf("검색하고 싶은 사람의 정확한 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	int memberpoint = 0;
	int ReturnSearch = SSearch(arr, count, &memberpoint, max, sear);
	if (ReturnSearch == 0){
		Print(arr + memberpoint);
	}
	printf("%s", SearchMsg[ReturnSearch]);
}
void MultiSearch(const user* arr, int count, int max, char* *SearchMsg){			//다중검색함수
	printf("검색하고 싶은 사람의 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	int arraycount = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	int ReturnSearch = MSearch(arr, count, flag, sear);
	if (ReturnSearch == 0){
		while (flag[arraycount] != -1){
			Print(&arr[ flag[arraycount] ]);
			arraycount++;
		}
	}
	printf("%s", SearchMsg[ReturnSearch]);
	free(flag);
}
void Change(user* arr, int count, int max,char* *SearchMsg, char* *ChangeMsg){		//수정함수( 정확히 일치하는 이름만 수정가능
	printf("수정하고 싶은 사람의 정확한 이름 : ");
	int memberpoint = 0;
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	printf("%s", SearchMsg[SSearch(arr, count, &memberpoint, max, sear)]);
	if (SSearch(arr, count, &memberpoint, max, sear) == 0){
		printf("수정할 정보\n");
		Killdata(&arr[memberpoint]);
		Enter(arr + memberpoint);
	}
	printf("%s", ChangeMsg[SSearch(arr, count, &memberpoint, max, sear)]);
}
void SingleDelete(user* arr, int *count, int max, char* *DeleteMsg){		//단일삭제함수
	printf("삭제하고 싶은 사람의 정확한 이름 : ");
	int memberpoint = 0;
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin); 
	int ReturnSearch = SSearch(arr, *count, &memberpoint, max, sear);
	if (ReturnSearch == 0){
		Movedata(arr, count, memberpoint, max);
	}
	printf("%s", DeleteMsg[ReturnSearch]);
}
void MultiDelete( user* arr, int *count, int max, char* *DeleteMsg){		//다중삭제
	printf("삭제하고 싶은 사람의 정확한 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	int arraycount = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	int ReturnSearch = MSearch(arr, *count, flag, sear);
	if (ReturnSearch == 0){
		while (flag[arraycount] != -1){
			flag[arraycount] -= arraycount;		//배열 요소가 이동하면서 생기는 arraycount 정보 수정
			Movedata(arr, count, flag[arraycount], max);
			arraycount++;
		}
	}
	printf("%s", DeleteMsg[ReturnSearch]);
	free(flag);
}
void InputUserNumber(user* *arr, int *max){
	printf("User Max :");
	scanf_s("%d", max);
	fflush(stdin);
	*arr = (user *)malloc(sizeof(user)* *max);
}
void FilePrint(const user* arr, int usermax, int count){
	FILE *fp;
	printf("주소록을 저장합니다.\n");
	fp = fopen("addressbook.txt", "w");
	fprintf(fp, "%d\n", usermax);
	for (int index = 0; index < count; index++)
	{
		fprintf(fp, "%s\n%s\n%s\n", arr[index].name, arr[index].address, arr[index].phonenum);
	}
	fclose(fp);
}
char* FileDataScan(FILE * fp,char **pData){
	char temp[1024] = { " " };
	char* tester;
	tester=fgets(temp, 1024, fp);
	*pData = (char *)malloc(strlen(temp));
	strcpy(*pData, temp);
	(*pData)[strlen(temp) - 1] = NULL;
	return tester;
}
void FileScan( user* arr, int *usermax, int *count){
	FILE *fp;
	fp = fopen("addressbook.txt", "r");
	if (fp == NULL)
		printf("주소록이 없습니다.");
	else{
		printf("주소록을 읽어옵니다.\n");
		fscanf(fp, "%d\n", usermax);
		int index = 0; 
		free(arr);
		arr = (user *)malloc(sizeof(user)* (*usermax));
		while (!feof(fp))
		{
			if(FileDataScan(fp, &arr[index].name)==NULL)break;
			FileDataScan(fp, &arr[index].address);
			FileDataScan(fp, &arr[index].phonenum);
			index++;

		}
		*count = index;
	}
	fclose(fp);
}
void main()
{
	char mode = '1';// mode는 모드설정 변수
	user* arr=NULL;
	int count = 0; //개수를 알려주는 변수
	int usermax=0;
	InputUserNumber(&arr, &usermax);
	char * SearchErrMsg[] = {"찾기성공", "삭제 등록된 데이터가 없습니다.", "찾으려는 데이터가 존재하지 않습니다."};
	char * ChangeErrMsg[] = {"수정성공", "등록된 데이터가 없습니다.", "찾으려는 데이터가 존재하지 않습니다." };
	char * DeleteErrMsg[] = {"삭제성공", "삭제 등록된 데이터가 없습니다.", "찾으려는 데이터가 존재하지 않습니다." };
	while (mode != '0'){
		printf("\nmode 선택 ( 1 = 입력 , 2 = 출력 , 3 = 단일검색(정확한 이름), 4 = 다중검색(포함된 글자), 5= 수정(정확한 이름), 6 = 단일삭제(정확한 이름), 7 = 다중삭제(포함된 글자), 8 = 파일저장, 9 = 파일로드 0 = 종료) \n");
		mode = getchar();
		fflush(stdin);

		switch (mode)
		{
		case '1':	//입력
			Input(arr, &count, usermax);
			break;
		case '2':	//출력
			Output(arr, count);
			break;
		case '3':	//단일검색
			SingleSearch(arr, count, usermax, SearchErrMsg);
			break;
		case '4':	//다중검색
			MultiSearch(arr, count, usermax, SearchErrMsg);
			break;
		case '5':	// 수정
			Change(arr, count, usermax,SearchErrMsg, ChangeErrMsg);
			break;
		case '6':	// 단일삭제
			SingleDelete(arr, &count, usermax, DeleteErrMsg);
			break;
		case '7':	//다중삭제
			MultiDelete(arr, &count, usermax, DeleteErrMsg);
			break;
		case '8':
			FilePrint(arr, usermax, count);
			break;
		case '9':
			FileScan(arr, &usermax, &count);
			break;
		default:
			mode = '0';
			free(arr);
			break;
		}
	} 
}