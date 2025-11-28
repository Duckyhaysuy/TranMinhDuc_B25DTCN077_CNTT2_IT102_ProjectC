#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 999

// NGUYEN MAU HAM
int isEmpty(char s[]);
int findEmployeeIndex(char id[]);
void addEmployee();
void updateEmployee();
void deleteEmpId();
void showEmployees();
void searchEmployeeByName();
void sortEmployeesBySalary();
void timeKeeping();
void viewTimeSheet();
void menu();

int i, j, k, n; // KHAI BAO BIEN TOAN CUC

struct Employee {      // Struct luu thong tin nhan vien
    char empId[20];
    char name[50];
    char position[20];
    double baseSalary;
    int workDay;
};

struct TimeSheet {    // Struct cham cong
    char logId[20];
    char empId[20];
    char date[20];
    char status[10];
};

struct Employee employees[MAX];
int empCount = 0;
struct TimeSheet logs[MAX];
int logCount = 0;

int isEmpty(char s[]) {      // HAM KIEM TRA CHU?I R?NG
    if (s == NULL) return 1;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\t' &&
            s[i] != '\n' && s[i] != '\r')
            return 0;
    }
    return 1;
}

int findEmployeeIndex(char id[]) {    // TIM NHAN VIEN THEO MA
    for (i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empId, id) == 0)
            return i;
    }
    return -1;
}

int main() {
    menu();
    return 0;
}

// MENU CHINH
void menu() {
    int choice;

    do {
        printf("\n+----------------------------------------------------------+\n");
        printf("|          Danh sach quan ly nhan vien va cham cong        |\n");
        printf("+----------------------------------------------------------+\n");
        printf("|1. Them moi nhan vien                                     |\n");
        printf("|2. Cap nhat ho so nhan vien                               |\n");
        printf("|3. Sa thai / Xoa nhan vien                                |\n");
        printf("|4. Hien thi danh sach nhan vien                           |\n");
        printf("|5. Tra cuu nhan vien theo ten                             |\n");
        printf("|6. Sap xep danh sach                                      |\n");
        printf("|7. Cham cong                                              |\n");
        printf("|8. Xem Bang Cong                                          |\n");
        printf("|9. Thoat                                                  |\n");
        printf("+----------------------------------------------------------+\n");
        printf("Nhap lua chon: ");

        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: updateEmployee(); break;
            case 3: deleteEmpId(); break;
            case 4: showEmployees(); break;
            case 5: searchEmployeeByName(); break;
            case 6: sortEmployeesBySalary(); break;
            case 7: timeKeeping(); break;
            case 8: viewTimeSheet(); break;
            case 9: printf("Thoat chuong trinh!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }

    } while (choice != 9);
}

// CASE 1: THEM NHAN VIEN
void addEmployee() {

    // Kiem tra danh sach da day chua
    if (empCount >= MAX) {
        printf("Danh sach nhan vien da day!\n");
        return;
    }

    struct Employee employee;
    char temp[200];

    // Nhap ma nhan vien
    while (1) {
        printf("Nhap ma nhan vien: ");
        if (fgets(employee.empId, sizeof(employee.empId), stdin) == NULL) {
            printf("Loi nhap! Thu lai.\n");
            continue;
        }
        employee.empId[strcspn(employee.empId, "\n")] = '\0';

        if (isEmpty(employee.empId)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        // THÊM: Không cho phép ID bat dau bang '-'
        if (employee.empId[0] == '-') {
            printf("Ma nhan vien khong hop le! Khong duoc bat dau bang dau '-'.\n");
            continue;
        }

        if (findEmployeeIndex(employee.empId) != -1) {
            printf("Ma nhan vien da ton tai!\n");
            continue;
        }
        break;
    }

    // Nhap ten nhan vien
    while (1) {
        printf("Nhap ten nhan vien: ");
        if (fgets(employee.name, sizeof(employee.name), stdin) == NULL) {
            printf("Loi nhap!\n"); 
            continue;
        }
        employee.name[strcspn(employee.name, "\n")] = '\0';

        if (isEmpty(employee.name)) {
            printf("Ten khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap chuc vu
    while (1) {
        printf("Nhap chuc vu: ");
        if (fgets(employee.position, sizeof(employee.position), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        employee.position[strcspn(employee.position, "\n")] = '\0';

        if (isEmpty(employee.position)) {
            printf("Chuc vu khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap luong co ban
    while (1) {
        printf("Nhap luong co ban: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Luong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%lf", &employee.baseSalary) != 1 || employee.baseSalary <= 0) {
            printf("Nhap sai! Vui long nhap so duong.\n");
            continue;
        }
        break;
    }

    // Nhap ngay cong - OPTION A/B
    while (1) {
        printf("Nhap ngay cong (Chon A mac dinh = 0 hoac B tu 1->31 ngay trong thang): ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';

        // Kiem tra enter trong
        if (isEmpty(temp)) {
            printf("Ngay cong khong duoc bo trong vui long chon option A/B\n");
            continue;
        }

        // Option A mac dinh = 0
        if (temp[0] == 'A' || temp[0] == 'a') {
            employee.workDay = 0;
            break;
        }

        // Option B nhap ngay cong tu 1->31
        if (temp[0] == 'B' || temp[0] == 'b') {
            while (1) {
                printf("Nhap so ngay cong (1 -> 31): ");

                if (fgets(temp, sizeof(temp), stdin) == NULL) {
                    printf("Loi nhap!\n");
                    continue;
                }
                temp[strcspn(temp, "\n")] = '\0';

                if (isEmpty(temp)) {
                    printf("Khong duoc bo trong ngay cong, vui long nhap lai\n");
                    continue;
                }

                if (sscanf(temp, "%d", &employee.workDay) != 1 || employee.workDay <= 0) {
                    printf("Nhap sai, ngay cong phai la so duong\n");
                    continue;
                }

                if (employee.workDay > 31) {
                    printf("Nhap sai, ngay cong phai tu 1 den 31\n");
                    continue;
                }

                break;
            }
            break;
        }

        // Nhap truc tiep so ngay cong (khong chon A/B)
        int workDayTmp;
        if (sscanf(temp, "%d", &workDayTmp) == 1) {
            if (workDayTmp < 0) {
                printf("Nhap sai, ngay cong phai la so duong\n");
                continue;
            }
            if (workDayTmp > 31) {
                printf("Nhap sai, ngay cong phai tu 1 den 31\n");
                continue;
            }
            employee.workDay = workDayTmp;
            break;
        }

        printf("Lua chon khong hop le! Nhan A/B hoac nhap so.\n");
    }

    employees[empCount++] = employee;
    printf("Them nhan vien thanh cong!\n");
}

// CASE 2: Cap nhat nhan vien
void updateEmployee() {
    char id[20];
    char temp[200];
    int index;

    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }
    
    while (1) {
        printf("Nhap ma nhan vien can cap nhat: ");

        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (isEmpty(id)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        index = findEmployeeIndex(id);
        if (index == -1) {
            printf("Khong tim thay ma '%s'. Vui long nhap lai!\n", id);
            continue;
        }
        break;
    }

    // Nhap ten moi
    while (1) {
        printf("Nhap ten moi: ");
        if (fgets(employees[index].name, sizeof(employees[index].name), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        employees[index].name[strcspn(employees[index].name, "\n")] = '\0';

        if (isEmpty(employees[index].name)) {
            printf("Ten khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap chuc vu moi
    while (1) {
        printf("Nhap chuc vu moi: ");
        if (fgets(employees[index].position, sizeof(employees[index].position), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        employees[index].position[strcspn(employees[index].position, "\n")] = '\0';

        if (isEmpty(employees[index].position)) {
            printf("Chuc vu khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap luong moi
    while (1) {
        printf("Nhap luong co ban moi: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Luong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%lf", &employees[index].baseSalary) != 1 ||
            employees[index].baseSalary <= 0) {
            printf("Nhap sai! Vui long nhap so duong.\n");
            continue;
        }
        break;
    }

    // ===== NH?P NGÀY CÔNG M?I (THÊM KI?M TRA 0 ? 31) =====
    while (1) {
        printf("Nhap ngay cong moi (0-31): ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Ngay cong khong duoc de trong!\n");
            continue;
        }

        // ch? nh?n s? nguyên
        if (sscanf(temp, "%d", &employees[index].workDay) != 1) {
            printf("Chi duoc nhap so nguyen tu 0 den 31!\n");
            continue;
        }

        // ki?m tra ph?m vi
        if (employees[index].workDay < 0 || employees[index].workDay > 31) {
            printf("Ngay cong phai nam trong khoang 0 - 31!\n");
            continue;
        }

        break;
    }

    printf("Cap nhat ho so thanh cong!\n");
}

// CASE 3: Xoa nhan vien
void deleteEmpId() {
    char id[20];
    int index;
    char confirm;

    // Nhap ma nhan vien can xoa
    while (1) {
        printf("Nhap ma nhan vien can xoa: ");
        if (fgets(id, sizeof(id), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        id[strcspn(id, "\n")] = '\0';

        if (isEmpty(id)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }

        index = findEmployeeIndex(id);
        if (index == -1) {
            printf("Khong tim thay nhan vien co ma %s!\n", id);
            return;  // neu khong tim thay thi thoat ham
        }
        break;
    }

    // Xac nhan xoa
    while (1) {
        printf("Ban co chac muon xoa nhan vien %s? (y/n): ", id);
        if (scanf(" %c", &confirm) != 1) {
            printf("Loi nhap!\n");
            while (getchar() != '\n'); // xoa bo nho dem
            continue;
        }
        while (getchar() != '\n'); // xoa bo nho dem
        if (confirm == 'y' || confirm == 'Y') {
            // Xoa nhan vien
            for (i = index; i < empCount - 1; i++) {
                employees[i] = employees[i + 1];
            }
            empCount--;
            printf("Xoa nhan vien %s thanh cong!\n", id);
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            printf("Huy xoa nhan vien %s!\n", id);
            break;
        } else {
            printf("Vui long nhap y hoac n!\n");
        }
    }
}

// CASE 4: Hien thi danh sach
void showEmployees() {
    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }
    int perPage = 1;      // so NV moi trang
    int totalPage = (empCount + perPage - 1) / perPage;
    int page = 1;
    char choice[10];

    while (1) {
        int start = (page - 1) * perPage;
        int end = start + perPage;
        if (end > empCount) end = empCount;

        printf("\n===== DANH SACH NHAN VIEN (Trang %d/%d) =====\n", page, totalPage);
        printf("STT | Ma NV      | Ten                      | Chuc vu            | Luong     | Ngay cong\n");
        printf("----+------------+--------------------------+--------------------+-----------+----------\n");

        for (i = start; i < end; i++) {
            printf("%3d | %-10s | %-24s | %-18s | %9.2f | %8d\n", 
                i + 1,
                employees[i].empId,
                employees[i].name,
                employees[i].position,
                employees[i].baseSalary,
                employees[i].workDay
            );
        }
        // MENU PHAN TRANG
        printf("\n(N) Trang tiep | (P) Trang truoc | (G) Nhay den trang | (Q) Thoat: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        // NEXT PAGE
        if (strcmp(choice, "N") == 0 || strcmp(choice, "n") == 0) {
            if (page < totalPage) page++;
            else printf("Ban dang o trang cuoi!\n");
        }
        // PREVIOUS PAGE
        else if (strcmp(choice, "P") == 0 || strcmp(choice, "p") == 0) {
            if (page > 1) page--;
            else printf("Ban dang o trang dau!\n");
        }
        // GO TO PAGE
        else if (strcmp(choice, "G") == 0 || strcmp(choice, "g") == 0) {
            char pageInput[10];
            int goPage;

            printf("Nhap so trang can xem (1-%d): ", totalPage);
            fgets(pageInput, sizeof(pageInput), stdin);
            pageInput[strcspn(pageInput, "\n")] = '\0';

            // Kiem tra có phai toàn so không
            int valid = 1;
            for (i = 0; pageInput[i]; i++) {
                if (!isdigit(pageInput[i])) {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                printf("So trang khong hop le!\n");
                continue;
            }
            goPage = atoi(pageInput);
            if (goPage < 1 || goPage > totalPage) {
                printf("Trang %d khong ton tai!\n", goPage);
            } else {
                page = goPage;
            }
        }
        // QUIT
        else if (strcmp(choice, "Q") == 0 || strcmp(choice, "q") == 0) {
            printf("Thoat hien thi danh sach.\n");
            break;
        }
        else {
            printf("Lua chon khong hop le!\n");
        }
    }
}

// ham hien thi
void printEmployee(struct Employee employees) {
    printf("Ma NV: %-10s | Ten: %-20s | Chuc vu: %-15s | Luong: %8.2f | Ngay cong: %d\n",
        employees.empId, employees.name, employees.position, employees.baseSalary, employees.workDay);
}

// Case 5: Tra cuu
void searchEmployeeByName() {
    char searchName[50];
    char lowerInput[50];
    char lowerName[50];

    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong! Khong the tra cuu.\n");
        return;
    }

    while (1) {
        printf("Nhap ten nhan vien can tra cuu: ");
        if (fgets(searchName, sizeof(searchName), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        searchName[strcspn(searchName, "\n")] = '\0';

        // KHÔNG CHO KHOANG TRONG ÐAU/ CUOI
        if (searchName[0] == ' ' || searchName[strlen(searchName) - 1] == ' ') {
            printf("Khong duoc de khoang trang o dau hoac cuoi chuoi!\n");
            continue;
        }

        if (isEmpty(searchName)) {
            printf("Ten tim kiem khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Chuyen chuoi nhap vào ve chu thuong
    for (i = 0; searchName[i]; i++)
        lowerInput[i] = tolower(searchName[i]);
    lowerInput[i] = '\0';

    printf("Da tim thay nhan vien ten %s.\n", searchName);
    printf("---- Ket qua tim kiem ----\n");

    int found = 0;

    for (i = 0; i < empCount; i++) {

        // Chuy?n tên nhân viên sang lowercase
        for (j = 0; employees[i].name[j]; j++)
            lowerName[j] = tolower(employees[i].name[j]);
        lowerName[j] = '\0';

        //không phân biet hoa/thuong
        if (strstr(lowerName, lowerInput) != NULL) {
            printEmployee(employees[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay nhan vien nao co ten '%s'!\n", searchName);
    }
}

// CASE 6: Sap xep danh sach theo luong co ban
void sortEmployeesBySalary() {
    if (empCount == 0) {
        printf("Danh sach nhan vien hien dang trong!\n");
        return;
    }
    char choice[10];
    // Chon kieu sap xep
    while (1) {
        printf("Chon kieu sap xep (1.Tang, 2.Giam): ");

        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        choice[strcspn(choice, "\n")] = '\0';

        if (isEmpty(choice)) {
            printf("Lua chon khong duoc de trong!\n");
            continue;
        }

        if (choice[0] == '1' || choice[0] == '2') {
            break;
        }

        printf("Lua chon khong hop le. Vui long nhap 1 hoac 2.\n");
    }

    // Bubble Sort
    for (i = 0; i < empCount - 1; i++) {
        for (j = 0; j < empCount - i - 1; j++) {

            int condition = 0;

            if (choice[0] == '1') {   // Tang
                condition = employees[j].baseSalary > employees[j + 1].baseSalary;
            } else {                  // Gi?m
                condition = employees[j].baseSalary < employees[j + 1].baseSalary;
            }

            if (condition) {
                struct Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    printf("\n---- Danh sach sau khi sap xep ----\n");
    showEmployees();
    printf("\nSap xep thanh cong!\n");
}

// Check nam nhuan hay khong? (Cho case 7)
int isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
int isValidDate(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12 || d < 1){
		return 0;
	}
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isLeapYear(y)){
        return d <= 29;
    }
    return d <= daysInMonth[m];
}

// Case 7 Cham cong
void timeKeeping() {
    char checkId[20];
    char date[20];

    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    // LAY NGAY HIEN TAI
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    int today_d = now.tm_mday;
    int today_m = now.tm_mon + 1;
    int today_y = now.tm_year + 1900;

    // NHAP MA KHONG DE TRONG
    while (1) {
        printf("Nhap ma nhan vien cham cong: ");
        fgets(checkId, sizeof(checkId), stdin);
        checkId[strcspn(checkId, "\n")] = '\0';

        if (isEmpty(checkId)) {
            printf("Ma nhan vien khong duoc de trong!\n");
            continue;
        }
        break;
    }

    int index = findEmployeeIndex(checkId);
    if (index == -1) {
        printf("Khong tim thay nhan vien '%s'!\n", checkId);
        return;
    }

    // NHAP NGAY CO KIEM TRA HOP LE
    int d, m, y;
    while (1) {
        printf("Nhap ngay cham cong (dd/mm/yyyy): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0';

        // KIEM TRA KHOANG TRONG ÐAU / CUOI
        if (date[0] == ' ' || date[strlen(date) - 1] == ' ') {
            printf("Khong duoc de khoang trang o dau hoac cuoi chuoi!\n");
            continue;
        }

        if (isEmpty(date)) {
            printf("Ngay khong duoc de trong!\n");
            continue;
        }

        if (sscanf(date, "%d/%d/%d", &d, &m, &y) != 3) {
            printf("Dinh dang khong hop le! Vui long nhap theo dd/mm/yyyy.\n");
            continue;
        }

        if (!isValidDate(d, m, y)) {
            printf("Ngay %s khong hop le! Vui long nhap lai.\n", date);
            continue;
        }

        // KHONG CHO CHAM CONG NGAY TUONG LAI
        if (y > today_y ||
           (y == today_y && m > today_m) ||
           (y == today_y && m == today_m && d > today_d)) {
            printf("Khong the cham cong ngay trong tuong lai! Hom nay la %02d/%02d/%04d.\n",
                   today_d, today_m, today_y);
            continue;
        }

        break;
    }

    // KIEM TRA TRUNG CHAM CONG
    for (i = 0; i < logCount; i++) {
        if (strcmp(logs[i].empId, checkId) == 0 &&
            strcmp(logs[i].date, date) == 0) {
            printf("Nhan vien %s da cham cong vao ngay %s roi.\n", checkId, date);
            return;
        }
    }

    // CHAM CONG
    employees[index].workDay++;

    sprintf(logs[logCount].logId, "LOG%03d", logCount + 1);
    strcpy(logs[logCount].empId, checkId);
    strcpy(logs[logCount].date, date);
    strcpy(logs[logCount].status, "Di lam");
    logCount++;

    printf("Cham cong ngay %s cho nhan vien %s thanh cong!\n", date, checkId);
}

// case 8: xem bang cong
void viewTimeSheet() {
    char viewEmpId[20];
    char buffer[50];
    int sDay, sMonth, sYear;   // ngày bat dau
    int day, month, year;
    int x, idx;

    // Lay ngày hien tai
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    int cDay = today.tm_mday;
    int cMonth = today.tm_mon + 1;
    int cYear = today.tm_year + 1900;

    // Nhap ID
    do {
        printf("Nhap ID nhan vien muon xem cham cong: ");
        fgets(viewEmpId, sizeof(viewEmpId), stdin);
        viewEmpId[strcspn(viewEmpId, "\n")] = 0;

        if (strlen(viewEmpId) == 0) {
            printf("ID khong duoc bo trong! Vui long nhap lai.\n");
        }
    } while (strlen(viewEmpId) == 0);

    int empIndex = findEmployeeIndex(viewEmpId);
    if (empIndex == -1) {
        printf("Khong tim thay nhan vien co ID %s!\n", viewEmpId);
        return;
    }

    // Nhap ngày bat dau
    while (1) {
        printf("Nhap ngay bat dau (dd/mm/yyyy): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (sscanf(buffer, "%d/%d/%d", &sDay, &sMonth, &sYear) != 3) {
            printf("Dinh dang phai dd/mm/yyyy!\n");
            continue;
        }

        if (sYear < 2000) {
            printf("Nam phai >= 2000!\n");
            continue;
        }
        if (sMonth < 1 || sMonth > 12) {
            printf("Thang khong hop le!\n");
            continue;
        }
        if (sDay < 1 || sDay > 31) {
            printf("Ngay khong hop le!\n");
            continue;
        }

        break;
    }

    // Không cho xem vuot tuong lai
    if (sYear > cYear ||
       (sYear == cYear && sMonth > cMonth) ||
       (sYear == cYear && sMonth == cMonth && sDay > cDay)) 
    {
        printf("Ngay bat dau khong duoc vuot qua hien tai!\n");
        return;
    }

    // TAO DANH SÁCH TAT CA NGÀY TU START -> HIEN TAI
    struct DateList {
        char dateStr[20];
    } list[2000];

    int listCount = 0;

    day = sDay;
    month = sMonth;
    year = sYear;

    while (1) {
        sprintf(list[listCount].dateStr, "%02d/%02d/%04d", day, month, year);
        listCount++;

        // Neu da den hien tai thì dung
        if (day == cDay && month == cMonth && year == cYear) break;

        // Tang ngày
        int maxDay;

        if (month == 2) {
            maxDay = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            maxDay = 30;
        } else {
            maxDay = 31;
        }

        day++;
        if (day > maxDay) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    // PHÂN TRANG
    int perPage = 10;
    int totalPage = (listCount + perPage - 1) / perPage;
    int page = 1;
    char cmd[10];

    while (1) {
        system("cls");
        printf("\n======= Bang cham cong %s (Trang %d/%d) =======\n",
               viewEmpId, page, totalPage);
        printf("ID Log     | Ngay        | Trang thai\n");
        printf("----------------------------------------\n");

        int start = (page - 1) * perPage;
        int end = start + perPage;
        if (end > listCount) end = listCount;

        for (idx = start; idx < end; idx++) {
            int found = 0;

            for (x = 0; x < logCount; x++) {
                if (strcmp(logs[x].empId, viewEmpId) == 0 &&
                    strcmp(logs[x].date, list[idx].dateStr) == 0)
                {
                    printf("%-10s | %-10s | %s\n",
                           logs[x].logId, logs[x].date, logs[x].status);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("---------- | %-10s | Nghi lam\n",
                       list[idx].dateStr);
            }
        }
        printf("----------------------------------------\n");
        printf("[N]ext  [P]revious  [G]o to page  [Q]uit\n");
        printf("Chon: ");

        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcasecmp(cmd, "N") == 0) {
            if (page < totalPage) page++;
        } 
        else if (strcasecmp(cmd, "P") == 0) {
            if (page > 1) page--;
        }
        else if (strcasecmp(cmd, "G") == 0) {
            printf("Nhap trang muon den (1 - %d): ", totalPage);
            fgets(cmd, sizeof(cmd), stdin);
            int newPage = atoi(cmd);
            if (newPage >= 1 && newPage <= totalPage) page = newPage;
        }
        else if (strcasecmp(cmd, "Q") == 0) {
            return;
        }
    }
}
