#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b)  (a>b)?a:b

int main(void)
{
    /*输入*/
    char* seq1;
    int n1=1000;
    int L1;
    seq1=(char*)malloc(sizeof(char)*n1);    //先分配较大的内存（1000字节）
    printf("First Sequence:");
    scanf("%s",seq1);
    L1=strlen(seq1);
    if ((n1-L1) > 10) {
        realloc(seq1,sizeof(char)*(L1+1));    //保留字符串内容不动，并缩小分配的内存
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
    /*初始化打分矩阵：设定打分矩阵第一行与第一列的值，矩阵其余部分值无所谓*/
    int i,j;  //循环值

    struct MO      //定义结构体，结构体名为MO
    {
        int value;   //值
        int x,y;     //该值来自于的位置坐标
    };
    struct MO Matrix[L2+1][L1+1];
    
    for(i=0;i<L2+1;i++)
        for(j=0;j<L1+1;j++)
            Matrix[i][j].value=-2*i-j*2;
    /*打分过程*/
    int t,x,y;
    //矩阵第一行的值来自坐标点的确定
    for(j=1;j<L1;j++){
        Matrix[0][j].x=0;
        Matrix[0][j].y=j-1;
    }
    //矩阵第一列的值来自坐标点的确定
    for(i=1;i<L2;i++){
        Matrix[i][0].x=i-1;
        Matrix[i][0].y=0;
    }
    //矩阵第其余行、列值来自坐标点的确定
    for(i=1;i<L2+1;i++){
        for(j=1;j<L1+1;j++){
            if(*(seq1+j-1)==*(seq2+i-1))
                t=Matrix[i-1][j-1].value+1;
            else
                t=Matrix[i-1][j-1].value-1;
        x=Matrix[i-1][j].value-2;   //x表示来自上边的值
        y=Matrix[i][j-1].value-2;   //y表示来自左方的值

        int m;
        m=t;
        Matrix[i][j].x=i-1;       //若最大得分来自左斜上方，该点坐标为(x，y)
        Matrix[i][j].y=j-1;
        if(m<x){
            m=x;
            Matrix[i][j].x=i-1;     //若最大得分来自上边的数，该点坐标为(x，y)
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
    /*格式输出打分矩阵*/
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
            //输出Matrix的行
            for(j=0;j<L1+1;j++)
                printf("%d\t",Matrix[i][j].value);

            printf("\n");
            }
        }
     /*回溯*/
    int m=1;  //循环结束条件
    int k=0;
    int i2;
    int flag=0;   //分数scores
    int N=MAX(L1,L2);
    char s1[N],s2[N];
    for(i=L2,j=L1,k=1;m;){
        if(Matrix[i][j].x==i-1&&Matrix[i][j].y==j-1){     //若该值来自于左上
            s1[N-k]=*(seq1+j-1);
            s2[N-k]=*(seq2+i-1);
            if(*(seq1+j-1)==*(seq2+i-1))
                flag += 1;
            else
                flag -= 1;
        }
        else if(Matrix[i][j].x==i-1&&Matrix[i][j].y==j){    //若该值来自于上方
            s1[N-k]='-';
            s2[N-k]=*(seq2+i-1);
            flag -= 2;
        }
        else {                                         //若该值来自于左方
            s1[N-k]=*(seq1+j-1);
            s2[N-k]='-';
            flag -= 2;
        }
        i2=i;  //防止经过i=Matrix[i][j].x处理后下一步的参数i变化!!!
        i=Matrix[i][j].x;
        j=Matrix[i2][j].y;
        k += 1;
        if((i==0)&&(j==0))
            m=0;

    }
    /*回溯确定的对比序列的输出*/
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
