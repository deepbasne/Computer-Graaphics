#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define SAMPLE_ROW 64
#define SAMPLE_COL 64
#define NEW_ROW 160
#define NEW_COL 160
#define WINSIZE 5
#define ErrThreshold 0.1
#define MAXERRTHRESHOLD 0.3
#define MAXNEIGHBOR 10000

// got help from online source
int compare(const void *a,const void *b)
{
    return *((double *)a)-*((double *)b);
}
void createFilter(double gKernel[][WINSIZE],int winsize,double sigma)
{
    // set standard deviation to 1.0
    double r, s = 2.0 * sigma * sigma;
    // sum is for normalization
    double sum = 0.0;
    int i,j,x,y,w = winsize/2;
    // generate 5x5 kernel
    for(x=-w;x<=w;x++){
        for(y=-w;y<=w;y++){
            r = x*x+y*y;
            gKernel[x+w][y+w] = (exp(-(r)/s))/(M_PI*s);
            sum += gKernel[x+w][y+w];
        }
    }
    // normalize the Kernel
    for(i=0;i<winsize;++i){
        for(j=0;j<winsize;++j){
            gKernel[i][j] /= sum;
            //printf("%f  ",gKernel[i][j]);
        }
        printf("\n");
    }
}
void GetUnfilledNeighbors(unsigned int filled[][NEW_COL],int pixel[][2],int r,int c)
{
    int i,j,a,b,count,f[NEW_ROW][NEW_COL];
    count = 0;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            f[i][j] = filled[i][j];
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(f[i][j]==1){
                for(a=i-1;a<r&&a<i+2;a++){
                    for(b=j-1;b<c&&b<j+2;b++){
                        if(f[a][b]!=1&&f[a][b]!=2){
                            if(count<MAXNEIGHBOR){
                                pixel[count][0] = a;
                                pixel[count++][1] = b;
                                //printf("unfilled %d %d\n",a,b);
                            }
                            f[a][b] = 2;
                        }
                    }
                }
            }
        }
    }
    //printf("2\n");
    pixel[count][0] = pixel[count][1] = -1;
}
double dist(unsigned char a[],unsigned char b[])
{
    int i,t,s,d=0;
    for(i=0;i<2;i++){
        t = (int)a[i];
        s = (int)b[i];
        d += (t-s)*(t-s);
    }
    return (double)d;
}

void FindMatches(unsigned char s[][SAMPLE_COL][3],unsigned char t[][WINSIZE][3],unsigned int vMask[][WINSIZE],double gMask[][WINSIZE],int matches[][2],double SSD[][SAMPLE_COL])
{
    int i,j,m,n,c,k;
    int w = WINSIZE/2;
    double weight = 0.0,min=1000000000.0;
    for(i=0;i<SAMPLE_ROW;i++)
        for(j=0;j<SAMPLE_COL;j++)
            SSD[i][j] = 0.0;
    
    for(i=0;i<WINSIZE;i++)
        for(j=0;j<WINSIZE;j++)
            weight += gMask[i][j]*(double)vMask[i][j];
    
    for(i=0;i<SAMPLE_ROW;i++){
        for(j=0;j<SAMPLE_COL;j++){
            
            for(m=-w;m<=w;m++){
                for(n=-w;n<=w;n++){
                    if(i+m>=0&&j+n>=0&&i+m<SAMPLE_ROW&&j+n<SAMPLE_COL){
                        for(k=0;k<3;k++)
                            SSD[i][j] += (s[i+m][j+n][k]-t[m+w][n+w][k])*(s[i+m][j+n][k]-t[m+w][n+w][k])*((double)vMask[m+w][n+w])*gMask[m+w][n+w];
                        
                    }
                }
            }
            SSD[i][j] /= weight;
            if(SSD[i][j]<min){
                min = SSD[i][j];
                matches[0][0] = i;
                matches[0][1] = j;
            }
        }
    }
    min *= (1+ErrThreshold);
    c = 1;
    for(i=0;i<SAMPLE_ROW;i++)
        for(j=0;j<SAMPLE_COL;j++)
            if(SSD[i][j]<min){
                matches[c][0] = i;
                matches[c++][1] = j;
            }
    matches[c][0] = matches[c][1] = -1;
}
int main(int argc,char *argv[])
{
    srand(time(NULL));
    FILE *input,*output;
    unsigned char in[SAMPLE_ROW][SAMPLE_COL][3];
    unsigned char out[NEW_ROW][NEW_COL][3];
    unsigned char template[WINSIZE][WINSIZE][3];
    unsigned int filled[NEW_ROW][NEW_COL],validMask[WINSIZE][WINSIZE];
    double gaussianMask[WINSIZE][WINSIZE],SSD[SAMPLE_ROW][SAMPLE_COL];
    double MaxErrThreshold = MAXERRTHRESHOLD;
    unsigned char t[100];
    int i,j,k,m,p;
    int newRow,newCol,npixels,nfilled,randRow,randCol;
    int seedSize,progress,rowStart,colStart;
    int seed[3][3],pixel[MAXNEIGHBOR][2];
    int matches[2000][2];
    char cc;
    newRow = NEW_ROW;
    newCol = NEW_COL;
    input = fopen(argv[1],"r+");
    output = fopen(argv[2],"w+");
    fread(t,sizeof(unsigned char),54,input);
    *(unsigned int *)(t+2) = 196662;
    *(unsigned int *)(t+0x12) = newRow;
    *(unsigned int *)(t+0x16) = newCol;
    fwrite(t,sizeof(unsigned char),54,output);
    printf("%d\n",*(unsigned int *)(t+2));
    printf("%d\n",*(unsigned int *)(t+0x12));
    printf("%d\n",*(unsigned int *)(t+0x16));
    fseek(input,54,SEEK_SET);
    fseek(output,54,SEEK_SET);
    fread(in,3,SAMPLE_ROW*SAMPLE_COL,input);

    for(i=0;i<newRow;i++){
        for(j=0;j<newCol;j++){
            filled[i][j] = 0;
            out[i][j][0] = out[i][j][0] = out[i][j][0] = (unsigned char)0;
        }
    }
    seedSize = 3;
    npixels = newRow*newCol;
    nfilled = seedSize*seedSize;
  
    randRow = SAMPLE_ROW/3;
    randCol = SAMPLE_COL/2;
   
    for(i=0;i<seedSize;i++){
        for(j=0;j<seedSize;j++){
            filled[newRow/2+i][newCol/2+j] = 1;
            for(k=0;k<3;k++)
                out[newRow/2+i][newCol/2+j][k] = in[randRow+i][randCol+j][k];
        }
    }
    
    createFilter(gaussianMask,WINSIZE,WINSIZE/6.4);
    while(nfilled<npixels){
        
        progress = 0;
        GetUnfilledNeighbors(filled,pixel,NEW_ROW,NEW_COL);
        p = 0;
        while(pixel[p][0]>=0){
            
            rowStart = pixel[p][0]-(WINSIZE/2);
            colStart = pixel[p][1]-(WINSIZE/2);
            for(i=0;i<WINSIZE;i++){
                for(j=0;j<WINSIZE;j++){
                    validMask[i][j] = 0;
                    template[i][j][0] =
                    template[i][j][1] =
                    template[i][j][2] = (unsigned char)0;
                }
            }
        
            for(i=rowStart;i<rowStart+WINSIZE;i++){
                if(i<0||i>newRow-1) continue;
                for(j=colStart;j<colStart+WINSIZE;j++){
                    if(j<0||j>newCol-1) continue;
                    validMask[i-rowStart][j-colStart] = filled[i][j];
                    for(k=0;k<3;k++)
                        template[i-rowStart][j-colStart][k] = in[i][j][k];
                }
            }
            FindMatches(in,template,validMask,gaussianMask,matches,SSD);
            m = 0;
            if(SSD[matches[m][0]][matches[m][1]]<MaxErrThreshold){
                for(i=0;i<3;i++)
                    out[pixel[p][0]][pixel[p][1]][i] = in[matches[m][0]][matches[m][1]][i];
                filled[pixel[p][0]][pixel[p][1]] = 1;
                progress = 1;
                nfilled++;
            }
            
            
            p++;
        }
        if(!progress)
            MaxErrThreshold *= 1.1;
    }
    fwrite(out,sizeof(unsigned char)*3,newRow*newCol,output);
    return 0;
}