#include <bits/stdc++.h>
using namespace std;

const string DATA_FILE = "linhkien.txt";

struct Component {
    string code;
    string name;
    string type;
    double price = 0.0;
    int quantity = 0;
};

static inline string trim(const string &s) {
    size_t b = 0;
    while (b < s.size() && isspace((unsigned char)s[b])) ++b;
    if (b == s.size()) return "";
    size_t e = s.size() - 1;
    while (e > b && isspace((unsigned char)s[e])) --e;
    return s.substr(b, e - b + 1);
}

static inline string toLower(const string &s) {
    string r = s;
    transform(r.begin(), r.end(), r.begin(), [](unsigned char c){ return (char)tolower(c); });
    return r;
}

vector<string> splitPipe(const string &line) {
    vector<string> parts;
    string cur;
    for (char ch : line) {
        if (ch == '|') {
            parts.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(ch);
        }
    }
    parts.push_back(cur);
    return parts;
}

bool loadComponents(vector<Component> &list) {
    list.clear();
    ifstream ifs(DATA_FILE);
    if (!ifs.is_open()) {
        // No file yet is fine
        return true;
    }
    string line;
    while (getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;
        auto parts = splitPipe(line);
        if (parts.size() < 5) continue; // invalid line -> skip
        Component c;
        c.code = trim(parts[0]);
        c.name = trim(parts[1]);
        c.type = trim(parts[2]);
        try {
            c.price = stod(trim(parts[3]));
        } catch (...) { c.price = 0.0; }
        try {
            c.quantity = stoi(trim(parts[4]));
        } catch (...) { c.quantity = 0; }
        list.push_back(c);
    }
    return true;
}

bool saveComponents(const vector<Component> &list) {
    ofstream ofs(DATA_FILE, ios::trunc);
    if (!ofs.is_open()) {
        cerr << "Không thể mở file để ghi: " << DATA_FILE << "\n";
        return false;
    }
    for (const auto &c : list) {
        ofs << c.code << "|" << c.name << "|" << c.type << "|";
        ofs << fixed << setprecision(2) << c.price << "|" << c.quantity << "\n";
    }
    return true;
}

int findByCode(const vector<Component> &list, const string &code) {
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i].code == code) return (int)i;
    }
    return -1;
}

string inputLine(const string &prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return trim(s);
}

void printComponentHeader() {
    cout << left << setw(12) << "Mã"
         << left << setw(30) << "Tên"
         << left << setw(18) << "Loại"
         << right << setw(10) << "Giá"
         << right << setw(10) << "Số lượng" << "\n";
    cout << string(80, '-') << "\n";
}

void printComponent(const Component &c) {
    cout << left << setw(12) << c.code
         << left << setw(30) << c.name
         << left << setw(18) << c.type
         << right << setw(10) << fixed << setprecision(2) << c.price
         << right << setw(10) << c.quantity << "\n";
}

void listAll(const vector<Component> &list) {
    if (list.empty()) {
        cout << "Danh sách rỗng.\n";
        return;
    }
    printComponentHeader();
    for (const auto &c : list) printComponent(c);
}

void addComponent(vector<Component> &list) {
    cout << "=== Thêm linh kiện ===\n";
    string code = inputLine("Mã linh kiện: ");
    if (code.empty()) { cout << "Mã rỗng -> hủy.\n"; return; }
    if (findByCode(list, code) != -1) {
        cout << "Mã '" << code << "' đã tồn tại. Không thể thêm.\n";
        return;
    }
    Component c;
    c.code = code;
    c.name = inputLine("Tên linh kiện: ");
    c.type = inputLine("Loại: ");
    string s;
    s = inputLine("Giá: ");
    try { c.price = stod(s); } catch (...) { c.price = 0.0; }
    s = inputLine("Số lượng: ");
    try { c.quantity = stoi(s); } catch (...) { c.quantity = 0; }

    list.push_back(c);
    if (saveComponents(list)) cout << "Đã thêm linh kiện.\n";
}

void editComponent(vector<Component> &list) {
    cout << "=== Sửa linh kiện ===\n";
    string code = inputLine("Nhập mã linh kiện cần sửa: ");
    if (code.empty()) { cout << "Mã rỗng -> hủy.\n"; return; }
    int idx = findByCode(list, code);
    if (idx == -1) { cout << "Không tìm thấy mã '" << code << "'.\n"; return; }
    Component &c = list[idx];
    cout << "Thông tin hiện tại:\n";
    printComponentHeader();
    printComponent(c);
    cout << "Nhập giá trị mới (enter để giữ nguyên):\n";
    string s;

    s = inputLine("Mã mới: ");
    if (!s.empty() && s != c.code) {
        if (findByCode(list, s) != -1) {
            cout << "Mã '" << s << "' đã tồn tại. Không đổi mã.\n";
        } else {
            c.code = s;
        }
    }
    s = inputLine("Tên mới: ");
    if (!s.empty()) c.name = s;
    s = inputLine("Loại mới: ");
    if (!s.empty()) c.type = s;
    s = inputLine("Giá mới: ");
    if (!s.empty()) {
        try { c.price = stod(s); } catch (...) { cout << "Giá không hợp lệ, giữ nguyên.\n"; }
    }
    s = inputLine("Số lượng mới: ");
    if (!s.empty()) {
        try { c.quantity = stoi(s); } catch (...) { cout << "Số lượng không hợp lệ, giữ nguyên.\n"; }
    }

    if (saveComponents(list)) cout << "Đã cập nhật linh kiện.\n";
}

void deleteComponent(vector<Component> &list) {
    cout << "=== Xóa linh kiện ===\n";
    string code = inputLine("Nhập mã linh kiện cần xóa: ");
    if (code.empty()) { cout << "Mã rỗng -> hủy.\n"; return; }
    int idx = findByCode(list, code);
    if (idx == -1) { cout << "Không tìm thấy mã '" << code << "'.\n"; return; }
    cout << "Xác nhận xóa linh kiện:\n";
    printComponentHeader();
    printComponent(list[idx]);
    string conf = inputLine("Gõ 'y' để xác nhận: ");
    if (toLower(conf) == "y") {
        list.erase(list.begin() + idx);
        if (saveComponents(list)) cout << "Đã xóa.\n";
    } else {
        cout << "Hủy xóa.\n";
    }
}

void searchAdvanced(const vector<Component> &list) {
    cout << "=== Tìm kiếm nâng cao ===\n";
    cout << "Bạn có thể nhập nhiều điều kiện cùng lúc. Để bỏ qua điều kiện, để trống.\n";
    string name = inputLine("Tên (chuỗi con, không phân biệt hoa thường): ");
    string type = inputLine("Loại (chuỗi con hoặc chính xác): ");
    string priceFromS = inputLine("Giá từ (số) : ");
    string priceToS   = inputLine("Giá đến (số) : ");

    bool byName = !trim(name).empty();
    bool byType = !trim(type).empty();
    bool byPrice = !(trim(priceFromS).empty() && trim(priceToS).empty());

    double priceFrom = 0.0, priceTo = 0.0;
    if (!trim(priceFromS).empty()) {
        try { priceFrom = stod(priceFromS); } catch (...) { priceFrom = -1e300; }
    } else priceFrom = -1e300;
    if (!trim(priceToS).empty()) {
        try { priceTo = stod(priceToS); } catch (...) { priceTo = 1e300; }
    } else priceTo = 1e300;

    string nameL = toLower(name);
    string typeL = toLower(type);

    vector<Component> results;
    for (const auto &c : list) {
        if (byName) {
            if (toLower(c.name).find(nameL) == string::npos) continue;
        }
        if (byType) {
            if (toLower(c.type).find(typeL) == string::npos) continue;
        }
        if (byPrice) {
            if (c.price < priceFrom || c.price > priceTo) continue;
        }
        results.push_back(c);
    }

    if (results.empty()) {
        cout << "Không tìm thấy kết quả phù hợp.\n";
        return;
    }
    cout << "Kết quả tìm kiếm: " << results.size() << " mục\n";
    printComponentHeader();
    for (const auto &c : results) printComponent(c);
}

void showMenu() {
    cout << "\n=== QUẢN LÝ LINH KIỆN ===\n";
    cout << "1. Danh sách tất cả linh kiện\n";
    cout << "2. Thêm linh kiện\n";
    cout << "3. Sửa linh kiện\n";
    cout << "4. Xóa linh kiện\n";
    cout << "5. Tìm kiếm nâng cao (theo loại, tên, giá)\n";
    cout << "0. Thoát\n";
}

    int main() {

    vector<Component> list;
    loadComponents(list);



    while (true) {
        showMenu();
        string choice = inputLine("Chọn: ");
        if (choice == "0") {
            cout << "Thoát chương trình. Lưu dữ liệu...\n";
            saveComponents(list);
            break;
        } else if (choice == "1") {
            listAll(list);
        } else if (choice == "2") {
            addComponent(list);
        } else if (choice == "3") {
            editComponent(list);
        } else if (choice == "4") {
            deleteComponent(list);
        } else if (choice == "5") {
            searchAdvanced(list);
        } else {
            cout << "Lựa chọn không hợp lệ.\n";
        }
    }

    return 0;
}