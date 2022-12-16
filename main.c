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


int trackInfester(int patient_no, int *detected_time, int *place);
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
            	pIndex=printf("ȯ���� ��ȣ�� �Է��ϼ���:"); // �̰� �־�� �ϴ��� �ƴ��� �� ������ �� ���µ�.. �켱 �־.  
            	scanf("%i",&pIndex);
            	printf("ȯ���� ��ȣ: %i\n",pIndex);
            	ifct_element = ifctdb_getData(pIndex);//����� ȯ���� ����ü ��������
            	ifctele_printElement(ifct_element);
                break;
                
            case MENU_PLACE:
            	int input_place;
                input_place=printf("��Ҹ� �Է��ϼ���:"); //��Ҹ� ���ڿ��� �Է¹ް�
				scanf("%s",&input_place); // scanf�ϰ�
				//���ڿ��� �ٽ� �������� �ٲ۴�.  
				//printf("%s",place); // ���ڿ��� ����Ʈ �ȵ�. 
				ifct_element = ifctdb_getData(1);
				printf("%i",placeHist[4]);
				for(int i=0;i<5;i++)
				{
					ifct_element = ifctdb_getData(i); // ifct_element 1,2,3,4,5��° open..? 
					printf("%i",pIndex); 
					if(placeHist[4]==input_place) // ������ ���==�Է¹��� ���(���ڷ� ��ȯ�ؾ� ��) 
					   printf("%i",pIndex);  // ���� ������ �� ����� pIndex�� print 
			    }
                break;
                
            case MENU_AGE:
            	int a,b;
            	a=printf("�ּ� ���ڸ� �Է��ϼ���:"); //�ּ� ���ڸ� �Է¹��� 
            	scanf("%d",&a); 
            	b=printf("�ִ� ���ڸ� �Է��ϼ���:"); //�ִ� ���ڸ� �Է¹��� 
            	scanf("%d",&b); 
            	for(int i=0;i<5;i++)     //for���� ������ �����͸� �� �о� ���Բ� 
            	{
            		ifct_element = ifctdb_getData(i);
            		if(ifctele_getAge(ifct_element)<=b&&age>=a)  // if���� �޾ƿͼ� ������ �ش�Ǵ��� Ȯ�� 
            		    printf("%i\n",ifctele_getAge(ifct_element)); // �ش�ȴٸ� age ��� 
				}
                break;
               
            case MENU_TRACK:
                ifctele_getinfestedTime(ifct_element);
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
