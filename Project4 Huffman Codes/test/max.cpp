#include <stdio.h>
#include <stdlib.h>
#define MaxSize 500
typedef struct{
    char c;                       //代码;
    int w;                       //代码权值;
    char code[MaxSize];           //代码的Huffman编码;
}HTCode,HuffCode[MaxSize];

typedef struct{
    int Weight;                   //权值;
    int LChild,RChild,Parent;
}HTNode,HuffTree[MaxSize];
//================================================================================
void HuffmanTree(HuffTree HT,int length,HuffCode hc);        //生成Huffman树;
void SelectHTNode(HuffTree HT,int n,int *min1,int *min2);    //查找最小和次小序号;
void HuffmanCode(HuffTree HT,int len,HuffCode hc);            //生成Huffman编码;
//================================================================================
int main(void)
{
    HuffTree HT;       //Huffman树;
    HuffCode HC;       //Huffman编码;
    int i,len;
    len=63;
	printf("%d\n",len);
    char c='A';
	for(i=1;i <= len;i++)
    {
        HC[i].c = c;
		if(c=='Z'){
			c='a';
		}else if(c=='z'){
			c='0';
		}
		else if(c=='9'){
			c='_';
		}else{
			c++;
		}
		
        HC[i].w=rand()%100+1;
        printf("%c %d ",HC[i].c,HC[i].w);
    }
    printf("\n");
    HuffmanTree(HT,len,HC);
    HuffmanCode(HT,len,HC);
    for(i = 1;i<=len;i++)
    {
        printf("%c ",HC[i].c);
        puts(HC[i].code);
        //printf("\n");
    }

    return 0;
}
//================================================================================
void HuffmanTree(HuffTree HT,int length,HuffCode hc)       //Huffman树初始化;
{
    int i,min1,min2;
    HT[0].Weight = 65535;
    for(i = 1;i <= length;i++)
    {
        HT[i].Weight = hc[i].w;
        HT[i].LChild = HT[i].RChild = HT[i].Parent = -1;
    }
    for(;i < 2*length;i++)            //i初值 = length+1;
    {
        HT[i].LChild = HT[i].RChild = HT[i].Parent = -1;
    }
    for(i = length+1;i < 2*length;i++)
    {
        SelectHTNode(HT,i,&min1,&min2);
        HT[min1].Parent = i;
        HT[min2].Parent = i;
        HT[i].LChild = min1;
        HT[i].RChild = min2;
        HT[i].Weight = HT[min1].Weight + HT[min2].Weight;
    }
}
//================================================================================
void SelectHTNode(HuffTree HT,int n,int *min1,int *min2)    //查找最小和次小序号;
{
    int i;
    *min1 = *min2 = 0;
    for(i = 1;i < n;i++)
    {
        if(HT[i].Parent == -1)
        {
            if(HT[*min1].Weight >= HT[i].Weight)
            {
                *min2 = *min1;
                *min1 = i;
            }
            else if(HT[*min2].Weight > HT[i].Weight)    *min2 = i;
        }
    }
}
//================================================================================
void HuffmanCode(HuffTree HT,int len,HuffCode hc)         //生成Huffman编码;
{
    int i,j,tc,Stack[MaxSize],top = -1;
    char flag[MaxSize];
    HTNode th;
    for(i = 1;i <= len;i++)
    {
        top = -1;                        //栈初始化;
        j = 0;                            //hc[i].code串首位置偏移;
        th = HT[i];                        //当前结点th;
        tc = i;                            //当前结点标记tc;
        while(th.Parent != -1)
        {            //当前结点th双亲P入栈,由P的孩子是th,确定flag;确定下次结点标记tc;
            //printf("%d,%d\n",top,th.Parent);
			Stack[++top] = th.Parent;
            if(HT[th.Parent].LChild == tc)    {flag[top] = 'L'; tc = th.Parent;}
            if(HT[th.Parent].RChild == tc)    {flag[top] = 'R'; tc = th.Parent;}
            th = HT[Stack[top]];        //下一结点;
        }                               
        while(top != -1)
        {
            if(flag[top] == 'L')    hc[i].code[j++] ='0';
            else                    hc[i].code[j++] ='1';
            Stack[top--];                //出栈;
        }
        hc[i].code[j] ='/0';            //当前串结束;
    }         
}

