# NT101.Q21-LAB
Lab môn an toàn mạng máy tính 
lab01
 TASK 2.1
  Ý tưởng thực hiện task 2.1 
     *Ý tưởng thuật toán 
         - mã hóa ta có công thưc : C = (p + k) mod 26
         - giải mã ta có công thức : p = (C − k) mod 26
         -  brute-force có 25 trường hợp từ số 0 -> số 25 
     * Ý tưởng code 
         - bước 1 : nhập dữ liệu 
             + lựa chọn chức năng 
             + nhập chuỗi văn bản 
             + nhập key 
         - bước 2 : duyệt từng kí tự trong chuỗi 
         - bước 3 : kiểm tra loại kí tự chữ hoa chữ thường 
             + nếu là chữ hoa isupper() ta chuyển về khoảng 0- 25 bằng cách trừ 'A'
             + nếu là chữ thường islower() ta chuyển về khoảng 0-25 bằng cách trừ 'a' 
             + kí tự khác thì ta dữ nguyên
         - Bước 4 : xây dựng các hàm 
             + hàm mã hóa : 
                  1 : duyệt từng kí tự trong  chuỗi  
                  2 : nếu là chữ cái  áp dụng công thức C = (p + k) mod 26
                  3 : chuyển lại về kì tứ ASCII và thêm vào res 
             + hàm giải mã 
              1 : duyệt từng kí tự trong  chuỗi  
              2 : nếu là chữ cái  áp dụng công thức p = (C - key + 26) mod 26( tránh trường hợp số âm )
              3 : chuyển lại về kì tứ ASCII và thêm vào res 
             + hàm Brute-force
              - vì key chỉ có 25 trường hợp nên ta dùng vòng lặp từ 0-> 25  mỗi lần lặp ta gọi hàm giải mã lại 1 lần  để tìm ra kết quả phù hợp 
 TASK 2.4
    Ý tưởng thực hiện task 2.4
     * ý tưởng  thuật toán 
         - Playfair Cipher là phương pháp mã hóa   bằng ma trận 5x5 có thể là 6x6 nếu có số
         - các bước thực hiện 
          1: chuẩn hóa khóa loại bỏ kí tự trùng và gộp j/ i 
          2: tạo ma trận 5x5 từ khóa  
          3: chuẩn hóa plaintext " 
           + chuyển thành chữ hoa 
           + thay j-> i 
           + chia thành cặp kí tự 
           + chèn X nếu hai ký tự giống nhau 
          4: áp dụng quy tắc Plaifair để mã hóa 
          quy tắc mã hóa  :
           + cùng hàng -> dịch sang phải 
           + cùng cột  -> dịch xuống 
           + khác hàng cột -> tạo hình chữ nhật 
          quy tắc giải mã 
           + cùng hàng -> dịch sang trái 
           + cùng cột -> dịch lên 
           + khác hàng cột -> tạo hình chữ nhật 
     * ý tưởng code 
        1 : nhập khóa và tạo ma trận 5x5
           - Chuyển khóa thành chữ in hoa
            -Loại bỏ khoảng trắng
            -Thay J → I
            -Loại bỏ ký tự trùng lặp
            -Thêm các chữ cái còn lại của bảng chữ cái (trừ J)
            -Sau đó điền vào ma trận 5×5 theo thứ tự từ trái sang phải, từ trên xuống dưới.
        2: Chuẩn hóa plaintext
            - chuyển tất cả thành chữ hoa thay J → - chia thành cặp ký tự
            - nếu hai ký tự trong cùng cặp giống nhau → chèn X
            - nếu số ký tự lẻ → thêm X ở cuối
        3: tìm vị trí ký tự trong ma trận 
         - với mỗi  kí tự trong ma trận ta tìm hàng và cột
        4: ta áp dụng quy tắc mã hóa 
            + trường hợp 1 : cùng hàng 
            + trường hợp 2 : cùng cột  
            + trường hợp 3 : khác hàng khác cột 
        5: áp dụng quy tắc giải mã 
            + trường hợp 1 : cùng hàng 
            + trường hợp 2 : cùng cột  
            + trường hợp 3 : khác hàng khác cột
         

