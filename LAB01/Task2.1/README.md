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
              vì key chỉ có 25 trường hợp nên ta dùng vòng lặp từ 0-> 25  mỗi lần lặp ta gọi hàm giải mã lại 1 lần  để tìm ra kết quả phù hợp 