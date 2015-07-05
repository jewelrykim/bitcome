#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
struct user
{
	char * name;		//�̸�
	char * address;	//�ּ�
	char * phonenum;	//��ȭ��ȣ
};
void Nodememory(char* *data,char * title){
	char temp[1024];
	printf("%s",title);
	gets(temp);
	fflush(stdin);
	*data = (char *)malloc(strlen(temp) + 1);
	strcpy(*data, temp);
}
void Enter( user* arr){	//�Է¹޴��Լ�
	Nodememory(&arr->name, "�̸� : ");
	Nodememory(&arr->address, "�ּ� : ");
	Nodememory(&arr->phonenum, "��ȭ��ȣ : ");
}
void Killdata( user* arr){
	arr->name = NULL;
	arr->address = NULL;
	arr->phonenum = NULL;
	free(arr->name);
	free(arr->address);
	free(arr->phonenum);
}
void Print(const user* arr){							//����ϴ��Լ�
	printf("\n�̸� : %s\n", arr->name);
	printf("�ּ� : %s\n", arr->address);
	printf("��ȭ��ȣ : %s\n\n", arr->phonenum);
}
void Input(user* arr, int* count, int usermax){		//�Է��ϴ� �Լ�
	if ((*count) >= usermax){
		printf("�ڸ��� �����ϴ�.\n");
		return;
	}
	Enter(&arr[*count]);
	(*count)++;
}
void Output( user* arr, int count){				//����Լ�
	if (count == 0){
		printf("����� �����Ͱ� �����ϴ�."); 
	}
	else{
		for (int i = 0; i < count; i++){
			Print((arr + i));
		}
	}
}
int SSearch(const user* arr, int count, int *num, int max, char*sear){				//���ϰ˻� �⺻ �Լ�
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
int MSearch(const user* arr, int count, int *flag, char * sear){		//���߰˻� �⺻ �Լ�
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
void Movedata( user* arr, int *count, int num, int max){		//�����ͻ����� ���� datamove�⺻�Լ�
		for (int i = num; i < *count; i++){
			Killdata(&arr[i]);
			arr[i].name = arr[i+1].name;
			arr[i].address = arr[i + 1].address;
			arr[i].phonenum = arr[i + 1].phonenum;
		}
		*count -= 1;
}
void SingleSearch(const user* arr, int count, int max, char* *SearchMsg){		//���ϰ˻��Լ�
	printf("�˻��ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	int memberpoint = 0;
	int ReturnSearch = SSearch(arr, count, &memberpoint, max, sear);
	if (ReturnSearch == 0){
		Print(arr + memberpoint);
	}
	printf("%s", SearchMsg[ReturnSearch]);
}
void MultiSearch(const user* arr, int count, int max, char* *SearchMsg){			//���߰˻��Լ�
	printf("�˻��ϰ� ���� ����� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
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
void Change(user* arr, int count, int max,char* *SearchMsg, char* *ChangeMsg){		//�����Լ�( ��Ȯ�� ��ġ�ϴ� �̸��� ��������
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int memberpoint = 0;
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	printf("%s", SearchMsg[SSearch(arr, count, &memberpoint, max, sear)]);
	if (SSearch(arr, count, &memberpoint, max, sear) == 0){
		printf("������ ����\n");
		Killdata(&arr[memberpoint]);
		Enter(arr + memberpoint);
	}
	printf("%s", ChangeMsg[SSearch(arr, count, &memberpoint, max, sear)]);
}
void SingleDelete(user* arr, int *count, int max, char* *DeleteMsg){		//���ϻ����Լ�
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int memberpoint = 0;
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin); 
	int ReturnSearch = SSearch(arr, *count, &memberpoint, max, sear);
	if (ReturnSearch == 0){
		Movedata(arr, count, memberpoint, max);
	}
	printf("%s", DeleteMsg[ReturnSearch]);
}
void MultiDelete( user* arr, int *count, int max, char* *DeleteMsg){		//���߻���
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	int arraycount = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	int ReturnSearch = MSearch(arr, *count, flag, sear);
	if (ReturnSearch == 0){
		while (flag[arraycount] != -1){
			flag[arraycount] -= arraycount;		//�迭 ��Ұ� �̵��ϸ鼭 ����� arraycount ���� ����
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
	printf("�ּҷ��� �����մϴ�.\n");
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
		printf("�ּҷ��� �����ϴ�.");
	else{
		printf("�ּҷ��� �о�ɴϴ�.\n");
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
	char mode = '1';// mode�� ��弳�� ����
	user* arr=NULL;
	int count = 0; //������ �˷��ִ� ����
	int usermax=0;
	InputUserNumber(&arr, &usermax);
	char * SearchErrMsg[] = {"ã�⼺��", "���� ��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�."};
	char * ChangeErrMsg[] = {"��������", "��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
	char * DeleteErrMsg[] = {"��������", "���� ��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
	while (mode != '0'){
		printf("\nmode ���� ( 1 = �Է� , 2 = ��� , 3 = ���ϰ˻�(��Ȯ�� �̸�), 4 = ���߰˻�(���Ե� ����), 5= ����(��Ȯ�� �̸�), 6 = ���ϻ���(��Ȯ�� �̸�), 7 = ���߻���(���Ե� ����), 8 = ��������, 9 = ���Ϸε� 0 = ����) \n");
		mode = getchar();
		fflush(stdin);

		switch (mode)
		{
		case '1':	//�Է�
			Input(arr, &count, usermax);
			break;
		case '2':	//���
			Output(arr, count);
			break;
		case '3':	//���ϰ˻�
			SingleSearch(arr, count, usermax, SearchErrMsg);
			break;
		case '4':	//���߰˻�
			MultiSearch(arr, count, usermax, SearchErrMsg);
			break;
		case '5':	// ����
			Change(arr, count, usermax,SearchErrMsg, ChangeErrMsg);
			break;
		case '6':	// ���ϻ���
			SingleDelete(arr, &count, usermax, DeleteErrMsg);
			break;
		case '7':	//���߻���
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