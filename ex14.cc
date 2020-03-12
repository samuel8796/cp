#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

int main(void){
    int num,flag,fc=0;
    cin>>num;
    double Xroom[num],Yroom[num];
    int X[num],Y[num];
    int N; 
    N = (num*(num-1))/2;
    double xd,yd,x,y;
    int map[num][num] ;

    for(int i =0;i<num;i++){
        for(int j=0;j<num;j++){
            map[i][j] = 0;
        }
    }


    for(int i=0;i<num;i++){
        scanf("%d ",&X[i]);
        scanf("%d ",&Y[i]);
        map[Y[i]][X[i]] = 1;
        //  cout<<X[i]<<Y[i]<<endl;
    }
    int rc =0;
    for(int i =0;i<num;i++){
        for(int j=0;j<num;j++){
            if(map[i][j]==1){
                Xroom[rc] = j;
                Yroom[rc] = i;
                rc++;
            }
        }

    }
    num = rc;
    for(int i=0;i<num;i++){
   //     cout<<Xroom[i]<<Yroom[i]<<endl;
    }

    N = (num*(num-1))/2;
    double slopes[N];


    int counter = 0;
    for(int i = 0;i < num;i++){
        for(int j = i+1;j<num;j++){
            xd = Xroom[i] - Xroom[j];
            yd = Yroom[i] - Yroom[j];
            if(xd == 0){
                slopes[counter] = 100000000000;
                counter++;
            }
            else{
                slopes[counter] = yd/xd;
                counter++;

            }
        }   
    }
    //cout<<N<<endl;
    double temp;
    for (int i = N-1;i>0;i--){
        for(int j = 0; j <= i-1;j++){
            if(slopes[j]>slopes[j+1]){
                temp = slopes[j];
                slopes[j] = slopes[j+1];
                slopes[j+1] = temp;
            }
        }
    } 
   // for(int i=0;i<N;i++)
        //cout<<slopes[i]<<endl;


    temp = slopes[0];
    //cout<<temp<<endl;
    int same_counter = 1,max = 1;
    for(int i = 1;i<N+1;i++){
      //  cout<<slopes[i]<<endl;
        if(slopes[i] == temp)
            same_counter++;
        else{
            temp = slopes[i];
            same_counter = 1;
        }
        if(same_counter > max)
            max = same_counter;
    }
    int ans;
    ans = (sqrt(max*8+1)+1)/2;
    //cout<<max<<endl;
    cout<<ans<<endl;


    return 0;
}


