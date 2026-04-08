import math
import base64

def tao_khoa(p, q, e):
    n = p * q
    phi_n = (p - 1) * (q - 1)
    if math.gcd(e, phi_n) != 1:
        raise ValueError("e khong nguyen to cung nhau voi phi(n)")
    d = pow(e, -1, phi_n)
    khoa_cong_khai = (e, n)
    khoa_rieng = (d, n)
    return khoa_cong_khai, khoa_rieng, phi_n

def ma_hoa_so_nguyen(ban_ro, khoa):
    so_mu, n = khoa
    if not (0 <= ban_ro < n):
        raise ValueError("Ban ro phai thoa 0 <= ban_ro < n")
    return pow(ban_ro, so_mu, n)

def giai_ma_so_nguyen(ban_ma, khoa):
    so_mu, n = khoa
    return pow(ban_ma, so_mu, n)

# Ma hoa chuoi theo tung block va xuat ra Base64
def ma_hoa_chuoi_sang_base64(chuoi, khoa):
    so_mu, n = khoa
    du_lieu = chuoi.encode("utf-8")
    kich_thuoc_block_ma = (n.bit_length() + 7) // 8
    kich_thuoc_block_ro = max(1, (n.bit_length() - 1) // 8)
    ket_qua = bytearray()
    for i in range(0, len(du_lieu), kich_thuoc_block_ro):
        block = du_lieu[i:i + kich_thuoc_block_ro]
        gia_tri_block = int.from_bytes(block, "big")
        if gia_tri_block >= n:
            raise ValueError("Block ban ro >= n, can giam kich thuoc block")
        ban_ma = pow(gia_tri_block, so_mu, n)
        ket_qua.extend(ban_ma.to_bytes(kich_thuoc_block_ma, "big"))
    return base64.b64encode(bytes(ket_qua)).decode()

def giai_ma_base64_sang_chuoi(base64_ban_ma, khoa, kich_thuoc_block_ro=None):
    so_mu, n = khoa
    kich_thuoc_block_ma = (n.bit_length() + 7) // 8
    if kich_thuoc_block_ro is None:
        kich_thuoc_block_ro = max(1, (n.bit_length() - 1) // 8)
    du_lieu_ma = base64.b64decode(base64_ban_ma)
    danh_sach_block = [
        du_lieu_ma[i:i + kich_thuoc_block_ma]
        for i in range(0, len(du_lieu_ma), kich_thuoc_block_ma)
    ]
    ket_qua = bytearray()
    for block in danh_sach_block:
        gia_tri_ma = int.from_bytes(block, "big")
        gia_tri_ro = pow(gia_tri_ma, so_mu, n)
        block_ro = gia_tri_ro.to_bytes((gia_tri_ro.bit_length() + 7) // 8 or 1, "big")
        ket_qua.extend(block_ro)
    return ket_qua.decode("utf-8", errors="replace")

# CAU 1 + CAU 2
p1, q1, e1 = 11, 17, 7
khoa_cong_khai_1, khoa_rieng_1, phi_n_1 = tao_khoa(p1, q1, e1)
print("Khoa cong khai 1 =", khoa_cong_khai_1)
print("Khoa rieng 1     =", khoa_rieng_1)
print("phi(n) 1         =", phi_n_1)
ban_ro = 5

# Truong hop bao mat (Confidentiality)
ban_ma_bao_mat = ma_hoa_so_nguyen(ban_ro, khoa_cong_khai_1)
ban_ro_sau_giai_ma_bao_mat = giai_ma_so_nguyen(ban_ma_bao_mat, khoa_rieng_1)
print("Bao mat:")
print("  Ban ma =", ban_ma_bao_mat)
print("  Giai ma =", ban_ro_sau_giai_ma_bao_mat)

# Truong hop xac thuc (Authentication)
ban_ma_xac_thuc = ma_hoa_so_nguyen(ban_ro, khoa_rieng_1)
ban_ro_sau_giai_ma_xac_thuc = giai_ma_so_nguyen(ban_ma_xac_thuc, khoa_cong_khai_1)
print("Xac thuc:")
print("  Ban ma =", ban_ma_xac_thuc)
print("  Giai ma =", ban_ro_sau_giai_ma_xac_thuc)

# CAU 1 - BO 2
p2 = 20079993872842322116151219
q2 = 676717145751736242170789
e2 = 17
khoa_cong_khai_2, khoa_rieng_2, phi_n_2 = tao_khoa(p2, q2, e2)
print("Khoa cong khai 2 =", khoa_cong_khai_2)
print("Khoa rieng 2     =", khoa_rieng_2)

# CAU 1 - BO 3
p3 = int("F7E75FDC469067FFDC4E847C51F452DF", 16)
q3 = int("E85CED54AF57E53E092113E62F436F4F", 16)
e3 = int("0D88C3", 16)
khoa_cong_khai_3, khoa_rieng_3, phi_n_3 = tao_khoa(p3, q3, e3)
print("Khoa cong khai 3 =", (hex(khoa_cong_khai_3[0]), hex(khoa_cong_khai_3[1])))
print("Khoa rieng 3     =", (hex(khoa_rieng_3[0]), hex(khoa_rieng_3[1])))

# CAU 3
thong_diep = "The University of Information Technology."
ban_ma_base64_bo_2 = ma_hoa_chuoi_sang_base64(thong_diep, khoa_cong_khai_2)
print("Ban ma Base64 voi bo 2 =", ban_ma_base64_bo_2)
thong_diep_giai_ma = giai_ma_base64_sang_chuoi(ban_ma_base64_bo_2, khoa_rieng_2)
print("Thong diep sau giai ma =", thong_diep_giai_ma)