#define double long double
double Simpson(double l, double r, const function<double(double)>& f) {
    return (f(l)+f(r)+4*f((l+r)/2))*(r-l)/6;
}

// Returns the definite integral of f from l to r.
// The epsilon should be chosen adequately depending on the desired precision.
// To avoid errors due to unlucky events (vl+vr~v randomly) the initial
// interval [l, r] should be relatively small.
double Integrate(double l, double r, const function<double(double)>& f) {
    static const double eps = 1e-16;
    double m = (l+r)/(double)2.0;
    double vl = Simpson(l, m, f), vr = Simpson(m, r, f), v = Simpson(l, r, f);
    if (abs(vl+vr-v) < eps and abs(l-r) <= 1e-3) return v;
    return Integrate(l, m, f) + Integrate(m, r, f);
}

double Integrate2(function<double(double, double)> f) {
    function<double(double)> g = [&](double x) {
        function<double(double)> h = [&](double y) { return f(x, y); };
        return Integrate(0, 1, h);
    };
    return Integrate(0, 1, g);
}

double Integrate3(function<double(double, double, double)> f) {
    function<double(double)> g = [&](double x) {
        function<double(double, double)> h = [&](double y, double z) { return f(x, y, z); };
        return Integrate2(h);
    };
    return Integrate(0, 1, g);
}

int main() {
    function<double(double,double,double)> f = [](double x, double y, double z) { return abs(max(max(x, y), z)-min(min(x, y), z)); };
    function<double(double,double)> g = [](double x, double y) {
        return max(x*y, (1-x)*(1-y)); };
    function<double(double,double)> h = [](double x, double y) {
        if (x > y) swap(x, y);
        if (x >= (1-x)*(1-y)) return x;
        return min(y, (1-x)*(1-y));
    };
    cout.precision(10);
    double F = 0.5; // Integrate3(f);
    double G = 5.0/12.0;// Integrate2(g);
    double H = Integrate2(h);
    cout << G << " " << H << endl;
    double res = F*F/3.0*(G + 2*H);
    cout << fixed << res << endl;
}