#include < iostream >
#include < gmpxx.h >

using namespace std;

class TN_LR { //truncate from left to right
public:
        static string trunc_num(const string &n) {
                return string(n, 1, n.length() - 1);
        };
};

class TN_RL { //truncate from right to left
public:
        static string trunc_num(const string &n) {
                return string(n, 0, n.length() - 1);
        };
};

template < class F >
static bool check_prime(const string &num) { //recursion:
//truncate until num is empty
        if(num == "")
                return true;
        if(mpz_probab_prime_p(mpz_class(num, 10).get_mpz_t(), 10) == 0)
                return false;
        return check_prime < F > (F::trunc_num(num));
}

int main() {
        mpz_class sum = 0;
        for(mpz_class i = 11; cmp(i, 1000000) < 0; mpz_nextprime(i.get_mpz_t(), i.get_mpz_t()))
                if(check_prime < TN_LR > (i.get_str()) && check_prime < TN_RL > (i.get_str()))
                        sum += i;
        cout << sum << endl;
        return 0;
}
