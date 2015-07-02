#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
struct user
{
	char name[128];		//�̸�
	char address[128];	//�ּ�
	char phonenum[128];	//��ȭ��ȣ
};
void Enter(user* arr){	//�Է¹޴��Լ�
	printf("�̸� : ");
	gets(arr->name);
	fflush(stdin);
	printf("�ּ� : ");
	gets(arr->address);
	fflush(stdin);
	printf("��ȭ��ȣ : ");
	gets(arr->phonenum);
	fflush(stdin);
}
void Print(user* arr){							//����ϴ��Լ�
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
void Output(user* arr, int count){				//����Լ�
	if (count == 0){
		printf("����� �����Ͱ� �����ϴ�."); 
	}
	else{
		for (int i = 0; i < count; i++){
			Print((arr + i));
		}
	}
}
int SSearch(user* arr, int count,int *num,int max,char*sear){				//���ϰ˻� �⺻ �Լ�
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
int MSearch(user* arr, int count, int *flag ,char * sear){		//���߰˻� �⺻ �Լ�
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
void Movedata(user* arr, int num, int *count, int max){		//�����ͻ����� ���� datamove�⺻�Լ�
	for (int i = num; i < max; i++){
		strcpy(arr[i].name, arr[i + 1].name);
		strcpy(arr[i].address, arr[i + 1].address);
		strcpy(arr[i].phonenum, arr[i + 1].phonenum);
	}
	*count -= 1;
}
void SingleSearch(user* arr, int count,int max,char* *errmsg){		//���ϰ˻��Լ�
	printf("�˻��ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int memberpoint=0;
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	if (SSearch(arr, count, &memberpoint, max, sear) == 0){
		Print(arr + memberpoint);
	}
	printf("%s", errmsg[SSearch(arr, count, &memberpoint, max, sear)]);
}
void MultiSearch(user* arr, int count, int max, char* *errmsg){			//���߰˻��Լ�
	printf("�˻��ϰ� ���� ����� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	int arraycount = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	if (MSearch(arr, count, flag, sear) == 0){
		while (flag[arraycount] != -1){
			Print(&arr[ flag[arraycount] ]);
			arraycount++;
		}
	}
	printf("%s", errmsg[MSearch(arr, count, flag, sear)]);
}
void Change(user* arr, int count, int max, char* *errmsg){		//�����Լ�( ��Ȯ�� ��ġ�ϴ� �̸��� ��������
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int memberpoint = 0;
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	printf("%s", errmsg[SSearch(arr, count, &memberpoint, max, sear)]);
	if (SSearch(arr, count, &memberpoint, max, sear) == 0){
		printf("������ ����\n");
		Enter(arr + memberpoint);
	}
}
void SingleDelete(user* arr, int *count, int max, char* *errmsg){		//���ϻ����Լ�
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int memberpoint = 0;
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	if (SSearch(arr, *count, &memberpoint, max, sear) == 0){
		Movedata(arr, memberpoint, &*count, max);
	}
	printf("%s", errmsg[SSearch(arr, *count, &memberpoint, max, sear)]);
}
void MultiDelete(user* arr, int *count, int max,char* *errmsg){		//���߻���
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	int arraycount = 0;
	int a = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	printf("%s", errmsg[MSearch(arr, *count, flag, sear)]);
	if (MSearch(arr, *count, flag, sear) == 0){
		while (flag[arraycount] != -1){
			flag[arraycount] -= arraycount;		//�迭 ��Ұ� �̵��ϸ鼭 ����� arraycount ���� ����
			Movedata(arr, flag[arraycount], &*count, max);
			arraycount++;
		}
	}
}
void InputUserNumber(user* *arr,int *max){
	printf("User Max :");
	scanf_s("%d", max);
	fflush(stdin);
	*arr = (user *)malloc(sizeof(user)* *max);
}
void Fileprint(user* arr, int usermax,int count){
	FILE *fp;
	printf("�ּҷ��� �����մϴ�.\n");
	fp = fopen("addressbook.txt", "w");
	fprintf(fp, "%d\n", usermax);
	for (int index = 0; index < count; index++)
	{
		fprintf(fp, "%s ,%s ,%s\n", arr[index].name, arr[index].address, arr[index].phonenum);
	}
	fclose(fp);
}
void FileScan(user* *arr, int *usermax, int *count){
	FILE *fp;
	fp = fopen("addressbook.txt", "r");
	if (fp == NULL)
		printf("�ּҷ��� �����ϴ�.");
	else{
		printf("�ּҷ��� �о�ɴϴ�.\n");
		fscanf(fp, "%d\n", &*usermax);
		int index = 0;
		free(*arr);
		*arr = (user *)malloc(sizeof(user)* (*usermax));
		while (!feof(fp))
		{
			fscanf(fp, "%s ,%s ,%s\n", &arr[index]->name, &arr[index]->address, &arr[index]->phonenum);
			index++;
		}
		*count = index;
		fclose(fp);
	}
}
void main()
{
	char mode = '1';// mode�� ��弳�� ����
	user* arr=NULL;
	int count = 0; //������ �˷��ִ� ����
	int usermax=0;
	InputUserNumber(&arr, &usermax);
	char * SearchErrMsg[] = {"ã�⼺��", "��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�."};
	char * ChangeErrMsg[] = {"ã�⼺��", "��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
	char * DeleteErrMsg[] = {"��������", "��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
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
			Change(arr, count, usermax, ChangeErrMsg);
			break;
		case '6':	// ���ϻ���
			SingleDelete(arr, &count, usermax, DeleteErrMsg);
			break;
		case '7':	//���߻���
			MultiDelete(arr, &count, usermax, DeleteErrMsg);
			break;
		case '8':
			Fileprint(arr, usermax, count);
			break;
		case '9':
			FileScan(&arr, &usermax, &count);
			//FILE *fp;
			//fp = fopen("addressbook.txt", "r");
			//if (fp == NULL)
			//	printf("�ּҷ��� �����ϴ�.");
			//else{
			//	printf("�ּҷ��� �о�ɴϴ�.\n");
			//	fscanf(fp, "%d\n", &usermax);
			//	int index = 0;
			//	free(arr);
			//	arr = (user *)malloc(sizeof(user)* (usermax));
			//	while (!feof(fp))
			//	{
			//		//�������� �и��� ���� �б�
			//		fscanf(fp, "%s ,%s ,%s\n", arr[index].name, arr[index].address, arr[index].phonenum);
			//		index++;
			//	}
			//	count = index;
			//	fclose(fp);
			//}
			break;
		default:
			mode = '0';
			free(arr);
			break;
		}
	} 
}