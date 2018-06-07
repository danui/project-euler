
def gcd(a,b):
    if a == 0:
        return b
    return gcd(b%a, a)

def rsa(n, k, data):
    return (data**k) % n

p = 743
q = 967
n = p * q
print "n:", n
phi = (p-1) * (q-1)
print "phi:", phi
e = 5+3*6
while (gcd(e, phi) != 1):
    e += 6
    if e > phi:
        print "cannot find e"
        exit(1)
print "e:", e
d = 0
while ((d*e) % phi) != 1:
    d += 1
print "d:", d
print "Public Key, n:", n, "e:", e
print "Private Key, n:", n, "d:", d

plain = 100
print "Plain:", plain
cipher = rsa(n, e, plain)
print "Cipher:", cipher
decrypted = rsa(n, d, cipher)
print "Decrypted:", decrypted
