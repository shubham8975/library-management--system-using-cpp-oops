#include <bits/stdc++.h>
using namespace std;

class book
{
    char bno[10];
    char bname[50];
    char aname[20];

public:
    void create_book()
    {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter The book no.";
        cin >> bno;
        cout << "\n\nEnter The Name of The Book ";
        cin >> bname;
        cout << "\n\nEnter The Author's Name ";
        cin >> aname;
        cout << "\n\n\nBook Created..";
    }

    void show_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nBook Name : " << bname;
        
        cout << "Author Name : " << aname;
    }

    void modify_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nModify Book Name : ";
        cin >> bname;
        cout << "\nModify Author's Name of Book : ";
        cin >> bname;
    }

    char *retbno()
    {
        return bno;
    }

    void report()
    {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;

public:
    void create_student()
    {

        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The admission no. ";
        cin >> admno;
        cout << "\n\nEnter The Name of The Student ";
        cin >> name;
        token = 0;

        cout << "\n\nStudent Record Created..";
    }

    void show_student()
    {
        cout << "\nAdmission no. : " << admno;
        cout << "\nStudent Name : " << name;

        cout << "\nNo of Book issued : " << token;
        if (token == 1)
            cout << "\nBook No " << stbno;
    }

    void modify_student()
    {
        cout << "\nAdmission no. : " << admno;
        cout << "\nModify Student Name : ";
        cin >> name;
    }

    char *retadmno()
    {
        return admno;
    }

    char *retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token = 1;
    }

    void resettoken()
    {
        token = 0;
    }

    void getstbno(char t[])
    {
        strcpy(stbno, t);
    }

    void report()
    {
        cout << "\t" << admno << setw(10) << name << setw(20) << token << endl;
    }
};

fstream fp, fp1;
book bk;
student st;

void write_book()
{
    char ch;
    fp.open("book.txt", ios::out | ios::app);
    do
    {

        bk.create_book();
        fp.write((char *)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.txt", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char *)&st, sizeof(student));
        cout << "\n\ndo you want to add more record..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void display_spb(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.txt", ios::in);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmpi(bk.retbno(), n) == 0)
        {
            bk.show_book();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nBook does not exist";
}

void display_sps(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.txt", ios::in);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if ((strcmpi(st.retadmno(), n) == 0))
        {
            st.show_student();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nStudent does not exist";
}


void modify_book()
{
    char n[6];
    int found = 0;

    cout << "\n\n\tMODIFY BOOK REOCORD.... ";
    cout << "\n\n\tEnter The book no. of The book";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(book)) && found == 0)
    {
        if (strcmpi(bk.retbno(), n) == 0)
        {
            bk.show_book();
            cout << "\nEnter The New Details of book" << endl;
            bk.modify_book();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(book));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
}

void modify_student()
{
    char n[6];
    int found = 0;

    cout << "\n\n\tMODIFY STUDENT RECORD... ";
    cout << "\n\n\tEnter The admission no. of The student";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.retadmno(), n) == 0)
        {
            st.show_student();
            cout << "\nEnter The New Details of student" << endl;
            st.modify_student();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
}



void delete_student()
{
    char n[6];
    int flag = 0;

    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(student)))
    {
        if (strcmpi(st.retadmno(), n) != 0)
            fp2.write((char *)&st, sizeof(student));
        else
            flag = 1;
    }

    fp2.close();
    fp.close();
    remove("student.txt");
    rename("Temp.txt", "student.txt");
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
}

void delete_book()
{
    char n[6];

    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(book)))
    {
        if (strcmpi(bk.retbno(), n) != 0)
        {
            fp2.write((char *)&bk, sizeof(book));
        }
    }

    fp2.close();
    fp.close();
    remove("book.txt");
    rename("Temp.txt", "book.txt");
    cout << "\n\n\tRecord Deleted ..";
}

//        function to display all students list

void display_alls()
{

    fp.open("student.txt", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";

        return;
    }

    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(20) << "Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";

    while (fp.read((char *)&st, sizeof(student)))
    {
        st.report();
    }

    fp.close();
}

//        function to display Books list

void display_allb()
{
    // clrscr();
    fp.open("book.txt", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";

        return;
    }

    cout << "\n\n\t\tBook LIST\n\n";
    cout << "=========================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(20) << "Author\n";
    cout << "=========================================================================\n";

    while (fp.read((char *)&bk, sizeof(book)))
    {
        bk.report();
    }
    fp.close();
}

void book_issue()
{
    char sn[6], bn[6];
    int found = 0, flag = 0;

    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The student's admission no.";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.retadmno(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == 0)
            {
                cout << "\n\n\tEnter the book no. ";
                cin >> bn;
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmpi(bk.retbno(), bn) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n\n\t Book issued successfully \n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            }
            else
                cout << "You have not returned the last book ";
        }
    }
    if (found == 0)
        cout << "Student record not exist...";

    fp.close();
    fp1.close();
}



void book_deposit()
{
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;

    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The student admission no.";
    cin >> sn;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(student)) && found == 0)
    {
        if (strcmpi(st.retadmno(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == 1)
            {
                while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmpi(bk.retbno(), st.retstbno()) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        cout << "\n\nBook deposited in no. of days";
                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine has to deposited Rs. " << fine;
                        }
                        st.resettoken();
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char *)&st, sizeof(student));
                        cout << "\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            }
            else
                cout << "No book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Student record not exist...";

    fp.close();
    fp1.close();
}

void admin_menu()
{

    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << endl;
    cout << "1.CREATE STUDENT RECORD" << endl;
    cout << "2.DISPLAY ALL STUDENTS RECORD" << endl;
    cout << "3.DISPLAY SPECIFIC STUDENT RECORD " << endl;
    cout << "4.MODIFY STUDENT RECORD" << endl;
    cout << "5.DELETE STUDENT RECORD" << endl;
    cout << "6.CREATE BOOK " << endl;
    cout << "7.DISPLAY ALL BOOKS " << endl;
    cout << "8.DISPLAY SPECIFIC BOOK " << endl;
    cout << "9.MODIFY BOOK " << endl;
    cout << "10.DELETE BOOK " << endl;
    cout << "11.BACK TO MAIN MENU" << endl;
    cout << "Please Enter Your Choice (1-11) " << endl;
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        write_student();
        break;
    case 2:
        display_alls();
        break;
    case 3:
        char num[6];

        cout << "\n\n\t Please Enter The Admission No. ";
        cin >> num;
        display_sps(num);
        break;
    case 4:
        modify_student();
        break;
    case 5:
        delete_student();
        break;
    case 6:
        write_book();
        break;
    case 7:
        display_allb();
        break;
    case 8:
    {
        char num[6];

        cout << "\n\n\t Enter The book No. ";
        cin >> num;
        display_spb(num);
        break;
    }
    case 9:
        modify_book();
        break;
    case 10:
        delete_book();
        break;
    case 11:
        return;
    default:
        cout << "\a";
    }
    admin_menu();
}

int main()
{
    display_allb();
    cout << "\n\n\n\n\n";
    int ch;

    while (1)
    {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. BOOK ISSUE";
        cout << "\n\n\t02. BOOK DEPOSIT";
        cout << "\n\n\t03. ADMINISTRATOR MENU";
        cout << "\n\n\t04. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-4) ";

        cin >> ch;
        switch (ch)
        {
        case 1:
            book_issue();
            break;
        case 2:
            book_deposit();
            break;
        case 3:
            admin_menu();
            break;
        case 4:
            exit(0);
        default:
            cout << " ";
        }
    }
}
