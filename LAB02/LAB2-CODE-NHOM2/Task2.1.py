def F(right, subkey):
    return (right ^ subkey) & 0x0F
def feistel_round(L_in, R_in, subkey):
    # LE_i = RE_{i-1}
    L_out = R_in
    # RE_i = LE_{i-1} XOR F(RE_{i-1}, K_i)
    R_out = L_in ^ F(R_in, subkey)
    return L_out & 0x0F, R_out & 0x0F
def track_avalanche(msg, key):
    # Tách 8 bit thành 2 nửa 4 bit
    L, R = (msg >> 4) & 0x0F, msg & 0x0F
    # Sinh 4 subkey như scaffold
    subkeys = [
        key & 0x0F,
        (key >> 4) & 0x0F,
        (key + 1) & 0x0F,
        (key + 2) & 0x0F
    ]
    print(f"Khởi tạo: L={format(L, '04b')}, R={format(R, '04b')}")
    for i in range(4):
        L, R = feistel_round(L, R, subkeys[i])
        print(f"Vòng {i+1}: L={format(L, '04b')}, R={format(R, '04b')}")
    return (L << 4) | R
# Chạy thử với 2 bản rõ
print("--- Mã hóa M1 ---")
cipher1 = track_avalanche(0xAB, 0x12)
print(f"Bản mã M1: 0x{cipher1:02X}")

print("\n--- Mã hóa M2 ---")
cipher2 = track_avalanche(0xAC, 0x12)
print(f"Bản mã M2: 0x{cipher2:02X}")