from Crypto.Cipher import AES

key = b'1234567890123456'
iv = b'ABCDEF1234567890'   # IV cố định, đúng 16 bytes
plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_"   # 32 bytes = 2 block AES

def print_blocks(label, data):
    print(f"\n{label}")
    for i in range(0, len(data), 16):
        block = data[i:i+16]
        print(f"Block {i//16 + 1}: {block.hex()}")

# 1) AES-ECB
cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)

# 2) AES-CBC
cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
ct_cbc = cipher_cbc.encrypt(plaintext)

print("PLAINTEXT BLOCKS:")
print_blocks("Plaintext", plaintext)

print(f"\nECB: {ct_ecb.hex()}")
print_blocks("ECB blocks", ct_ecb)

print(f"\nCBC: {ct_cbc.hex()}")
print_blocks("CBC blocks", ct_cbc)

# So sánh nhanh
print("\nSO SÁNH:")
print("ECB block 1 == block 2 ?", ct_ecb[:16] == ct_ecb[16:32])
print("CBC block 1 == block 2 ?", ct_cbc[:16] == ct_cbc[16:32])

# 3) Thử thêm các mode khác trong lab
cipher_cfb = AES.new(key, AES.MODE_CFB, iv=iv, segment_size=128)
ct_cfb = cipher_cfb.encrypt(plaintext)

cipher_ofb = AES.new(key, AES.MODE_OFB, iv=iv)
ct_ofb = cipher_ofb.encrypt(plaintext)

cipher_ctr = AES.new(key, AES.MODE_CTR, nonce=b'12345678')
ct_ctr = cipher_ctr.encrypt(plaintext)

print(f"\nCFB: {ct_cfb.hex()}")
print_blocks("CFB blocks", ct_cfb)

print(f"\nOFB: {ct_ofb.hex()}")
print_blocks("OFB blocks", ct_ofb)

print(f"\nCTR: {ct_ctr.hex()}")
print_blocks("CTR blocks", ct_ctr)