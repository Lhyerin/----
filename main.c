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
			fscanf(fp,"%i", &placeHist[i]); // i번째 감염경로 숫자를 읽기   
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
            	pIndex=printf("환자의 번호를 입력하세요:"); // 이거 넣어야 하는지 아닌지 잘 구별은 안 가는데.. 우선 넣어봄.  
            	scanf("%i",&pIndex);
            	printf("환자의 번호: %i\n",pIndex);
            	ifct_element = ifctdb_getData(pIndex);//몇번쨰 환자의 구조체 가져오기
            	ifctele_printElement(ifct_element);
                break;
                
            case MENU_PLACE:
            	int input_place;
                input_place=printf("장소를 입력하세요:"); //장소를 문자열로 입력받고
				scanf("%s",&input_place); // scanf하고
				//문자열을 다시 정수열로 바꾼다.  
				//printf("%s",place); // 문자열로 프린트 안됨. 
				ifct_element = ifctdb_getData(1);
				printf("%i",placeHist[4]);
				for(int i=0;i<5;i++)
				{
					ifct_element = ifctdb_getData(i); // ifct_element 1,2,3,4,5번째 open..? 
					printf("%i",pIndex); 
					if(placeHist[4]==input_place) // 마지막 장소==입력받은 장소(숫자로 변환해야 함) 
					   printf("%i",pIndex);  // 만약 맞으면 그 사람의 pIndex를 print 
			    }
                break;
                
            case MENU_AGE:
            	int a,b;
            	a=printf("최소 숫자를 입력하세요:"); //최소 숫자를 입력받음 
            	scanf("%d",&a); 
            	b=printf("최대 숫자를 입력하세요:"); //최대 숫자를 입력받음 
            	scanf("%d",&b); 
            	for(int i=0;i<5;i++)     //for문을 돌려서 데이터를 다 읽어 오게끔 
            	{
            		ifct_element = ifctdb_getData(i);
            		if(ifctele_getAge(ifct_element)<=b&&age>=a)  // if문을 받아와서 범위에 해당되는지 확인 
            		    printf("%i\n",ifctele_getAge(ifct_element)); // 해당된다면 age 출력 
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
