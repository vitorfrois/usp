vt = 0.12
vc = 9.0

def f(d, dc):
    dc += d
    dt = (d*vt)/vc
    d -= dt
    print('Enquanto o coelho foi na linha de chegada, a tart andou ', str(dt), 'm')
    t = d/(vt+vc)
    dt = t*vt
    d -= dt
    print('Para voltar até a tartaruga, o coelho correu', str(d), 'm')
    dc += d
    return d, dc

a = 80
b = 0
while a > 0.1:
    a, b = f(a, b)
    print('O coelho ja correu ', str(b), 'm')

print('O coelho correu ', str(b), 'm no total')
