bool decode(unsigned char key[3])
{
    int key_count   = 0;
    int punct_count = 0;

    for (int ii = 0; ii < sizeof(seq); ++ii)
    {
        unsigned char ch = seq[ii] ^ key[key_count];

        if (!std::isprint(ch)) return false;
        if ( std::ispunct(ch)) ++punct_count;

        // advance the key
        key_count = ++key_count % 3;
    }

    if (punct_count > 100) return false;

    return true;
}

int main()
{
    for (unsigned char k1 = 'a'; k1 <= 'z'; ++k1)
    {
        for (unsigned char k2 = 'a'; k2 <= 'z'; ++k2)
        {
            for (unsigned char k3 = 'a'; k3 <= 'z'; ++k3)
            {
                unsigned char key[3] = { k1, k2, k3 };

                if (decode(key))
                {
                    std::cout << k1 << k2 << k3 << std::endl;
                }
            }
        }
    }
}
