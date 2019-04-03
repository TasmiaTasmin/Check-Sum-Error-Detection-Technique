// checkSum error detection technique

#include<bits/stdc++.h>
#include<iostream>

using namespace std;

#define SIZE 50

int numberOfWord, lengthInBit;
int wordArray[SIZE][SIZE], wA[SIZE][SIZE], sum[SIZE], rSum[SIZE];
int checkSum[SIZE];
int sComplement[SIZE], rComplement[SIZE];

void takeInput(int Array[][SIZE])
{
    int i, j;
    for(i=0; i<numberOfWord; i++)
    {
        for(j=0; j<lengthInBit; j++)
        {
            scanf("%d", &Array[i][j]);
        }
    }
    printf("\n");
}

void findSumForSender(int Array[][SIZE], int *sum)
{
    int carry, i, j;

    for(j=0; j<lengthInBit; j++)
    {
        sum[j] = Array[0][j];
    }

    carry = 0;
    for(i=1; i<numberOfWord; i++)
    {
        for(j=lengthInBit-1; j>=0; j--)
        {
            if(sum[j] == 0 && Array[i][j] == 0 && carry == 0)
            {
                sum[j]=0;
                carry=0;
            }
            else if(sum[j]==0 && Array[i][j]==0 && carry==1)
            {
                sum[j]=1;
                carry=0;
            }
            else if(sum[j]==0 && Array[i][j]==1 && carry==0)
            {
                sum[j]=1;
                carry=0;
            }
            else if(sum[j]==0 && Array[i][j]==1 && carry==1)
            {
                sum[j]=0;
                carry=1;
            }
            else if(sum[j]==1 && Array[i][j]==0 && carry==0)
            {
                sum[j]=1;
                carry=0;
            }
            else if(sum[j]==1 && Array[i][j]==0 && carry==1)
            {
                sum[j]=0;
                carry=1;
            }
            else if(sum[j]==1 && Array[i][j]==1 && carry==0)
            {
                sum[j]=0;
                carry=1;
            }
            else if(sum[j]==1 && Array[i][j]==1 && carry==1)
            {
                sum[j]=1;
                carry=1;
            }
            else
                break;
        }
        if(carry == 1)
        {
            for(j=lengthInBit-1; j>=0; j--)
            {
                if(sum[j] == 0 && carry == 1)
                {
                    sum[j]=1;
                    carry=0;
                }
                else if(sum[j]==1 && carry==1)
                {
                    sum[j]=0;
                    carry=1;
                }
            }
        }
    }
}

void complementOfSum(int *sum, int *Complement)
{
    int j;
    for(j=lengthInBit-1; j>=0; j--)
    {
        if(sum[j] == 0)
        {
            Complement[j]=1;
        }
        else
        {
            Complement[j]=0;
        }
    }
}

void findSumForReceiver(int *rSum, int *checkSum)
{
    int carry, i, j;
    carry = 0;
    for(j=lengthInBit-1; j>=0; j--)
    {
        if(rSum[j] == 0 && checkSum[j] == 0 && carry == 0)
        {
            rSum[j]=0;
            carry=0;
        }
        else if(rSum[j]==0 && checkSum[j]==0 && carry==1)
        {
            rSum[j]=1;
            carry=0;
        }
        else if(rSum[j]==0 && checkSum[j]==1 && carry==0)
        {
            rSum[j]=1;
            carry=0;
        }
        else if(rSum[j]==0 && checkSum[j]==1 && carry==1)
        {
            rSum[j]=0;
            carry=1;
        }
        else if(rSum[j]==1 && checkSum[j]==0 && carry==0)
        {
            rSum[j]=1;
            carry=0;
        }
        else if(rSum[j]==1 && checkSum[j]==0 && carry==1)
        {
            rSum[j]=0;
            carry=1;
        }
        else if(sum[j]==1 && checkSum[j]==1 && carry==0)
        {
            rSum[j]=0;
            carry=1;
        }
        else if(rSum[j]==1 && checkSum[j]==1 && carry==1)
        {
            rSum[j]=1;
            carry=1;
        }
        else
            break;
    }
    if(carry == 1)
    {
        for(j=lengthInBit-1; j>=0; j--)
        {
            if(rSum[j] == 0 && carry == 1)
            {
                rSum[j]=1;
                carry=0;
            }
            else if(rSum[j]==1 && carry==1)
            {
                rSum[j]=0;
                carry=1;
            }
        }
    }
}

void checkError(int *rComplement)
{
    int a, j;

    a=0;
    for(j=0; j<lengthInBit; j++)
    {
        a += rComplement[j];
    }

    if(a ==0)
    {
        printf("Transmitted data is accepted as the result is 0.\n\n");
    }
    else
    {
        printf("Transmitted data is discarded as the result is not 0.\n\n");
    }
}

int main()
{
    int  i, j, k, l, m, n, cnt;

    printf("Enter the number of words:");               //How many chunks of bit
    scanf("%d", &numberOfWord);
    printf("\n");

    printf("Enter the length of word in bit:");          //Length of every chunks
    scanf("%d", &lengthInBit);
    printf("\n");

    printf("Enter the bit words to be sent: \n\n");         //Input data of sender's side

    takeInput(wordArray);
    findSumForSender(wordArray, sum);
    complementOfSum(sum, sComplement);

    printf("Computed checksum for given data: ");

    for(j=0; j<lengthInBit; j++)
    {
        printf("%d ", sComplement[j]);
    }
    printf("\n");
    printf("\n");
    printf("Enter the bit words to be received: \n\n");       //Input data of receiver's side

    takeInput(wA);

    for(j=0; j<lengthInBit; j++)
    {
        scanf("%d", &checkSum[j]);
    }

    printf("\n");

    findSumForSender(wA, rSum);
    findSumForReceiver(rSum, checkSum);
    complementOfSum(rSum, rComplement);
    checkError(rComplement);

    return 0;
}

