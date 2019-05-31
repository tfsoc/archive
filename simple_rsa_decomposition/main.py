#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random
from fractions import gcd

e = 331
d = 12071
n = 66013

# KROK 1
# Liczbe ed − 1 przedstawiamy w postaci 2^s*t, gdzie t jest liczba nieparzysta
t = (e * d - 1) / 2
s = 1
while t % 2 == 0:
    s = s + 1
    t = t / 2

print "ed - 1 = 2^s * t = 2^%d * %d" % (s, t)


# KROK 2 
# Wybieramy losowo liczbe a z przedzialu 1 < a < n
while(True):
    a = random.randint(1, n)
    a = 2
# KROK 3
# Obliczamy b = a^t mod n
    b = pow(a, t, n)

# KROK 4
# Jesli b = 1, to wracamy do 2.
    if (b == 1):
        continue
    
    print "a := ", a
    print "b := a^2 mod n = ", b
    print "b != 1"
# KROK 5
# Obliczamy rekurencyjnie ciag c_0 = b, c_(i+1) = (c_i)^2 az do uzyskania 1 dla c_(i+1)
    c = b
    for i in range(s):
        tmp = pow(c, 2, n)
        if ( tmp == 1):
            break
        else:
            c = tmp
# KROK 6
# Jesli c = n-1, to wracamy do 2
    if (c == n - 1):
        continue
# KROK 7
# Zwracamy d = nwd(c-1,n) jako dzielnik pierwszy n i STOP
    d = gcd(c - 1, n)
    print "p = %d, q = %d\n" % (d, n / d)
    break
