#!/bin/bash

# Khai báo mảng
files=("booking" "service" "server")

# Lặp qua từng phần tử trong mảng
for name in "${files[@]}"; do
    echo "Đang xử lý: $name.ctl"

    # Giả sử dùng sqlldr chẳng hạn
    sqlldr userid=system/0@localhost:1521/ORACLE \
        control="$name.ctl" \
        data="$name.csv" \
        log="$name.log" \
        bad="$name.bad"
done
