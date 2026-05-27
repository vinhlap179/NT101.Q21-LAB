

from Crypto.Cipher import DES

p1 = b'STAYHOME'
p2 = b'STAYHOMA'

def avalanche_test(key):
    cipher = DES.new(key, DES.MODE_ECB)
    c1 = cipher.encrypt(p1)
    c2 = cipher.encrypt(p2)
    bin_c1 = bin(int.from_bytes(c1, 'big'))[2:].zfill(64) # [2:].zfill(64) khong co cai nay in ra so 0 o truoc bi loi gg
    bin_c2 = bin(int.from_bytes(c2, 'big'))[2:].zfill(64) # dung de fill vao
    hamming_distance = 0
    for bit1, bit2 in zip(bin_c1, bin_c2):
        if bit1 != bit2:
            hamming_distance += 1            
    TongBits = 64 
    PhanTram = (hamming_distance / TongBits) * 100    
    print(f"Test voi key: {key}")
    print(f"Ma 1 (STAYHOME): {bin_c1}")
    print(f"Ma 2 (STAYHOMA): {bin_c2}")
    print(f"So bit khac nhau (Hamming Distance): {hamming_distance} / {TongBits}")
    print(f"Ty le thay doi: {PhanTram:.2f}%\n")

keys = [b'87654321', b'24520946', b'24521958']
for key in keys:
    avalanche_test(key)