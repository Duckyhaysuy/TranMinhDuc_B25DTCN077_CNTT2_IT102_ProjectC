#include <stdio.h>
#include <string.h>
#define MAX 999

// NGUYÊN M?U HÀM
int isEmpty(char s[]);
int findEmployeeIndex(char id[]);
void addEmployee();
void updateEmployee();
void deleteEmpId();
void showEmployees();

int i, j, k, n; // KHAI BÁO BI?N TOÀN C?C

struct Employee {      // Struct luu thông tin nhân viên
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

int isEmpty(char s[]) {      // HÀM KI?M TRA CHU?I R?NG
    if (s == NULL) return 1;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\t' &&
            s[i] != '\n' && s[i] != '\r')
            return 0;
    }
    return 1;
}

int findEmployeeIndex(char id[]) {    // TÌM NHÂN VIÊN THEO MÃ
    for (i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empId, id) == 0)
            return i;
    }
    return -1;
}

void addEmployee() {           // CASE 1: THÊM NHÂN VIÊN

    if (empCount >= MAX) {
        printf("Danh sach nhan vien da day!\n");
        return;
    }

    struct Employee employee;
    char temp[200];
    
    while (1) {             // Nhap mã NV
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

        if (findEmployeeIndex(employee.empId) != -1) {
            printf("Ma nhan vien da ton tai!\n");
            continue;
        }
        break;
    }

    // Nhap ten
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

        if (sscanf(temp, "%lf", &employee.baseSalary) != 1 ||
            employee.baseSalary <= 0) {
            printf("Nhap sai! Vui long nhap so duong.\n");
            continue;
        }
        break;
    }

    // Nhap ngay cong
    while (1) {
        printf("Nhap so ngay cong: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n"); 
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Ngay cong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%d", &employee.workDay) != 1 ||
            employee.workDay < 0) {
            printf("Nhap sai! Vui long nhap so nguyen >= 0.\n");
            continue;
        }
        break;
    }

    employees[empCount++] = employee;
    printf("Them nhan vien thanh cong!\n");
}

// CASE 2: Cap nhat nhan vien
void updateEmployee() {
    char id[20];
    char temp[200];
    int index;

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

    // Nhap ngay cong moi
    while (1) {
        printf("Nhap ngay cong moi: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }

        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Ngay cong khong duoc de trong!\n");
            continue;
        }

        if (sscanf(temp, "%d", &employees[index].workDay) != 1 ||
            employees[index].workDay < 0) {
            printf("Nhap sai! Vui long nhap so nguyen.\n");
            continue;
        }
        break;
    }

    printf("Cap nhat ho so thanh cong!\n");
}

// CASE 3: Xoa nhan vien
void deleteEmpId() {
    char id[20], temp[10];
    int index;

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
            return;
        }
        break;
    }

    while (1) {             // Xac nhan y/n?
        printf("Ban chac chan muon sa thai nhan vien %s? (y/n): ", id);
        if (fgets(temp, sizeof(temp), stdin) == NULL) continue;

        if (temp[0] == 'y' || temp[0] == 'Y')
            break;
        else if (temp[0] == 'n' || temp[0] == 'N') {
            printf("Da huy thao tac xoa nhan vien %s.\n",id);
            return;
        }
        else printf("Lua chon khong hop le!\n");
    }

    for (i = index; i < empCount - 1; i++) {    // Xóa (delete)
        employees[i] = employees[i + 1];
    }
    empCount--;

    printf("Xoa nhan vien %s thanh cong!\n",id);
}

void showEmployees() {      // CASE 4: Hien thi danh sach

    if (empCount == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    printf("STT | Ma NV      | Ten                      | Chuc vu            | Luong     | Ngay cong\n");
    printf("----+------------+--------------------------+--------------------+-----------+----------\n");

    for (i = 0; i < empCount; i++) {
        printf("%3d | %-10s | %-24s | %-18s | %9.2f | %8d\n", i + 1,
            employees[i].empId,
            employees[i].name,
            employees[i].position,
            employees[i].baseSalary,
            employees[i].workDay
        );
    }
}

int main() {        // MENU CHÍNH

    int choice;
    char temp[20];

    do {
        printf("+--------------------MENU--------------------+\n");
        printf("| 1. Them nhan vien.                         |\n");
        printf("| 2. Cap nhat ho so.                         |\n");
        printf("| 3. Nghi viec / Sa thai.                    |\n");
        printf("| 4. Hien thi danh sach.                     |\n");
        printf("| 5. Tra cuu.                                |\n");
        printf("| 6. Sap xep danh sach.                      |\n");
        printf("| 7. Cham cong ngay.                         |\n");
        printf("| 8. Xem bang cong.                          |\n");
        printf("| 9. Thoat.                                  |\n");
        printf("+--------------------------------------------+\n");
        printf("Nhap lua chon: ");

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            printf("Loi nhap!\n");
            continue;
        }
        temp[strcspn(temp, "\n")] = '\0';

        if (isEmpty(temp)) {
            printf("Lua chon khong duoc de trong!\n");
            continue;
        }
        if (sscanf(temp, "%d", &choice) != 1) {
            printf("Lua chon sai dinh dang!\n");
            continue;
        }
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                updateEmployee();
                break;
            case 3:
                deleteEmpId();
                break;
            case 4:
                showEmployees();
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                printf("Thoat Menu!\n");
                break;
            default:
                printf("Khong hop le!\n");
        }
    } while (choice != 9);
    
    return 0;
}

