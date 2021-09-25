from gmpy2 import mpfr, get_context, const_pi, is_square
get_context().precision = 128 
pi = const_pi()

def I(D, N, search_window = 5):
    best_approximation_error = 1
    r = D**mpfr(0.5)
    v = (1, 0)
    a = int(D**0.5)
    u = (a, -1)
    v_point = (1, 1)
    u_point = (u[0]-r, u[0])
    
    while u[0] < N:
        # Euclidean reduction iteration
        k = int(-v_point[0]/u_point[0])
        a = k*u[0] + v[0]
        b = k*u[1] + v[1]
        v, v_point = u, u_point
        u = (a,b)
        u_point = (a+b*r, a)
        
        # Transform the point to the lattice coordinates by matrix inversion
        d = u_point[0]*v_point[1] - u_point[1]*v_point[0]
        x0 = int(pi*v_point[1]/d)
        y0 = int(-pi*u_point[1]/d)
        
        # Locat search for best solution
        for dx in xrange(-search_window, +search_window):
            for dy in xrange(-search_window, +search_window):
                x = x0 + dx
                y = y0 + dy
                a2 = u[0]*x + v[0]*y
                b2 = u[1]*x + v[1]*y
                approximation_error = abs(a2+b2*r-pi)
                if abs(a2) <= N and abs(b2) <= N and approximation_error <= best_approximation_error:
                    best_approximation_error = approximation_error
                    res = a2
    return res

def p591(N = 10**13):
    res = 0
    for d in xrange(100):
        if not is_square(d):
            res += abs(I(d, N))
    return res