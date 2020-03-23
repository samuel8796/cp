#include<stdio.h>                                                           
#include<stdlib.h>
#include<stdbool.h>

struct Nodes{
   
    struct Nodes *next;
  
   
    int position[2];
};
typedef struct Nodes nodes;
typedef nodes *nodeptr;

nodeptr qhead,qback;

void makequeue();
void qpush(int a,int b);
void qpop();
bool empty();
int *qtop();
int shoow();

int shoow(){
    nodeptr temp;
    int counter=0;
    temp=qhead->next;
    while(temp!=NULL){
        counter++;
        temp=temp->next;

    }
    return counter;
    printf("\n");

}
int *qtop(){
    return qhead->next->position;

}

bool empty(){
    if(qhead->next==NULL){
        return true;
    }
    return false;

}

void makequeue(){
    qhead=qback= (nodes *)malloc(sizeof(nodes));
    qhead->next=NULL;
    qback->next=NULL;
}

void qpush(int a,int b){
    nodeptr newptr = (nodes *)malloc(sizeof(nodes));
    if(qhead->next==NULL)
        qhead->next=newptr;

    newptr->position[0]=a;
    newptr->position[1]=b;
    newptr->next=NULL;
    qback->next=newptr;
    qback=newptr;

}

void qpop(){
    nodeptr temp;
    if(qhead->next == NULL)
        return;
 
  
    temp=qhead;
    qhead=qhead->next;
    free(temp);
}


int main(void){
    int*now;
    int counter0=0,counter1=0;
    int max0=0,max1=0;
    int size_of_row=0,size_of_column=0;
    nodeptr curptr,headptr;
    scanf("%d %d\n",&size_of_row,&size_of_column);
    int ans;
    int cur_row=0,cur_column=0;
    bool v[size_of_row][size_of_column];
    int map[size_of_row][size_of_column];

    for(int i=0;i<size_of_row;i++){
        for(int j=0;j<size_of_column;j++){
            scanf("%d ",&map[i][j]);
            v[i][j]=false;
        }
    }





    makequeue();

    for(int i=0;i<size_of_row;i++){
        for(int j=0;j<size_of_column;j++){
            if(v[i][j]==false){

                v[i][j]=true;
                qpush(i,j);
        
                if(map[i][j]==0)
                    counter0++;
                if(map[i][j]==1)
                    counter1++;


                while(qhead->next!=NULL){
                    now=qtop();

                    if(v[*(now+0)+1][*(now+1)]==false && map[*(now+0)+1][*(now+1)]==map[*(now+0)][*(now+1)]){

                        v[*(now+0)+1][*(now+1)]=true;
                        qpush(*(now+0)+1,*(now+1));

                        if(map[*(now+0)][*(now+1)]==0)
                            counter0++;
                        if(map[*(now+0)][*(now+1)]==1)
                            counter1++;

                    }

                    if(v[*(now+0)-1][*(now+1)]==false && map[*(now+0)-1][*(now+1)]==map[*(now+0)][*(now+1)]){

                        v[*(now+0)-1][*(now+1)]=true;
                        qpush(*(now+0)-1,*(now+1));

                        if(map[*(now+0)][*(now+1)]==0)
                            counter0++;
                        if(map[*(now+0)][*(now+1)]==1)
                            counter1++;

                    }

                    if(v[*(now+0)][*(now+1)+1]==false && map[*(now+0)][*(now+1)+1]==map[*(now+0)][*(now+1)]){

                        v[*(now+0)][*(now+1)+1]=true;
                        qpush(*(now+0),*(now+1)+1);

                        if(map[*(now+0)][*(now+1)]==0)
                            counter0++;
                        if(map[*(now+0)][*(now+1)]==1)
                            counter1++;

                    }

                    if(v[*(now+0)][*(now+1)-1]==false && map[*(now+0)][*(now+1)-1]==map[*(now+0)][*(now+1)]){

                        v[*(now+0)][*(now+1)-1]=true;
                        qpush(*(now+0),*(now+1)-1);

                        if(map[*(now+0)][*(now+1)]==0)
                            counter0++;
                        if(map[*(now+0)][*(now+1)]==1)
                            counter1++;

                    }


                    qpop();

                }
                if(counter0 >max0)
                    max0=counter0;
                if(counter1 > max1)
                    max1=counter1;
                counter1=0;
                counter0=0;
            }

        }
    }

    ans=max1>max0?max1:max0;
    printf("%d",ans);





    return 0;

}
