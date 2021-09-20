int main()
{
    int nums[20][20];
    char c;
    int highest = 0;
    FILE* file = fopen("20x20.txt", "r");

    for(int i=0; i<20;i++)
        for(int j=0; j<20;j++)
        {
            fread(&c, 1 ,1, file);
            nums[j][i] = (c-48) * 10;
            fread(&c,1,1,file);
            nums[j][i] += (c-48);
            fread(&c,1,1,file);
        }
    
    for(int i=0; i<20; i++)
        for(int j=0;j<17;j++)
        {
            if(nums[i][j] * nums[i][j+1] * nums[i][j+2]  * nums[i][j+3] > highest) highest = nums[i][j] * nums[i][j+1] * nums[i][j+2]  * nums[i][j+3];
            if(nums[j][i] * nums[j+1][i] * nums[j+2][i]  * nums[j+3][i] > highest) highest = nums[j][i] * nums[j+1][i] * nums[j+2][i]  * nums[j+3][i];
        }
    for (int i=0; i<17;i++)
        for(int j=0; j<17; j++)
        {
            if(nums[i][j] * nums[i+1][j+1] * nums[i+2][j+2]  * nums[i+3][j+3] > highest) highest = nums[i][j] * nums[i+1][j+1] * nums[i+2][j+2]  * nums[i+3][j+3];
            if(nums[19-i][j] * nums[19-i-1][j+1] * nums[19-i-2][j+2]  * nums[19-i-3][j+3] > highest) highest = nums[19-i][j] * nums[19-i-1][j+1] * nums[19-i-2][j+2]  * nums[19-i-3][j+3];
        }     
    std::cout<<highest;
}
