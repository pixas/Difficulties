#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
using namespace std;
struct student
{
    char no[12];
    char name[20];
    char date[7];
    char phone[12];
};
class Solution{
public:
    const char * file = "C:\\Users\\86130\\Desktop\\projects\\tasks\\cpp\\14and15contest\\output.txt";
    char max[12]="00000000000";
    
    char* strrev(char* str){
        int len = strlen(str);
        int i = 0;
        int j = len - 1;
        while (i < j){
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            i++;
            j--;
        }
        return str;
    }
    char * plus(char* str, char num)
    {
        strrev(str);
        int rem = 0;
        int len = strlen(str);
        int temp;
        int i;
        for (i = 0; i < len; i++)
        {
            temp = str[i] + num + rem - 2 * '0';
            str[i] = temp % 10 + '0';
            rem = temp / 10;
            num = '0';
        }
        if (rem == 1)
            str[i] = '1';
        strrev(str);
        return str;
    }
    int main()
    {
        char p = '1';
        int ct = 0;
        char name[20];
        char no[12];
        char date[7];
        char phone[12];
        char op[2];
        fstream finout;

        finout.open(file,ios_base::in|ios_base::binary|ios_base::out);
        

        student st;
        if (!finout.is_open())
        {
            cerr << "Open failed" << endl;
            exit(EXIT_FAILURE);
        }
        finout.seekg(0);
        while (finout.read((char*)&st, sizeof st))
        {
            if (strcmp(max,st.no)<0)
                strcpy(max,st.no);
        }
        
        cin >> op;

        while (op[0]!='\n')
        {
            finout.clear();
            if (op[0] == '1')
            {
                finout.seekg(0);
                cin >> no;
                while (finout.read((char*)&st, sizeof st))
                {
                    if (strcmp(no,st.no) == 0){
                        finout.seekp(0,ios_base::end);
                        plus(max,p);
                        strcpy(st.no,max);
                        finout.write((char* )&st,sizeof st);
                        break;
                    }
                }
            }
            else if (op[0] == '3')
            {
                cin >> name >> date >> phone;
                finout.seekp(0,ios_base::end);
                strcpy(st.name,name);
                plus(max,p);
                strcpy(st.no,max);
                strcpy(st.date,date);
                strcpy(st.phone,phone);
                finout.write((char*)&st, sizeof st);
            }
            else if (op[0] == '2')
            {
                char app[6];
                cin >> app;
                if (app[0] == 'b')
                {
                    cin >> no;
                    finout.seekg(0);
                    while (finout.read((char*)&st, sizeof st))
                    {
                        if (strcmp(no,st.no) == 0){
                            streampos place = ct * sizeof st;
                            cin >> date;
                            strcpy(st.date,date);
                            finout.seekp(place);
                            finout.write((char* )&st,sizeof st);
                            break;
                        }
                        ct++;
                    }
                }
                else
                {
                    cin >> no;
                    finout.seekg(0);
                    while (finout.read((char*)&st, sizeof st))
                    {
                        if (strcmp(no,st.no) == 0){
                            streampos place = ct * sizeof st;
                            cin >> phone;
                            strcpy(st.phone, phone);
                            finout.seekp(place);
                            finout.write((char* )&st, sizeof st);
                            break;
                        }
                        ct++;
                    }
                }
                
            }
            ct = 0;
            cin >> op;
            if (cin.eof()) break;
        }

        finout.close();
        return 0;
    }
};
void print(student& st)
{
    cout << st.no << " " << st.name << " " << st.date << " " << st.phone << endl;
}
int main()
{
    Solution a;
    a.main();
    fstream fout(a.file,ios_base::in|ios_base::out|ios_base::binary);
    fout.seekg(0);
    student st;
    while (fout.read((char *)&st, sizeof st))
    {
        print(st);
    }
    return 0;

}
