
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import os
padded_data = pad(b'1234567890' * 100, 16) 
key = os.urandom(16)
iv = os.urandom(16)
def check(ten_che_do, mode):
    if ten_che_do == 'ECB':
        cipher_enc = AES.new(key, mode)          
    elif ten_che_do == 'CBC':
        cipher_enc = AES.new(key, mode, iv)     
    elif ten_che_do == 'CFB':
        cipher_enc = AES.new(key, mode, iv)      
    elif ten_che_do == 'OFB':
        cipher_enc = AES.new(key, mode, iv)      
    
    ban_ma = bytearray(cipher_enc.encrypt(padded_data))

    ban_ma[25] ^= 0x01     
    if ten_che_do == 'ECB':
        cipher_dec = AES.new(key, mode)
    elif ten_che_do == 'CBC':
        cipher_dec = AES.new(key, mode, iv)
    elif ten_che_do == 'CFB':
        cipher_dec = AES.new(key, mode, iv)
    elif ten_che_do == 'OFB':
        cipher_dec = AES.new(key, mode, iv)
        
    ban_loi = cipher_dec.decrypt(bytes(ban_ma))
    
    so_byte_loi = sum(1 for b1, b2 in zip(padded_data, ban_loi) if b1 != b2)
    print(f"{ten_che_do} {so_byte_loi} byte loi")

check('ECB', AES.MODE_ECB)
check('CBC', AES.MODE_CBC)
check('CFB', AES.MODE_CFB)
check('OFB', AES.MODE_OFB)