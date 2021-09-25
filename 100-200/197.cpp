void Problem197() {
    double ce,cp;
    double u,ualt;

    ce = 30.403243784;
    cp = 0.0000000001;
    u = -1;

    cout.precision(9);

    for (int i=0; i<pow(10,12); i++)
    {
        u = floor(pow(2,ce-u*u))*pow(10,-9);
        cout << i << " " << fixed << u+ualt << endl;
        ualt=u;
    }
}
