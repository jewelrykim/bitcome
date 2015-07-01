#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>

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
	printf("�̸� : %s\n", arr->name);
	printf("�ּ� : %s\n", arr->address);
	printf("��ȭ��ȣ : %s\n\n", arr->phonenum);
}
void Input(user* arr, int* count, int a){		//�Է��ϴ� �Լ�
	if ((*count) >= a){
		printf("�ڸ������ϴ�.\n");
		return;
	}
	Enter(&arr[*count]);
	(*count)++;
}
void Output(user* arr, int count){				//����Լ�
	for (int i = 0; i < count; i++){
		Print((arr + i));
	}
}
int SSearch(user* arr, int count,int max){				//���ϰ˻� �⺻ �Լ�
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < count; i++){
		if (strcmp(sear, arr[i].name) == 0){
			return i;
		}
	}
	return max+1;
}
void MSearch(user* arr, int count, int *flag){		//���߰˻� �⺻ �Լ�
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	int num=0;
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < count; i++){
		if (strstr(arr[i].name, sear) != NULL){
			flag[num] = i;
			num++;
		}
	}
	flag[num] = -1;
}
void Movedata(user* arr, int num, int *count, int max){		//�����ͻ����� ���� datamove�⺻�Լ�
	for (int i = num; i < max; i++){
		strcpy(arr[i].name, arr[i + 1].name);
		strcpy(arr[i].address, arr[i + 1].address);
		strcpy(arr[i].phonenum, arr[i + 1].phonenum);
	}
	*count -= 1;
}
void SingleSearch(user* arr, int count, int max){		//���ϰ˻��Լ�
	printf("�˻��ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int num =SSearch(arr, count, max);
	if ( num == max + 1);
	else{
		Print(arr + num);
	}
}
void MultiSearch(user* arr, int count, int max){			//���߰˻��Լ�
	printf("�˻��ϰ� ���� ����� �̸� : ");
	int arraycount = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	MSearch(arr, count, flag);
	while (flag[arraycount] != -1){
		Print(arr + flag[arraycount]);
		arraycount++;
	}
}
void Change(user* arr, int count, int max){		//�����Լ�( ��Ȯ�� ��ġ�ϴ� �̸��� ��������
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	if (SSearch(arr, count,max) != max+1){
		printf("������ ����\n");
		Enter(arr + SSearch(arr, count,max));
	}
}
void SingleDelete(user* arr, int *count, int max){		//���ϻ����Լ�
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int num = SSearch(arr, *count, max);
	if (num == max + 1);
	else{
		Movedata(arr, num, &*count, max);
	}
}
void MultiDelete(user* arr, int *count, int max){		//���߻���
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	int arraycount = 0;
	int a = 0;
	int * flag = (int *)malloc(sizeof(int)*max);
	MSearch(arr, *count, flag);
	while (flag[arraycount] != -1){
		flag[arraycount] -= arraycount;		//�迭 ��Ұ� �̵��ϸ鼭 ����� arraycount ���� ����
		Movedata(arr, flag[arraycount], & *count, max);
		arraycount++;
	}
}

void InputUserNumber(user* *arr,int *max){
	printf("User Max :");
	scanf_s("%d", max);
	fflush(stdin);
	*arr = (user *)malloc(sizeof(user)* *max);
}

void main()
{
	char mode = '1';// mode�� ��弳�� ����
	user* arr=NULL;
	int usermax=0;
	InputUserNumber(&arr, &usermax);
	int count = 0; //������ �˷��ִ� ����
	while (mode != '8'){
		printf("\nmode ���� ( 1 = �Է� , 2 = ��� , 3 = ���ϰ˻�(��Ȯ�� �̸�), 4 = ���߰˻�(���Ե� ����), 5= ����(��Ȯ�� �̸�), 6 = ���ϻ���(��Ȯ�� �̸�), 7 = ���߻���(���Ե� ����), 8 = ����) \n");
		mode = getchar();
		fflush(stdin);

		switch (mode)
		{
		case '1': //�Է�
			Input(arr, &count, usermax);
			break;
		case '2': //���
			Output(arr, count);
			break;
		case '3': //�˻�
			SingleSearch(arr, count, usermax);
			break;
		case '4':
			MultiSearch(arr, count, usermax);
			break;
		case '5':	// ����
			Change(arr, count, usermax);
			break;
		case '6':	// ����
			SingleDelete(arr, &count, usermax);
			break;
		case '7':
			MultiDelete(arr, &count, usermax);
			break;
		default:
			mode = '8';
			break;
		}
	} 
}