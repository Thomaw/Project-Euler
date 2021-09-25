bool is_special_set(set<int> testme)
{
    set<int>::iterator it;
    set<int> sums;
    int minsum[testme.size()+1];
    int maxsum[testme.size()+1];
    int sum;

    for (int i=0; i<=testme.size(); i++)
    {
        minsum[i]=1000000;
        maxsum[i]=0;
    }

    int length_set = testme.size();
    long long number_subsets = pow(2,length_set);
    int subset_length;
    int bit;
    for (int cur_subset=1; cur_subset<number_subsets; cur_subset++)
    {
        subset_length=0;
        it = testme.begin();
        sum = 0;

        //binary representation of current subset
        for (int cur_element_in_set=length_set-1; cur_element_in_set>=0; cur_element_in_set--)
        {
            bit = ((cur_subset >> cur_element_in_set) & 1);
            subset_length+=bit;
            if (bit==1)
                sum += *(it);
            it++;
        }

        //this sum of a subset is already a sum of another subset
        if (sums.find(sum) != sums.end())
        {
            return false;
        }
        else
            sums.insert(sum);

        if (sum<minsum[subset_length])
            minsum[subset_length]=sum;
        if (sum>maxsum[subset_length])
            maxsum[subset_length]=sum;
    }

    //check if subset with length k>i exists, which has
    //smaller sum than subset with length i
    for (int i=1; i<=length_set; i++)
        for (int k=i+1; k<=length_set; k++)
            if (maxsum[i]>=minsum[k])
                return false;

    return true;
}

void Problem105()
{
    set<int> digits;
    set<int>::iterator iter;
    string line;
    stringstream stream;
    int i;
    size_t found;

    int sum=0;

    fstream file_op("sets.txt",ios::in);

    while(file_op >> line)
    {
        found = 1;
        digits.clear();
        while (found != string::npos)
        {
            found = line.find(",");
            stream.clear();
            stream << line.substr(0,found);
            stream >> i;
            line.erase(0,found+1);
            digits.insert(i);
        }

        if (is_special_set(digits))
        {
            for(iter = digits.begin(); iter!=digits.end(); ++iter )
            {
                sum += *iter;
            }
        }
    }

    cout << "sum: " << sum << endl;
}