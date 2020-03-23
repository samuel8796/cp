/**********************set _2048AI = 0 to play   2048   *************************/
/**********************set _2048AI = 1 to launch 2048 AI*************************/

/*I use conio.h handle console IO. You may need to change the library and the code according to your OS*/
/*If you don's want to play the game, simply remove this line and the corresponding _getch()*/
int _2048AI = 1;
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h> 

using namespace std;


int num = 2;
int num2 = 3;
int main(){
	int a = min(num,num2);
	cout<<a<<endl;
	
}

double PROB4 = 0.1;
int ok=0;
	float monweight = 0.1;
	float smoweight = 0.1;
	float empweight = 2.7;
	float maxweight = 0.5;

int FastLog2(int a) {
	if (a == 0) {
		return 0;
	}

	int count = 0;
	while (a != 1) {
		a = a >> 1; 
		count++;
	}
	return count;
}

// if you want to map a borad to a scord, call this function to map the board to an unsigned long long,
// and then map this unsigned long long to a score
unsigned long long BoardToULL(int board[4][4]) {
	unsigned long long h;
	int logBoard[4][4];
	int exp;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				logBoard[i][j] = 0;
			}
			else {
				logBoard[i][j] = FastLog2(board[i][j]);
			}
		}
	}


	h = 0;
	unsigned long long pow2 = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int temp = logBoard[i][j];
			for (int k = 8; k > 0; k = k >> 1) {
				if (temp >= k) {
					h = h | pow2;
					temp -= k;
				}

				pow2 = pow2 << 1;
			}
		}
	}

	return h;
}

//Copy the content of src to dst
void CopyBoard(int dst[4][4], int src[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

//return 1 if the contents of b1 and b2 are the same
//return 0 otherwise
int AreEqual(int b1[4][4], int b2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b1[i][j] != b2[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void PrintBoard(int board[4][4]) {
	for (int y = 0; y < 17; y++) {
		if (y % 4 == 0) {
			printf("*****************************\n");
		}
		else if (y % 4 == 1 || y % 4 == 3) {
			printf("*      *      *      *      *\n");
		}
		else {
			int i = y / 4;
			for (int j = 0; j < 4; j++) {
				printf("*");

				if (board[i][j] == 0) {
					printf("      ");
				}
				else if (board[i][j] < 10) {
					printf("   %d  ", board[i][j]);
				}
				else if (board[i][j] < 100) {
					printf("  %d  ", board[i][j]);
				}
				else if (board[i][j] < 1000) {
					printf("  %d ", board[i][j]);
				}
				else {
					printf(" %d ", board[i][j]);
				}
			}
			printf("*\n");
		}
	}

	return;
}

//print the old board, the action, and the new board
void PrintGame(int oldBoard[4][4], int newBoard[4][4], char a) {
	PrintBoard(oldBoard);
	if (a == 'w') {
		printf("\n\nUp\n\n");
	}
	else if (a == 's') {
		printf("\n\nDown\n\n");
	}
	else if (a == 'd') {
		printf("\n\nRight\n\n");
	}
	else if (a == 'a') {
		printf("\n\nLeft\n\n");
	}
	PrintBoard(newBoard);
}

//return the number of 0s in the board
int GetNEmptyPos(int b[4][4]) {
	int count = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b[i][j] == 0) {
				count++;
			}
		}
	}

	return count;
}

int GenNewNumber() {
	if ((double)rand() / (double)RAND_MAX < PROB4) {
		return 4;
	}
	return 2;
}

void InitBoard(int board[4][4]) {
	int initCol1, initRow1, initCol2, initRow2;
	initCol1 = rand() % 4;
	initRow1 = rand() % 4;

	initCol2 = rand() % 4;
	initRow2 = rand() % 4;

	while (initCol1 == initCol2 && initRow1 == initRow2) {
		initCol2 = rand() % 4;
		initRow2 = rand() % 4;
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	board[initCol1][initRow1] = GenNewNumber();
	board[initCol2][initRow2] = GenNewNumber();

	return;
}


void Shift(int board[4][4], int oldX, int oldY, int newX, int newY) {
	if (oldX == newX && oldY == newY) {
		return;
	}
	else {
		board[newX][newY] = board[oldX][oldY];
		board[oldX][oldY] = 0;
		return;
	}
}

void UpdateIthColumn(int board[4][4], int i, char a) {
	int dir = 1;
	int first = 0;
	if (a == 's') {
		dir = -1;
		first = 3;
	}

	int hasNumber = 0;
	int nextPos = 0;

	for (int j = first; j >= 0 && j < 4; j += dir) {
		if (board[j][i] > 0) {
			hasNumber = 1;
			Shift(board, j, i, first, i);
			nextPos = j + dir;
			break;
		}
	}

	if (!hasNumber) {
		return;
	}

	int mergePos = first;
	int emptyPos = first + dir;
	int hasMerged = 0;

	for (int j = nextPos; j >= 0 && j < 4; j += dir) {
		if (board[j][i] > 0) {
			if (!hasMerged && board[mergePos][i] == board[j][i]) {
				board[mergePos][i] = board[mergePos][i] << 1;
				board[j][i] = 0;
				hasMerged = 1;
			}
			else {
				Shift(board, j, i, emptyPos, i);
				mergePos = emptyPos;
				emptyPos += dir;
				hasMerged = 0;
			}
		}
	}
}

void UpdateIthRow(int board[4][4], int i, char a) {
	int dir = 1;
	int first = 0;
	if (a == 'd') {
		dir = -1;
		first = 3;
	}

	int hasNumber = 0;
	int nextPos = 0;

	for (int j = first; j >= 0 && j < 4; j += dir) {
		if (board[i][j] > 0) {
			hasNumber = 1;
			Shift(board, i, j, i, first);
			nextPos = j + dir;
			break;
		}
	}

	if (!hasNumber) {
		return;
	}

	int mergePos = first;
	int emptyPos = first + dir;
	int hasMerged = 0;

	for (int j = nextPos; j >= 0 && j < 4; j += dir) {
		if (board[i][j] > 0) {
			if (!hasMerged && board[i][mergePos] == board[i][j]) {
				board[i][mergePos] = board[i][mergePos] << 1;
				board[i][j] = 0;
				hasMerged = 1;
			}
			else {
				Shift(board, i, j, i, emptyPos);
				mergePos = emptyPos;
				emptyPos += dir;
				hasMerged = 0;
			}
		}
	}
}

int IsGameOver(int board[4][4]) {
	if (GetNEmptyPos(board) > 0) {
		return 0;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == board[i][j + 1]) {
				return 0;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == board[i + 1][j]) {
				return 0;
			}
		}
	}

	return 1;
}

void UpdateBoard(int board[4][4], char a) {
	if (a == 'w' || a == 's') {
		for (int i = 0; i < 4; i++) {
			UpdateIthColumn(board, i, a);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			UpdateIthRow(board, i, a);
		}
	}
	return;
}

void AddNewNumber(int board[4][4]) {
	int nEmptyPos = GetNEmptyPos(board);

	int r = 1 + rand() % nEmptyPos;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				r--;
				if (r == 0) {
					board[i][j] = GenNewNumber();
					break;
				}
			}
		}
	}
}

int smoothness(int b[4][4]){
int smooth=abs(FastLog2(b[0][1])-FastLog2(b[0][0]))+abs(FastLog2(b[1][0])-FastLog2(b[0][0]))+abs(FastLog2(b[0][2])-FastLog2(b[0][1]))+abs(FastLog2(b[1][1])-FastLog2(b[0][1]))+abs(FastLog2(b[0][3])-FastLog2(b[0][2]))+abs(FastLog2(b[1][2])-FastLog2(b[0][2]))+abs(FastLog2(b[1][3])-FastLog2(b[0][3]))+abs(FastLog2(b[1][1])-FastLog2(b[1][0]))+abs(FastLog2(b[2][0])-FastLog2(b[1][0]))+abs(FastLog2(b[1][2])-FastLog2(b[1][1]))+abs(FastLog2(b[2][1])-FastLog2(b[1][1]))+abs(FastLog2(b[1][3])-FastLog2(b[1][2]))+abs(FastLog2(b[2][2])-FastLog2(b[1][2]))+abs(FastLog2(b[2][3])-FastLog2(b[1][3]))+abs(FastLog2(b[2][1])-FastLog2(b[2][0]))+abs(FastLog2(b[3][0])-FastLog2(b[2][0]))+abs(FastLog2(b[2][2])-FastLog2(b[2][1]))+abs(FastLog2(b[3][1])-FastLog2(b[2][1]))+abs(FastLog2(b[2][3])-FastLog2(b[2][2]))+abs(FastLog2(b[3][2])-FastLog2(b[2][2]))+abs(FastLog2(b[3][3])-FastLog2(b[2][3]));

	
	
	
	return smooth*=(-1);
 	
	
	
}
int big(int a,int b){
	
	if(a>b)
		return a;
	else
		return b;
	
	
	
}

int monotonicity(int b[4][4]){
	
	int upbig=0,downbig=0,rightbig=0,leftbig=0;
	
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(b[j+1][i]>b[j][i]){
				if(b[j][i]==0){
					continue;
				}
				downbig+=(FastLog2(b[j+1][i])-FastLog2(b[j][i]));
			
			}
			
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(b[j+1][i]<b[j][i]){
				if(b[j+1][i]==0){
					continue;
				}
				upbig+=(FastLog2(b[j][i])-FastLog2(b[j+1][i]));
			
			}
			
		}
	}

	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(b[i][j+1]<b[i][j]){
				if(b[i][j+1]==0){
					continue;
				}
				rightbig+=(FastLog2(b[i][j])-FastLog2(b[i][j+1]));
			
			}
			
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(b[i][j+1]>b[i][j]){
				if(b[i][j]==0){
					continue;
				}
				leftbig+=(FastLog2(b[i][j+1])-FastLog2(b[i][j]));
			
			}
			
		}
	}
	
	
	
	upbig*=(-1);
	rightbig*=(-1);
	leftbig*=(-1);
	downbig*=(-1);
	int mon=(big(upbig,downbig)+big(leftbig,rightbig));
	return mon; 
	

	
}

float emptyvalue(int emptynum){
	
	if(emptynum==1)
	return 0;
	if(emptynum==2)
	return 0.69;
	if(emptynum==3)
	return 1.09;
	if(emptynum==4)
	return 1.38;
	if(emptynum==5)
	return 1.6;
	if(emptynum==6)
	return 1.79;
	if(emptynum==7)
	return 1.94;
	if(emptynum==8)
	return 2.07;
	if(emptynum==9)
	return 2.19;
	if(emptynum==10)
	return 2.3;
	if(emptynum==11)
	return 2.39;
	if(emptynum==12)
	return 2.48;
	if(emptynum==13)
	return 2.56;
	if(emptynum==14)
	return 2.63;
	
	
}

int Maxvalue(int b[4][4]){
	
	int max=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(b[i][j]>max)
				max=b[i][j];
		}
	}
	
	return FastLog2(max);
	
}



char AIGenNextMove(int newb[4][4]);


float NextMove(int wors[4][4]);

float worstcase2(int curb[4][4]){
	ok++;

		
	float sec=0.0,key=0.0;
	float worst1=0.0,worst2=0.0;
	unsigned long long temp,worstarr[32];
	bool skip=false;
	int worstb[4][4],map[4][4]={0};
	int worst=0,mapvalue=0;

	CopyBoard(worstb,curb);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(curb[i][j]!=0)
				map[i][j]=2;
			
		}
	}
	
	
	for(;;){
		//cout<<"fuck"<<endl;
		mapvalue=0;
		//worst1=0.0;
		skip=false;
		
		
		CopyBoard(worstb,curb);
		AddNewNumber(worstb);
		temp = BoardToULL(worstb);
		for(int i=0;i<32;i++){
			if(worstarr[i]==temp)
				skip=true;
		}
		
		
		if(skip==false){
			
		
		
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					if(map[i][j]!=2&&worstb[i][j]!=0)
						map[i][j]+=1;
						
					
				}
			}
			int value = monotonicity(worstb)*monweight+smoothness(worstb)*smoweight+Maxvalue(worstb)*maxweight+emptyvalue(GetNEmptyPos(worstb))*empweight;	
		//if(value<worst)
			worst1 += value;
		   // worst2 += sec;
			key++;
			
		}
		
		
		
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(map[i][j]==2)
					mapvalue+=1;
			
			}
		}
	

		//cout<<mapvalue<<endl;
	   if(mapvalue==16){
	    //cout<<worst<<endl;
	    
	    return worst1/key;
	   
	     	
		}
		
	}
	
}

float worstcase(int curb[4][4],int a){
	ok++;
	a=0;
		
	float sec=0.0,key=0.0;
	float worst1=0.0,worst2=0.0;
	unsigned long long temp,worstarr[32]={0};
	bool skip=false;
	int worstb[4][4],map[4][4]={0};
	int worst=0,mapvalue=0;

	CopyBoard(worstb,curb);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(curb[i][j]!=0)
				map[i][j]=2;
			
		}
	}
	
	
	for(;;){
		//cout<<"fuck"<<endl;
		mapvalue=0;
	//	worst1=0.0;
		skip=false;
		
		
		CopyBoard(worstb,curb);
		AddNewNumber(worstb);
		temp = BoardToULL(worstb);
		for(int i=0;i<32;i++){
			if(worstarr[i]==temp)
				skip=true;
		}
		
		
		if(skip==false){
			
			sec=NextMove(worstb);
		
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					if(map[i][j]!=2&&worstb[i][j]!=0)
						map[i][j]+=1;
						
					
				}
			}
			int value = monotonicity(worstb)*monweight+smoothness(worstb)*smoweight+Maxvalue(worstb)*maxweight+emptyvalue(GetNEmptyPos(worstb))*empweight;	
		//cout<<monotonicity(worstb)*monweight<<smoothness(worstb)*smoweight<<Maxvalue(worstb)*maxweight<<emptyvalue(GetNEmptyPos(worstb))*empweight<<endl;
		//if(value<worst)
			worst1 += value;
		    worst2 += sec;
			key++;
			
		}
		
		
		
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(map[i][j]==2)
					mapvalue+=1;
			
			}
		}
	

	//cout<<key<<endl;
	   if(mapvalue==16){
	    //cout<<worst<<endl;
	    
	    return worst1/key+worst2/key;
	   
	     	
		}
		
	}
	
	
	
}
float NextMove(int curb[4][4]){
	float m[4],equal=-0.03;
	
//	int old[4][4];
	
	float key=0.0;
	float worst1=0.0;
	unsigned long long temp,worstarr[32]={0};
	bool skip=false;
	int worstb[4][4],map[4][4]={0};
	int worst=0,mapvalue=0;

		
	CopyBoard(worstb,curb);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(curb[i][j]!=0)
				map[i][j]=2;
			
		}	
	}
	
	
	char move = 'w';	
	int oldb[4][4];
	CopyBoard(oldb,worstb);
	UpdateBoard(worstb,move);
	if (!AreEqual(worstb, oldb)) {
	//	cout<<"f"<<endl;
	//AddNewNumber(worstb);
	m[0]=worstcase2(worstb);
	
	}
	else
		m[0]=equal;
		
	//	key=0;

	


	move = 's';	
	
	CopyBoard(oldb,worstb);
	UpdateBoard(worstb,move);
	if (!AreEqual(worstb, oldb)) {	
	//cout<<"f"<<endl;
	m[1]=worstcase2(worstb);
		
	}
	else
		m[1]=equal;



	
	move = 'd';	
	
	CopyBoard(oldb,worstb);
	UpdateBoard(worstb,move);
	if (!AreEqual(worstb, oldb)) {	
		m[2]=worstcase2(worstb);	
		
	}
	else
		m[2]=equal;



	move = 'a';	

	CopyBoard(oldb,worstb);
	UpdateBoard(worstb,move);
	if (!AreEqual(worstb, oldb)) {	
	m[3]=worstcase2(worstb);	
		
	}
	else
		m[3]=equal;

	
	
	
	
	
	
	
	
return (m[1]+m[0]+m[2]+m[3])/4;
	
	
	//return m[0];
	
}

float maximum(float a,float b,float c,float d){ 



    float hold=-100;

    if(a>hold){

        hold=a;

    }   

    if(b>hold){

        hold=b;

    }   

    if(c>hold){

        hold=c;

    }   

    if(d>hold){

        hold=d;

    }   

   

    return hold;



}
float up(int b[4][4]){



    int c[4][4];

   
    CopyBoard(c,b);

    UpdateBoard(c,'w');

    if(AreEqual(c,b))

        return -100;

    AddNewNumber(c);

    int w[4][4],a[4][4],s[4][4],d[4][4];

    CopyBoard(w,c);

    CopyBoard(a,c);

    CopyBoard(s,c);

    CopyBoard(d,c);

    UpdateBoard(w,'w');

    UpdateBoard(a,'a');

    UpdateBoard(s,'s');

    UpdateBoard(d,'d');

    float Max1,Max2,Max3,Max4;

    Max1= smoweight*smoothness(w)+monotonicity(w)+empweight*emptyvalue(GetNEmptyPos(w))+Maxvalue(w);

    Max2= smoweight*smoothness(a)+monotonicity(a)+empweight*emptyvalue(GetNEmptyPos(a))+Maxvalue(a);

    Max3= smoweight*smoothness(s)+monotonicity(s)+empweight*emptyvalue(GetNEmptyPos(s))+Maxvalue(s);

    Max4= smoweight*smoothness(d)+monotonicity(d)+empweight*emptyvalue(GetNEmptyPos(d))+Maxvalue(d);

   


    return maximum(Max1,Max2,Max3,Max4);

}

float down(int b[4][4]){



    int c[4][4];


    CopyBoard(c,b);

    UpdateBoard(c,'s');

    if(AreEqual(c,b))

        return -100;

    AddNewNumber(c);

    int w[4][4],a[4][4],s[4][4],d[4][4];

    CopyBoard(w,c);

    CopyBoard(a,c);

    CopyBoard(s,c);

    CopyBoard(d,c);

    UpdateBoard(w,'w');

    UpdateBoard(a,'a');

    UpdateBoard(s,'s');

    UpdateBoard(d,'d');

    float Max1,Max2,Max3,Max4;

     Max1= smoweight*smoothness(w)+monotonicity(w)+empweight*emptyvalue(GetNEmptyPos(w))+Maxvalue(w);

    Max2= smoweight*smoothness(a)+monotonicity(a)+empweight*emptyvalue(GetNEmptyPos(a))+Maxvalue(a);

    Max3= smoweight*smoothness(s)+monotonicity(s)+empweight*emptyvalue(GetNEmptyPos(s))+Maxvalue(s);

    Max4= smoweight*smoothness(d)+monotonicity(d)+empweight*emptyvalue(GetNEmptyPos(d))+Maxvalue(d);
   


    return maximum(Max1,Max2,Max3,Max4);



}



float left(int b[4][4]){



    int c[4][4];

   
    CopyBoard(c,b);

    UpdateBoard(c,'a');

    if(AreEqual(c,b))

        return -100;

    AddNewNumber(c);

    int w[4][4],a[4][4],s[4][4],d[4][4];

    CopyBoard(w,c);

    CopyBoard(a,c);

    CopyBoard(s,c);

    CopyBoard(d,c);

    UpdateBoard(w,'w');

    UpdateBoard(a,'a');

    UpdateBoard(s,'s');

    UpdateBoard(d,'d');

    float Max1,Max2,Max3,Max4;

   Max1= smoweight*smoothness(w)+monotonicity(w)+empweight*emptyvalue(GetNEmptyPos(w))+Maxvalue(w);

    Max2= smoweight*smoothness(a)+monotonicity(a)+empweight*emptyvalue(GetNEmptyPos(a))+Maxvalue(a);

    Max3= smoweight*smoothness(s)+monotonicity(s)+empweight*emptyvalue(GetNEmptyPos(s))+Maxvalue(s);

    Max4= smoweight*smoothness(d)+monotonicity(d)+empweight*emptyvalue(GetNEmptyPos(d))+Maxvalue(d);
   


    return maximum(Max1,Max2,Max3,Max4);



}





float right(int b[4][4]){



    int c[4][4];

   

    CopyBoard(c,b);

    UpdateBoard(c,'d');

    if(AreEqual(c,b))

        return -100;

    AddNewNumber(c);

    int w[4][4],a[4][4],s[4][4],d[4][4];

    CopyBoard(w,c);

    CopyBoard(a,c);

    CopyBoard(s,c);

    CopyBoard(d,c);

    UpdateBoard(w,'w');

    UpdateBoard(a,'a');

    UpdateBoard(s,'s');

    UpdateBoard(d,'d');

    float Max1,Max2,Max3,Max4;

   Max1= smoweight*smoothness(w)+monotonicity(w)+empweight*emptyvalue(GetNEmptyPos(w))+Maxvalue(w);

    Max2= smoweight*smoothness(a)+monotonicity(a)+empweight*emptyvalue(GetNEmptyPos(a))+Maxvalue(a);

    Max3= smoweight*smoothness(s)+monotonicity(s)+empweight*emptyvalue(GetNEmptyPos(s))+Maxvalue(s);

    Max4= smoweight*smoothness(d)+monotonicity(d)+empweight*emptyvalue(GetNEmptyPos(d))+Maxvalue(d);
    

    return maximum(Max1,Max2,Max3,Max4);



}





char AIGenNextMove(int newb[4][4]) {
					 				 
	float m[4],hold;
	
	int wall=-1000;
	char move = 'w';	
	int oldb[4][4];
	CopyBoard(oldb,newb);
	UpdateBoard(newb,move);
	if (!AreEqual(newb, oldb)) {	
	 m[0] = maximum(up(newb),left(newb),down(newb),right(newb));
	//cout<<"w is:"<<m[0]<<endl;
	}
	else
		m[0]=wall;

	

	
	
	move = 's';	
	CopyBoard(newb,oldb);
	UpdateBoard(newb,move);
	if (!AreEqual(newb, oldb)) {
		m[1]=maximum(up(newb),left(newb),down(newb),right(newb));
	
//	cout<<"s is:"<<m[1]<<endl;
	}
	else
		m[1]=wall;
		
		




	move = 'd';	
	CopyBoard(newb,oldb);
	UpdateBoard(newb,move);
	if (!AreEqual(newb, oldb)) {
		m[2]=maximum(up(newb),left(newb),down(newb),right(newb));
	//cout<<"d is:"<<m[2]<<endl;
	}
	else
		m[2]=wall;
	
	
	
	
	
	move = 'a';	
	CopyBoard(newb,oldb);
	UpdateBoard(newb,move);
	if (!AreEqual(newb, oldb)) {
		m[3]=maximum(up(newb),left(newb),down(newb),right(newb));
	//cout<<"a is:"<<m[3]<<endl;
	}
	else
		m[3]=wall;
	
	
	
	//cout<<m[0]<<m[1]<<m[2]<<m[3]<<endl;
	
	
	if(m[0]>m[1]&&m[0]>m[2]&&m[0]>m[3])
		move = 'w';
	if(m[1]>m[0]&&m[1]>m[2]&&m[1]>m[3])
		move = 's';
	if(m[2]>m[1]&&m[2]>m[0]&&m[2]>m[3])
		move = 'd';
	if(m[3]>m[1]&&m[3]>m[2]&&m[3]>m[0])
		move = 'a';
		 	 	 	 //cout<<"fuck"<<endl;
		 
					 
	
	return move;
}

int main() {
	int board[4][4];
	int oldBoard[4][4];
	srand(time(NULL));
	InitBoard(board);
	PrintBoard(board);


	for (;;) {
		char c;
		CopyBoard(oldBoard, board);

		if (!_2048AI) {
		
			c = _getch();
			if (c != 'w' && c != 's' && c != 'a' && c != 'd') {
				printf("\n\n please press w, s, a, or d\n");
				continue;
			}
		}
		else {
		//	cout<<"fuck"<<endl;
			c = AIGenNextMove(oldBoard);
		}
     	
		UpdateBoard(board, c);

		if (!AreEqual(board, oldBoard)) {
			AddNewNumber(board);

// I use system("cls") to clear screen. Change the code according to your OS.
			system("cls");
// I use system("cls") to clear screen. Change the code according to your OS.

			PrintGame(oldBoard, board, c);
		}

		if (IsGameOver(board)) {
			printf("\n\n Game Over!!\n\n");
			getchar();
		}
	}

	return 0;
}

