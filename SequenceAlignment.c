#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b)  (a>b)?a:b

int main(void)
{
    /*input*/
    char* seq1;
    int n1=1000;
    int L1;
    seq1=(char*)malloc(sizeof(char)*n1);    //Allocate larger memory
    printf("First Sequence:");
    scanf("%s",seq1);
    L1=strlen(seq1);
    if ((n1-L1) > 10) {
        realloc(seq1,sizeof(char)*(L1+1));    //Preserve string content and reduce allocated memory
        n1= L1+1;
    }
    char* seq2;
    int n2=1000;
    int L2;
    seq2=(char*)malloc(sizeof(char)*n2);
    printf("Second Sequence:");
    scanf("%s",seq2);
    L2=strlen(seq2);
    if ((n2-L2) > 10) {
        realloc(seq2,sizeof(char)*(L2+1));
        n2= L2+1;
    }
    /*Initialize the scoring matrix: Set the value of the first row and first column of the scoring matrix*/
    int i,j; 

    struct MO      
    {
        int value;   //value
        int x,y;     //Position coordinates
    };
    struct MO Matrix[L2+1][L1+1];
    
    for(i=0;i<L2+1;i++)
        for(j=0;j<L1+1;j++)
            Matrix[i][j].value=-2*i-j*2;
    /*Scoring process*/
    int t,x,y;
    //The value of the first row of the matrix is determined from the coordinate point
    for(j=1;j<L1;j++){
        Matrix[0][j].x=0;
        Matrix[0][j].y=j-1;
    }
    //The value of the first column of the matrix is determined from the coordinate point
    for(i=1;i<L2;i++){
        Matrix[i][0].x=i-1;
        Matrix[i][0].y=0;
    }
    //The remaining row and column values of the matrix are determined from the coordinate points
    for(i=1;i<L2+1;i++){
        for(j=1;j<L1+1;j++){
            if(*(seq1+j-1)==*(seq2+i-1))
                t=Matrix[i-1][j-1].value+1;
            else
                t=Matrix[i-1][j-1].value-1;
        x=Matrix[i-1][j].value-2;   //x represents the value from the top
        y=Matrix[i][j-1].value-2;   //y represents the value from the left

        int m;
        m=t;
        Matrix[i][j].x=i-1;       //If the maximum score is from the upper left oblique, the point coordinate is (x,y)
        Matrix[i][j].y=j-1;
        if(m<x){
            m=x;
            Matrix[i][j].x=i-1;     //If the maximum score comes from the upper number, the point coordinate is (x,y)
            Matrix[i][j].y=j;
        }
        if(m<y){
            m=y;
            Matrix[i][j].x=i;
            Matrix[i][j].y=j-1;
        }
        Matrix[i][j].value=m;
        }
    }
    /*Format output scoring matrix*/
    printf("   \t");
    printf("%d\t",0);
    for(i=0;i<L1;i++)
        printf("%c\t",*(seq1+i));
    printf("\n");

    for(i=0;i<L2+1;i++){
        if(i==0){
            printf("%d\t",0);
            for(j=0;j<L1+1;j++)
                printf("%d\t",Matrix[i][j].value);

            printf("\n");
        }
        else{
            printf("%c\t",*(seq2+i-1));
            //Output rows of Matrix
            for(j=0;j<L1+1;j++)
                printf("%d\t",Matrix[i][j].value);

            printf("\n");
            }
        }
     /*Backtracking*/
t    int m=1;  //The condition of end of loop
    int k=0;
    int i2;
    int flag=0;   //scores
    int N=MAX(L1,L2);
    char s1[N],s2[N];
    for(i=L2,j=L1,k=1;m;){
        if(Matrix[i][j].x==i-1&&Matrix[i][j].y==j-1){     //If the value comes from the upper left
            s1[N-k]=*(seq1+j-1);
            s2[N-k]=*(seq2+i-1);
            if(*(seq1+j-1)==*(seq2+i-1))
                flag += 1;
            else
                flag -= 1;
        }
        else if(Matrix[i][j].x==i-1&&Matrix[i][j].y==j){    //If the value comes from above
            s1[N-k]='-';
            s2[N-k]=*(seq2+i-1);
            flag -= 2;
        }
        else {                                         //If the value comes from left
            s1[N-k]=*(seq1+j-1);
            s2[N-k]='-';
            flag -= 2;
        }
        i2=i;  //Prevent the next parameter i change after i=Matrix[i][j].x processing
        i=Matrix[i][j].x;
        j=Matrix[i2][j].y;
        k += 1;
        if((i==0)&&(j==0))
            m=0;

    }
    /*Retrospectively determined output of comparison sequences*/
    printf("\n");
    printf("\n");
    for(i=0;i<N;i++)
        printf("%c\t",s1[i]);
    printf("\n");
    for(i=0;i<N;i++)
        printf("%c\t",s2[i]);
    printf("\n");
    printf("Scores=%d",flag);   
    printf("\n");
}
