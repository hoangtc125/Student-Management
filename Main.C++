// Khai báo tất cả các thư viện
#include<bits/stdc++.h>
using namespace std;



// Cấu trúc dữ liệu ngày tháng năm sinh
typedef struct {
    int Ng,
        Th,
        Na;
} ngaysinh;

// Cấu trúc dữ liệu 1 sinh viên
typedef struct dssv{
    char shsv[9];
    char* Hoten;
    char* ten;
    ngaysinh ns;
    char gioitinh[5];
    float diem;
    dssv* nextsv;
} dssv;

// Cấu trúc dữ liệu 1 lớp học
typedef struct dslop{
    char* tenlop;
    dslop* nextlop;
    dssv* firstsvOflop;
} dslop;



/*
Hàm đọc dữ liệu từ file
*/
void read_file_input(char*);

/*
Hàm ghi dữ liệu ra file
*/
void write_file_output(char*);

/*
Hàm chèn sinh viên vào lớp tương ứng (đối với dữ liệu từ file)
*/
void insert_from_file(char*, char*, char*, char*, char*, char*, char*, char*);

/*
Hàm tìm kiếm lớp, trả về 1 lớp có tên lớp được truyền vào đối số
Nếu không tìm thấy sẽ tạo mới 1 lớp và trả về lớp đó (đối với dữ liệu từ file)
*/
dslop* search_lop(char*);

/*
Hàm tạo ra 1 lớp với tên cụ thể, trả về con trỏ tới lớp được tạo ra (đối với dữ liệu từ file)
*/
dslop* create_lop(char*);

/*
Hàm tạo ra 1 lớp với tên cụ thể được người dùng nhập vào từ bàn phím
*/
dslop* create_lop();

/*
Hàm tạo mới sinh viên, trả về 1 con trỏ trỏ tới sinh viên đó (đối với dữ liệu từ file)
*/
dssv* create_sinhvien(char*, char*, char*, char*, char*, char*, char*);

/*
Hàm tạo mới sinh viên với dữ liệu được nhập từ bàn phím
*/
dssv* create_sinhvien();

/*
Hàm chèn 1 lớp vào danh sách móc nối các lớp (đối với dữ liệu từ file)
*/
void insert_lop(dslop*);

/*
Hàm chèn 1 sinh viên vào 1 lớp cụ thể và sắp xếp thứ tự tên VN
*/
void insert_sinhvien(dslop*, dssv*);

/*
Hàm hiển thị thông tin 1 lớp cụ thể
*/
void show_lop(dslop*);

/*
Hàm hiển thị thông tin của 1 sinh viên cụ thể
*/
void show_sinhvien(dssv*);

/*
Hàm hiển thị danh sách các lớp và danh sách sinh viên tương ứng với từng lớp
*/
void show_list_lop();

/*
Hàm kiểm tra tên của 2 sinh viên theo kiểu VN
*/
bool checkSort(dssv*, dssv*);



/*
Các biến toàn cục
*/
dslop* head_dslop = NULL; // con trỏ trỏ tới đầu danh sách các lớp được móc nối
char name[1000]; // biến tạm thời để lưu tên nhập từ bàn phím
char buffer [33]; // biến vùng đệm cho việc chuyển int thành char* để lưu file



/*
Hàm đọc đọc dữ liệu với path = "dssv.txt"
*/
void read_file_input(char* path) {
    FILE* f = fopen(path, "r"); // mở file

    // các biến tạm thời để lưu dữ liệu từ file
    char ten_lop[100],
        shsv[100],
        hoten[100],
        gioi_tinh[10],
        ng[10],
        th[10],
        na[10],
        diem[10];

    // lắp đến khi hết file
    while(!feof(f)) {
        // đọc
        fgets(ten_lop, 99, f);
        ten_lop[strlen(ten_lop) - 1] = '\0';
        // cout << ten_lop << endl;
        fgets(shsv, 99, f);
        shsv[strlen(shsv) - 1] = '\0';
        // cout << shsv << endl;
        fgets(hoten, 99, f);
        hoten[strlen(hoten) - 1] = '\0';
        // cout << hoten << endl;
        fgets(ng, 9, f);
        ng[strlen(ng) - 1] = '\0';
        // cout << atoi(ng) << endl;
        fgets(th, 9, f);
        th[strlen(th) - 1] = '\0';
        // cout << atoi(th) << endl;
        fgets(na, 9, f);
        na[strlen(na) - 1] = '\0';
        // cout << atoi(na) << endl;
        fgets(gioi_tinh, 99, f);
        gioi_tinh[strlen(gioi_tinh) - 1] = '\0';
        // cout << gioi_tinh << endl;
        fgets(diem, 9, f);
        diem[strlen(diem) - 1] = '\0';
        // cout << atoi(diem) << endl;

        // gọi hàm để chèn thông tin sinh viên vừa đọc vào lớp, chèn lớp vào danh sách lớp
        insert_from_file(ten_lop, shsv, hoten, ng, th, na, gioi_tinh, diem);
    }

    // đóng file
    fclose(f);
}



/*
Hàm ghi dẽ liệu với path = "dssv_output.txt"
*/
void write_file_output(char* path) {
    FILE* f = fopen(path, "w"); // mở file để ghi
    dslop* loptmp = head_dslop;
    while(loptmp != NULL) {
        dssv* svtmp = loptmp->firstsvOflop;
        while(svtmp != NULL) {
            fprintf(f, loptmp->tenlop);
            fprintf(f, "\n");
            fprintf(f, svtmp->shsv);
            fprintf(f, "\n");
            fprintf(f, svtmp->Hoten);
            fprintf(f, "\n");
            fprintf(f, itoa(svtmp->ns.Ng, buffer, 10));
            fprintf(f, "\n");
            fprintf(f, itoa(svtmp->ns.Th, buffer, 10));
            fprintf(f, "\n");
            fprintf(f, itoa(svtmp->ns.Na, buffer, 10));
            fprintf(f, "\n");
            fprintf(f, svtmp->gioitinh);
            fprintf(f, "\n");
            fprintf(f, itoa(svtmp->diem, buffer, 10));
            fprintf(f, "\n");

            svtmp = svtmp->nextsv;
        }
        loptmp = loptmp->nextlop;
    }

    // đóng file
    fclose(f);
}


/*
Hàm tạo mới 1 lớp (với dữ liệu từ file)
*/
dslop* create_lop(char* ten_lop) {
    dslop* tmp = new dslop();
    // cấp phát động cho tenlop đủ với chiều dài tên 
    tmp->tenlop = (char*) malloc((strlen(ten_lop)) * sizeof(char));
    // gán tên đó vào lớp
    strcpy(tmp->tenlop, ten_lop);
    tmp->nextlop = NULL;
    tmp->firstsvOflop = NULL;
    return tmp;
}


/*
Hàm tìm kiếm lớp, nếu không có thì tạo mới lớp
Trả về con trỏ tới lớp vừa tạo
*/
dslop* search_lop(char* ten_lop) {
    // nếu chưa có lớp nào thì gán head = lớp đó
    if(head_dslop == NULL) {
        head_dslop = create_lop(ten_lop);
        return head_dslop;
    }
    // duyệt qua các lớp xem đã tồn tại chưa
    dslop* tmp = head_dslop;
    while(tmp != NULL) {
        if(strcmp(tmp->tenlop, ten_lop) == 0) {
            // nếu tìm thấy lớp đã tồn tại thì return lớp đó
            return tmp;
        } else {
            tmp = tmp->nextlop;
        }
    }
    // Nếu không tìm thấy thì tạo mới
    if(tmp == NULL) {
        tmp = head_dslop;
        // duyệt đến cuối danh sách
        while(tmp->nextlop != NULL) {
            tmp = tmp->nextlop;
        }
        // gán lớp đó vào cuối danh sách
        tmp->nextlop = create_lop(ten_lop);
    }
    // trả về lớp đó
    return tmp->nextlop;
}



/*
Hàm tạo mới sinh viên với dữ liệu đọc từ file
*/
dssv* create_sinhvien(char* shsv, char* hoten, char* ng, char* th, char* na, char* gioi_tinh, char* diem) {
    dssv* tmp = new dssv();

    strcpy(tmp->shsv, shsv);
    // cấp phát động cho tên 
    tmp->Hoten = (char*) malloc((strlen(hoten)) * sizeof(char));
    // gán giá trị cho tên
    strcpy(tmp->Hoten, hoten);
    // gán giá trị cho ngày tháng năm sinh, chuyển đổi char về int
    tmp->ns.Ng = atoi(ng);
    tmp->ns.Th = atoi(th);
    tmp->ns.Na = atoi(na);

    strcpy(tmp->gioitinh, gioi_tinh);

    tmp->diem = atoi(diem);

    tmp->nextsv = NULL;

    // tách tên từ họ và tên
    int space = -1; // biến đánh dấu vị trí dấu cách cuối cùng trong tên
    for(int i = strlen(tmp->Hoten) - 1; i >= 0; i--) {
        if(tmp->Hoten[i] == ' ') {
            space = i;
            // nếu tìm thấy thì thoát lặp
            break;
        }
    }
    if(space != -1) { // nếu có dấu cách
        tmp->ten = new char[strlen(tmp->Hoten) - space - 1];
        strcpy(tmp->ten, "");
        // gán cho tên các kí tự từ vị trí dấu cách cuối cùng đến hết họ và tên
        for(int i = space + 1; i < strlen(tmp->Hoten); i++) {
            strncat(tmp->ten, &(tmp->Hoten[i]), 1);
        }
    } else { // nếu không có dấu cách
        tmp->ten = new char[strlen(tmp->Hoten)];
        strncpy(tmp->ten, tmp->Hoten, strlen(tmp->Hoten));
    }
    // trả về sinh viên đó
    return tmp;
}
 


/*
Hàm chèn sinh viên vào lớp tương ứng, chèn lớp vào danh sách lớp
*/
void insert_from_file(char* ten_lop, char* shsv, char* hoten, char* ng, char* th, char* na, char* gioi_tinh, char* diem) {
    dslop* tmp = search_lop(ten_lop); // tìm lớp của sinh viên
    dssv* sv = create_sinhvien(shsv, hoten, ng, th, na, gioi_tinh, diem); // tạo mới sinh viên
    insert_sinhvien(tmp, sv); // chèn sinh viên vào lớp tìm được
}



/*
Hàm tạo ra lớp mới với dữ liệu được nhập từ bàn phím
*/
dslop* create_lop() {
    dslop* tmp = new dslop();

    cout << "ten lop: ";
    cin.getline(name, 999);
    tmp->tenlop = (char*) malloc((strlen(name) - 1) * sizeof(char));
    strcpy(tmp->tenlop, name);
    tmp->nextlop = NULL;
    tmp->firstsvOflop = NULL;

    return tmp;
}



/*
Hàm tạo ra sinh viên với dữ liệu dược nhập từ bàn phím
*/
dssv* create_sinhvien() {
    dssv* tmp = new dssv();

    cout << endl << "shsv: ";
    cin >> tmp->shsv;

    cout << "ho ten: ";
    cin.ignore();
    cin.getline(name, 999);
    tmp->Hoten = (char*) malloc((strlen(name) - 1) * sizeof(char));
    strcpy(tmp->Hoten, name);

    cout << "ngay sinh: ";
    cin >> tmp->ns.Ng;
    
    cout << "thang sinh: ";
    cin >> tmp->ns.Th;
    
    cout << "nam sinh: ";
    cin >> tmp->ns.Na;

    cout << "gioi tinh: ";
    cin.ignore();
    cin >> tmp->gioitinh;

    cout << "diem: ";
    cin >> tmp->diem;
    cin.ignore();

    tmp->nextsv = NULL;

    // tìm tên sinh viên (tương tự hàm cho dữ liệu từ file)
    int space = -1;
    for(int i = strlen(tmp->Hoten) - 1; i >= 0; i--) {
        if(tmp->Hoten[i] == ' ') {
            space = i;
            break;
        }
    }
    if(space != -1) {
        tmp->ten = new char[strlen(tmp->Hoten) - space - 1];
        strcpy(tmp->ten, "");
        for(int i = space + 1; i < strlen(tmp->Hoten); i++) {
            strncat(tmp->ten, &(tmp->Hoten[i]), 1);
        }
    } else {
        tmp->ten = new char[strlen(tmp->Hoten)];
        strncpy(tmp->ten, tmp->Hoten, strlen(tmp->Hoten));
    }
    // trả về sinh viên đó
    return tmp;
}



/*
Hàm chèn 1 lớp vào danh sách lớp 
*/
void insert_lop(dslop* lop) {
    if(head_dslop == NULL) {
        // nếu chưa có lớp nào, gán head = lớp đó
        head_dslop = lop;
    } else {
        // duyệt đến cuối danh sách lớp
        dslop* tmp = head_dslop;
        while(tmp->nextlop != NULL) {
            tmp = tmp->nextlop;
        }
        // gán lớp đó vào cuối danh sách
        tmp->nextlop = lop;
    }
}



/*
Hàm kiểm tra so sánh tên 2 sinh viên theo kiểu VN
*/
bool checkSort(dssv* tmp, dssv* sv) {
    // so sánh tên
    int check = strcmp(tmp->ten, sv->ten); // check = 0: bằng nhau, >0: lớn hơn
    if(check > 0) {
        return true;
    } else if(check == 0) {
        // nếu tên bằng nhau so sánh tiếp họ và tên
        if(strcmp(tmp->Hoten, sv->Hoten) >= 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}



/*
Hàm chèn sinh viên vào lớp
*/
void insert_sinhvien(dslop* lop, dssv* sv) {
    if(lop->firstsvOflop == NULL) {
        // nếu lớp chưa có sinh viên thì gán 
        lop->firstsvOflop = sv;
    } else {
        dssv* tmp = lop->firstsvOflop;
        // nếu lớp chỉ có 1 sinh viên
        if(tmp->nextsv == NULL) {
            if(checkSort(tmp, sv)) {
                // chèn sinh viên lên đầu danh sách 
                sv->nextsv = tmp;
                lop->firstsvOflop = sv;
            } else {
                // chèn vào cuối danh sách
                tmp->nextsv = sv;
            }
        } else {
            // nếu sinh viên đó có thể chèn ở đầu danh sách sinh viên
            if(checkSort(tmp, sv)) {
                sv->nextsv = tmp->nextsv;
                lop->firstsvOflop = sv;
            }
            // duyệt danh sách sinh viên trong lớp
            while(tmp->nextsv != NULL) {
                if(checkSort(tmp->nextsv, sv)) {
                    // dừng khi sinh viên tiếp theo bị vi phạm
                    break;
                } else {
                    tmp = tmp->nextsv;
                }
            }
            // chèn sinh viên vào vị trí vi phạm
            sv->nextsv = tmp->nextsv;
            tmp->nextsv = sv;
        }
    }
}



/*
Hàm hiển thị thông tin 1 lớp
*/
void show_lop(dslop* lop) {
    cout << endl << "ten lop: " << lop->tenlop << endl;
    dssv* tmp = lop->firstsvOflop;
    while(tmp != NULL) {
        show_sinhvien(tmp);
        tmp = tmp->nextsv;
    }
}



/*
Hàm hiển thị thông tin 1 sinh viên
*/
void show_sinhvien(dssv* sv) {
    cout << endl;
    cout << "shsv: " << sv->shsv << endl;
    cout << "ho ten: '" << sv->Hoten << "'" << endl;
    cout << "ten: '" << sv->ten << "'" << endl;
    cout << "ngay sinh: " << sv->ns.Ng << endl;
    cout << "thang sinh: " << sv->ns.Th << endl;
    cout << "nam sinh: " << sv->ns.Na << endl;
    cout << "gioi tinh: " << sv->gioitinh << endl;
    cout << "diem: " << sv->diem << endl;
}



/*
Hàm hiển thị thông tin danh sách các lớp
*/
void show_list_lop() {
    dslop* tmp = head_dslop;
    while(tmp != NULL) {
        show_lop(tmp);
        tmp = tmp->nextlop;
    }
}



/*
    Hướng dẫn sử dụng
I. Option 1 - Đọc từ file
    Chỉ cần chạy chương trình
II. Option 2 - Nhập dữ liệu trực tiếp
    Làm theo hướng dẫn hiển thị (hãy nhập những gì cần nhập)
*/
int main() {

        // option 1
    read_file_input("dssv.txt");
    write_file_output("dssv_output.txt");
        // end of option 1


        // option 2
    // dslop* lopA = create_lop();
    // insert_lop(lopA);

    // dssv* sv1 = create_sinhvien();
    // insert_sinhvien(lopA, sv1);
    // dssv* sv2 = create_sinhvien();
    // insert_sinhvien(lopA, sv2);
    // dssv* sv3 = create_sinhvien();
    // insert_sinhvien(lopA, sv3);


    // dslop* lopB = create_lop();
    // insert_lop(lopB);

    // dssv* sv11 = create_sinhvien();
    // insert_sinhvien(lopB, sv11);
    // dssv* sv22 = create_sinhvien();
    // insert_sinhvien(lopB, sv22);
    // dssv* sv33 = create_sinhvien();
    // insert_sinhvien(lopB, sv33);
        // end of option 2

    // hiển thị
    show_list_lop();

    return 0;
}