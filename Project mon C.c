#include<stdio.h>
#include<string.h>
#define MAX 999

struct Employee{
    char empId[20];
    char name[50];
    char position[15]; 
    double baseSalary;
    int workDay;
};

struct TimeSheet{
    char logId[20];
    char empId[20];
    char date[20];
    char status[10];
};

struct Employee employees[MAX];
struct TimeSheet logs[MAX];

int empCount = 0;
int logCount = 0;
int i;
// hàm tìm tên theo id
int findEmployeeIndex(char id[]) {
    for(i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empId, id) == 0)
            return i;
    }
    return -1;
}

// case 1: Them moi nhan vien
void addEmployee() {                                              

    if (empCount >= MAX) {                                        
        printf("Danh sach nhan vien da day!\n");                  
        return;                                                   
    }

    struct Employee employee;                                     // Tao bien employee de nhap du lieu

    printf("Nhap ma nhan vien: ");                                
    fgets(employee.empId, sizeof(employee.empId), stdin);         
    employee.empId[strcspn(employee.empId, "\n")] = '\0';        

    if (strlen(employee.empId) == 0) {                            // Kiem tra rong?
        printf("Ma nhan vien khong hop le!\n");                   
        return;                                                   
    }

    for (i = 0; i < empCount; i++) {                              // Duyet danh sach de kiem tra trung ID
        if (strcmp(employee.empId, employees[i].empId) == 0) {    // So sánh mã NV
            printf("Ma nhan vien da ton tai!\n");                 
            return;                                               
        }
    }

    printf("Nhap ten nhan vien: ");                               
    fgets(employee.name, sizeof(employee.name), stdin);           
    employee.name[strcspn(employee.name, "\n")] = '\0';           

    if (strlen(employee.name) == 0) {                             // Kiem tra rong
        printf("Ten nhan vien khong hop le!\n");                  
        return;                                                   // Thoát hàm
    }

    printf("Nhap chuc vu: ");                                     
    fgets(employee.position, sizeof(employee.position), stdin);   
    employee.position[strcspn(employee.position, "\n")] = '\0';   

    if (strlen(employee.position) == 0) {                         // Kiem tra rong
        printf("Chuc vu khong hop le!\n");                        
        return;                                                   
    }

    printf("Nhap luong co ban: ");                                
    if (scanf("%lf", &employee.baseSalary) != 1 || employee.baseSalary <= 0) {                              
        printf("Luong khong hop le!\n");                          
        getchar();                                // Xóa buffer
        return;                                                   
    }
    getchar();                                                    // Xóa newline còn lai trong buffer

    employee.workDay = 0;                                         // Gán ngày công ban dau = 0

    employees[empCount] = employee;                               // Luu nhan vien vao mang
    empCount++;                                                   // Tang so luong nhan vien

    printf("Them nhan vien thanh cong!\n\n");                     // Báo thành công
}


//case 2:Cap nhat thong tin
void updateEmployee() {

    char id[20];

    printf("Nhap ma nhan vien can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findEmployeeIndex(id);
    if (index == -1) {
        printf("Khong tim thay nhan vien!\n");
        return;
    }

    printf("Nhap ten moi: ");
    fgets(employees[index].name, sizeof(employees[index].name), stdin);
    employees[index].name[strcspn(employees[index].name, "\n")] = '\0';

    printf("Nhap chuc vu moi: ");
    fgets(employees[index].position, sizeof(employees[index].position), stdin);
    employees[index].position[strcspn(employees[index].position, "\n")] = '\0';

    printf("Nhap luong co ban moi: ");
    if (scanf("%lf", &employees[index].baseSalary) != 1 || employees[index].baseSalary <= 0) {
        printf("Luong khong hop le!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    printf("Cap nhat thong tin thanh cong!\n");
}

//case 4: Hien thi danh sach
void showEmployees() {

    if (empCount == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("STT | empId      | Ten                      | Chuc vu             | Luong     | Ngay lam\n");
    printf("----+------------+--------------------------+---------------------+-----------+---------\n");

    for (i = 0; i < empCount; i++) {
        printf("%3d | %-10s | %-24s | %-20s | %9.2f | %7d\n", i + 1, employees[i].empId, employees[i].name, employees[i].position, employees[i].baseSalary, employees[i].workDay);
    }
}


// hàm main
int main() {
    int choice;

    do {
        printf("\nMenu\n");
        printf("1. Them nhan vien moi.\n");
        printf("2. Cap nhat ho so.\n");
        printf("3. Nghi viec/Sa thai.\n");
        printf("4. Hien thi danh sach.\n");
        printf("5. Tra cuu.\n");
        printf("6. Sap xep danh sach.\n");
        printf("7. Cham cong ngay.\n");
        printf("8. Xem bang cong.\n");
        printf("9. Thoat.\n");
        printf("Vui long nhap lua chon: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addEmployee();
                break;

            case 2:
                updateEmployee();
                break;

            case 3:
                
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
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 9);

    return 0;
}

