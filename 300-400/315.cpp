char bin2char(const char* num){
    char ret = 0;
    for(int i = 0 ; i <= 7 ; ++i){
        ret *= 2;
        if(num[i] == '1')
            ++ret;
    }
    return ret;
}

int count(char num){
    int ret = 0;
    while(num > 0){
        if(num & 1)
            ++ret;
        num /= 2;
    }
    return ret;
}

int digit_root(int num){
    int ret = 0;
    while(num > 0){
        ret += (num % 10);
        num /= 10;
    }
    return ret;
}

int main(){
    char numbers[] = {
        bin2char("01011111"),
        bin2char("00000101"),
        bin2char("01110110"),
        bin2char("01110101"),
        bin2char("00101101"),
        bin2char("01111001"),
        bin2char("01111011"),
        bin2char("01001101"),
        bin2char("01111111"),
        bin2char("01111101")
    };
    int diff = 0;
    int i;
    int root, next, tmp, tmp_r, tmp_i, tmp_c, transitions_sam, transitions_max;
    sieve* primes = new sieve(20000000);
    primelist list = (*primes).get_list();
    while(*list < 10000000)
        ++list;

    while(*list){
        i = *list;
        transitions_max = 0;
        transitions_sam = 0;
        tmp = i;
        while(tmp > 0){
            tmp_c = count(numbers[tmp % 10]);
            transitions_sam += 2 * tmp_c;
            transitions_max += tmp_c;
            tmp /= 10;
        }
        while(true){
            root = digit_root(i);
            if(root == i)
                break;
            next = root;
            while(root > 0){
                tmp_r = numbers[root % 10];
                tmp_i = numbers[i % 10];
                transitions_sam += 2 * count(tmp_r);
                transitions_max += count(tmp_i ^ tmp_r);
                root /= 10;
                i /= 10;
            }
            while(i > 0){
                transitions_max += count(numbers[i % 10]);
                i /= 10;
            }
            i = next;
        }
        transitions_max += count(numbers[next]);
        diff += (transitions_sam - transitions_max);
        ++list;
    }
    std::cout<<"Difference: "<<diff<<std::endl;
}