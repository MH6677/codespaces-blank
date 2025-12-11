

QUẢN LÝ LINH KIỆN – Nguyễn Huỳnh Minh Hiếu

I. Giới thiệu hệ thống

Module “Quản lý linh kiện” chịu trách nhiệm lưu trữ, truy vấn, cập nhật và xóa thông tin linh kiện trong hệ thống. Đây là nền tảng để phục vụ các module cấp cao hơn như: nhập – xuất kho, xử lý đơn hàng, thống kê doanh thu.

Hệ thống sử dụng cấu trúc dữ liệu vector<Component> và lưu toàn bộ dữ liệu vào file văn bản linhkien.txt.

II. Cấu trúc dữ liệu Component
struct Component {
    string code;      // Mã linh kiện (duy nhất)
    string name;      // Tên linh kiện
    string type;      // Loại linh kiện
    double price;     // Giá
    int quantity;     // Số lượng tồn kho
};

III. Định dạng file linhkien.txt

Format chuẩn 5 trường, ngăn cách bằng ký tự “|”:

code|name|type|price|quantity


Ví dụ:

CPU01|Intel Core i3 10100F|CPU|2100000|15

RAM01|Kingston Fury 8GB 3200MHz|RAM|450000|40
...

IV. Các chức năng chính
1. Thêm linh kiện

Nhập mã

Kiểm tra trùng mã

Nhập các trường còn lại

Ghi vào file

2. Sửa linh kiện

Tìm theo mã

Hiển thị thông tin cũ

Nhập giá trị mới (enter để giữ nguyên)

Kiểm tra xung đột mã mới

3. Xóa linh kiện

Tìm theo mã

Yêu cầu xác nhận 'y'

Xóa khỏi vector + ghi file

4. Tìm kiếm nâng cao

Cho phép nhập đồng thời nhiều tiêu chí:

Tiêu chí	Kiểu
Tên	substring, không phân biệt hoa thường
Loại	substring
Giá	khoảng (from–to)

Tìm kiếm dùng AND logic: tất cả điều kiện phải đúng.
