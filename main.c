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
		int Ptime[i]=detected_time-N_HISTORY+i;//현재환자의 i번째 이동장소 시점 계산
		//위의 상황에서 대상환자의 이동장소 계산 
	}
	//만난시간; 
	//안 만났으면 -1 반환하 
}
*/
int trackInfester(int patient_no, int detected_time, int place)
{
	int influencer; //전파자 선언해준다.  
    for(int i=1;i<patient_no;i++) //i번째 환자 
	{
		//int Meet=isMet(detected_time,patient_no); //만난 시간 선언해준다. (isMet 함수를 사용한다.) 
		//if(Meet>0) //만났다면  
		{
			//if() //지금까지 환자 중 만난 시간이 가장 이른가?
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
            	printf("환자의 번호를 입력하세요:"); 
            	scanf("%i",&pIndex);  // 환자번호를 입력받는다.
            	printf("환자의 번호: %i\n",pIndex);  //환자번호를 출력한다.  
            	ifct_element = ifctdb_getData(pIndex); //입력받은 환자번호의 구조체 가져오기
            	ifctele_printElement(ifct_element);  // 나이, 시간, 장소 print 
                break;
                
            case MENU_PLACE:
            	char input_place[MAX_PLACENAME]; //문자열을 선언 
                printf("장소를 입력하세요:"); //장소를 문자열로 입력받고
				scanf("%s",input_place); // scanf함. 문자열 형태로 저장

				for(int i=0;i<pIndex+1;i++)
				{
					ifct_element = ifctdb_getData(i); // ifct_element 0,1,2,3,4,번째 data를 가져온다.  
					int number=ifctele_getHistPlaceIndex(ifct_element,4); //0,1,2,3,4...번째의 5번째 장소의 숫자를 함수로 받고 number에 저장합니다.  
					if (strcmp(ifctele_getPlaceName(number),input_place)==0 ) // 함수를 이용해 문자열로 바꾼 후 서로 비교합니다.  
					{
					    printf("환자번호: %i번\n",i);
						ifctele_printElement(ifct_element);  // 만약 맞으면 환자의 정보를 print 
					} 
			    }
                break;
                
            case MENU_AGE:
            	int a,b;
            	printf("최소 숫자를 입력하세요:");  
            	scanf("%d",&a);   //최소 숫자를 입력받음 
            	printf("최대 숫자를 입력하세요:");  
            	scanf("%d",&b);   //최대 숫자를 입력받음
            	for(int i=0;i<pIndex+1;i++)     //for문을 돌려서 데이터를 다 읽어 오게끔한다. 
            	{
            		ifct_element = ifctdb_getData(i); //i번째 데이터를 받아온다.  
            		if(ifctele_getAge(ifct_element)<=b&&age>=a)  // i번째 사람의 나이가 범위에 해당되는지 확인
					{
						printf("환자번호: %i번\n",i);
						ifctele_printElement(ifct_element);
					} 
				}
                break;
            
            case MENU_TRACK:
            	
            	int input_index;
				printf("환자번호를 입력하세요:");
			    scanf("%d",&input_index);  // 현재환자의 번호를 입력받는다.  
			    while(input_index<pIndex+1)  // 현재환자 번호가 범위 안에 포함된다.  
			    {
			    	ifct_element = ifctdb_getData(input_index); //현재환자의 정보를 가져온다.  
			    	int influencer=trackInfester(input_index,ifctele_getinfestedTime(ifct_element),ifctele_getHistPlaceIndex(ifct_element, N_HISTORY-1)); //전염자를 확인하기  
			    	if(influencer>0) //전파자가 존재하면
					{
						printf("%i 환자는 %i 환자에게 전파됨\n",input_index,influencer); //현재환자와 전파자에 대해 서술해준다. 
						printf("시점 %i, %s",ifctele_getinfestedTime(ifct_element)-4,ifctele_getHistPlaceIndex(ifct_element, 1)); //시점과 장소를 출력해준다.  
					}       
			    	else // 전파자가 없으면  
			    	    int First_influencer=influencer; //최초 전파자=현재환자
						break; //최초 전파자를 찾으면 while문 break 
					input_index=influencer; //현재환자=전파자 (다시 while문으로 돌아가야 하니깐)				 
				}
				 
                
                break;
                
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break; 
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
