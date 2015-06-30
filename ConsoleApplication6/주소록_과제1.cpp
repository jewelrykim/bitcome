#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#define MAX 5

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

void Output(user* arr,int count){				//����Լ�
	for (int i = 0; i < count;i++){
		Print((arr + i));
	}
}

int SSearch(user* arr, int count){				//���ϰ˻� �⺻ �Լ�
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < count; i++){
		if (strcmp(sear, arr[i].name) == 0){
			return i;
		}
	}
	return MAX+1;
}

void SingleSearch(user* arr ,int count){		//���ϰ˻��Լ�
	printf("�˻��ϰ� ���� ����� ��Ȯ�� �̸� : ");
	if (SSearch(arr, count) == MAX + 1);
	else{
		Print(arr + SSearch(arr, count));
	}
}

void MultiSearch(user* arr, int count){			//���߰˻��Լ�
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	for (int i = 0; i < count; i++){
		if (strstr(arr[i].name, sear) != NULL){
			Print(arr + i);
		}
	}

}

void Change(user* arr, int count){		//�����Լ�( ��Ȯ�� ��ġ�ϴ� �̸��� ��������
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	if (SSearch(arr, count) != MAX+1){
		printf("������ ����\n");
		Enter(arr + SSearch(arr, count));
	}
}

void Delete(user* arr, int* count){		//�����Լ�
	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
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
	char mode=' ';// mode�� ��弳�� ����
	user arr[MAX] = {' ',' ',' '};
	int count = 0; //������ �˷��ִ� ����
	do{
		printf("\nmode ���� ( 1 = �Է� , 2 = ��� , 3 = ���ϰ˻�(��Ȯ�� �̸�), 4 = ���߰˻�(���Ե� ����) , 5= ����(��Ȯ�� �̸�), 6= ����(��Ȯ�� �̸�) ,7= ��) \n");
		mode = getchar();
		fflush(stdin);
		switch (mode)
		{
		case '1': //�Է�
			Input(arr, &count, sizeof(arr) / sizeof(arr[0]));
			break;
		case '2': //���
			Output(arr, count);
			break;
		case '3': //�˻�
			SingleSearch(arr, count);
			break;
		case '4':
			MultiSearch(arr, count);
			break;
		case '5':	// ����
			Change(arr, count);
			break;
		case '6':	// ����
			Delete(arr, &count);
			break;
		default:
			mode = '7';
			break;
		}
	} while (mode != '7');
}