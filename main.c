//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2
/*
int converTimeToIndex(int time,int infestedTime)
{
	int index=-1;
	if(time<=infestedTime && time >infestedTime-N_HISTORY)
	{
		index=N_HISTORY-(infestedTime-time)-1;
	}
	return index;
}

int isMet(int detected_time, int number)
{
	for(i=1;i<N_HISTORY;i++)
	{
		int Ptime[i]=detected_time-N_HISTORY+i;//����ȯ���� i��° �̵���� ���� ���
		//���� ��Ȳ���� ���ȯ���� �̵���� ��� 
	}
	//�����ð�; 
	//�� �������� -1 ��ȯ�� 
}
*/
int trackInfester(int patient_no, int detected_time, int place)
{
	int influencer; //������ �������ش�.  
    for(int i=1;i<patient_no;i++) //i��° ȯ�� 
	{
		//int Meet=isMet(detected_time,patient_no); //���� �ð� �������ش�. (isMet �Լ��� ����Ѵ�.) 
		//if(Meet>0) //�����ٸ�  
		{
			//if() //���ݱ��� ȯ�� �� ���� �ð��� ���� �̸���?
			   influencer=i; 
		} 
	}
	return influencer; 
}

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //1-2. loading each patient informations

    while(3==fscanf(fp,"%i %i %i",&pIndex,&age,&time))
    {
    	for(int i=0; i<5;i++)
		{
			fscanf(fp,"%i", &placeHist[i]); // i��° ������� ���ڸ� �б�   
		} 
		ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
		ifctdb_addTail(ifct_element);
	};
    //1-3. FILE pointer close
    fclose(fp);
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
            	printf("ȯ���� ��ȣ�� �Է��ϼ���:"); 
            	scanf("%i",&pIndex);  // ȯ�ڹ�ȣ�� �Է¹޴´�.
            	printf("ȯ���� ��ȣ: %i\n",pIndex);  //ȯ�ڹ�ȣ�� ����Ѵ�.  
            	ifct_element = ifctdb_getData(pIndex); //�Է¹��� ȯ�ڹ�ȣ�� ����ü ��������
            	ifctele_printElement(ifct_element);  // ����, �ð�, ��� print 
                break;
                
            case MENU_PLACE:
            	char input_place[MAX_PLACENAME]; //���ڿ��� ���� 
                printf("��Ҹ� �Է��ϼ���:"); //��Ҹ� ���ڿ��� �Է¹ް�
				scanf("%s",input_place); // scanf��. ���ڿ� ���·� ����

				for(int i=0;i<pIndex+1;i++)
				{
					ifct_element = ifctdb_getData(i); // ifct_element 0,1,2,3,4,��° data�� �����´�.  
					int number=ifctele_getHistPlaceIndex(ifct_element,4); //0,1,2,3,4...��°�� 5��° ����� ���ڸ� �Լ��� �ް� number�� �����մϴ�.  
					if (strcmp(ifctele_getPlaceName(number),input_place)==0 ) // �Լ��� �̿��� ���ڿ��� �ٲ� �� ���� ���մϴ�.  
					{
					    printf("ȯ�ڹ�ȣ: %i��\n",i);
						ifctele_printElement(ifct_element);  // ���� ������ ȯ���� ������ print 
					} 
			    }
                break;
                
            case MENU_AGE:
            	int a,b;
            	printf("�ּ� ���ڸ� �Է��ϼ���:");  
            	scanf("%d",&a);   //�ּ� ���ڸ� �Է¹��� 
            	printf("�ִ� ���ڸ� �Է��ϼ���:");  
            	scanf("%d",&b);   //�ִ� ���ڸ� �Է¹���
            	for(int i=0;i<pIndex+1;i++)     //for���� ������ �����͸� �� �о� ���Բ��Ѵ�. 
            	{
            		ifct_element = ifctdb_getData(i); //i��° �����͸� �޾ƿ´�.  
            		if(ifctele_getAge(ifct_element)<=b&&age>=a)  // i��° ����� ���̰� ������ �ش�Ǵ��� Ȯ��
					{
						printf("ȯ�ڹ�ȣ: %i��\n",i);
						ifctele_printElement(ifct_element);
					} 
				}
                break;
            
            case MENU_TRACK:
            	
            	int input_index;
				printf("ȯ�ڹ�ȣ�� �Է��ϼ���:");
			    scanf("%d",&input_index);  // ����ȯ���� ��ȣ�� �Է¹޴´�.  
			    while(input_index<pIndex+1)  // ����ȯ�� ��ȣ�� ���� �ȿ� ���Եȴ�.  
			    {
			    	ifct_element = ifctdb_getData(input_index); //����ȯ���� ������ �����´�.  
			    	int influencer=trackInfester(input_index,ifctele_getinfestedTime(ifct_element),ifctele_getHistPlaceIndex(ifct_element, N_HISTORY-1)); //�����ڸ� Ȯ���ϱ�  
			    	if(influencer>0) //�����ڰ� �����ϸ�
					{
						printf("%i ȯ�ڴ� %i ȯ�ڿ��� ���ĵ�\n",input_index,influencer); //����ȯ�ڿ� �����ڿ� ���� �������ش�. 
						printf("���� %i, %s",ifctele_getinfestedTime(ifct_element)-4,ifctele_getHistPlaceIndex(ifct_element, 1)); //������ ��Ҹ� ������ش�.  
					}       
			    	else // �����ڰ� ������  
			    	    int First_influencer=influencer; //���� ������=����ȯ��
						break; //���� �����ڸ� ã���� while�� break 
					input_index=influencer; //����ȯ��=������ (�ٽ� while������ ���ư��� �ϴϱ�)				 
				}
				 
                
                break;
                
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break; 
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
