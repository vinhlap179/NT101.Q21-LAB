import secrets
# Kiểm tra số nguyên tố bằng Miller-Rabin
def kiem_tra_nguyen_to(n, so_lan_kiem_tra=10):
    if n < 2:
        return False
    cac_so_nguyen_to_nho = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    for p in cac_so_nguyen_to_nho:
        if n == p:
            return True
        if n % p == 0:
            return False
    r = 0
    d = n - 1
    while d % 2 == 0:
        r += 1
        d //= 2
    for _ in range(so_lan_kiem_tra):
        a = secrets.randbelow(n - 3) + 2
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue

        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True
# Sinh số nguyên tố có số bit cho trước
def sinh_so_nguyen_to(so_bit):
    while True:
        n = secrets.randbits(so_bit)
        n |= (1 << (so_bit - 1))   # đảm bảo đúng số bit
        n |= 1                     # đảm bảo là số lẻ
        if kiem_tra_nguyen_to(n):
            return n
# Tìm ước chung lớn nhất bằng Euclid
def uoc_chung_lon_nhat(a, b):
    while b != 0:
        a, b = b, a % b
    return a
# Tính lũy thừa modulo bằng phương pháp bình phương và nhân
def luy_thua_modulo(a, x, p):
    ket_qua = 1
    a = a % p
    while x > 0:
        if x % 2 == 1:
            ket_qua = (ket_qua * a) % p
        a = (a * a) % p
        x //= 2
    return ket_qua
# Tìm số nguyên tố liền trước một số n
def nguyen_to_lien_truoc(n):
    ung_vien = n - 1
    if ung_vien % 2 == 0:
        ung_vien -= 1
    while ung_vien > 2:
        if kiem_tra_nguyen_to(ung_vien):
            return ung_vien
        ung_vien -= 2
    return 2
# 1. Sinh số nguyên tố 8 bit, 16 bit, 64 bit
so_nguyen_to_8_bit = sinh_so_nguyen_to(8)
so_nguyen_to_16_bit = sinh_so_nguyen_to(16)
so_nguyen_to_64_bit = sinh_so_nguyen_to(64)
print("So nguyen to 8 bit :", so_nguyen_to_8_bit)
print("So nguyen to 16 bit:", so_nguyen_to_16_bit)
print("So nguyen to 64 bit:", so_nguyen_to_64_bit)
# 2. Tìm 10 số nguyên tố lớn nhất nhỏ hơn 2^89 - 1
mersenne_thu_10 = 2**89 - 1
danh_sach_nguyen_to = []
hien_tai = mersenne_thu_10
for _ in range(10):
    hien_tai = nguyen_to_lien_truoc(hien_tai)
    danh_sach_nguyen_to.append(hien_tai)
print("\n10 so nguyen to lon nhat nho hon 2^89 - 1:")
for i, p in enumerate(danh_sach_nguyen_to, 1):
    print(f"{i}. {p}")
# 3. Kiểm tra một số có phải số nguyên tố không
so_can_kiem_tra = 9999999967
print(f"\n{so_can_kiem_tra} la so nguyen to? {kiem_tra_nguyen_to(so_can_kiem_tra)}")
# 4. Tính UCLN của hai số lớn
a = 123456789123456789123456789
b = 987654321987654321987654321
print("\nUCLN =", uoc_chung_lon_nhat(a, b))
# 5. Tính lũy thừa modulo
print("7^40 mod 19 =", luy_thua_modulo(7, 40, 19))