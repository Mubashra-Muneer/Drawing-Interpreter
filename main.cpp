#include"help.h"
#include<iostream>
#include<conio.h>//for full screen
#include<cmath>//for sin and cos
#include<windows.h>//for help.h and for full screen
#include<fstream>//file handling
using namespace std;
//function prototype to avoid function call errors
void GetAllHisory();
void Draw(char array2[], int val, char og[] , bool flag );
void ResetDefault();
int cwidth ;//currentwidth
char history[100][100];
int pindex;//current command index
int commandindex ;//history index
int currentvalue;//value given by user
bool LineorCircle;  //if true then draw line and if false draw circle
int nx1 , ny1 , cx1 ,cy1 ;//cx1, cy1 are first coordinates and nx1, ny1 second coordinates
int cangle = 90;//current angle
int prevangle =90;//previous angle
bool cpen;//pen status
int color = 6;// 0 for black, 1 for red, 2 for green, 3 for blue else white

bool GetCommand(char input[], int& value) { //input validation
    char array[20][20] = {
        {"fd\0"},{"forward\0"},{"bk\0"},{"backward\0"},{"rt\0"},{"lt\0"},{"repeat\0"},{"pu\0"},{"pd\0"},{"color\0"},{"width\0"},{"cs\0"},{"circle\0"},{"save\0"},{"load\0"}
    };
    if (input[0] == 'c' && input[1] == 's') {
        return true;
    }
    else if (input[0] == 'p' && input[1] == 'u') {
        return true;
    }
    else if (input[0] == 'p' && input[1] == 'd') {
        return true;
    }
    else if (input[0] == 's' && input[1] == 'a' && input[2] == 'v' && input[3] == 'e') {
        return true;
    }
    else if (input[0] == 'l' && input[1] == 'o' && input[2] == 'a' && input[3] == 'd') {
        return true;
    }
    for (int i = 0; i < 15; i++) {
        if (strncmp(input, array[i], strlen(array[i])) == 0) {
            value = 0;
            int numericIndex = strlen(array[i]);
            int num = 0;
            for (int j = i; input[j] != '\0' && input[j] != '['; j++) {
                if (input[j] >= 48 && input[j] <= 57)//ascii conversion to integer
                {
                    num = input[j] - 48;
                    value = value * 10;
                    value = value + num;
                }
            }
            if (numericIndex != strlen(input)) {
                return true;
            }
                return false;
        }
    }

    return false;
}

void RotateArrowhead(int x1, int y1, int x2, int y2, int x3, int y3, int anglee,int color )
{
    double angle = (90 + anglee) * (3.141 / 180); // 90 degrees in radians
    int px = (x1 + x2 + x3) / 3;
    int py = (y1 + y2 + y3) / 3;
    int x1_rotated = (px + (x1 - px) * cos(angle) - (y1 - py) * sin(angle));
    int y1_rotated = (py + (x1 - px) * sin(angle) + (y1 - py) * cos(angle));
    int x2_rotated = (px + (x2 - px) * cos(angle) - (y2 - py) * sin(angle));
    int y2_rotated = (py + (x2 - px) * sin(angle) + (y2 - py) * cos(angle));
    int x3_rotated = (px + (x3 - px) * cos(angle) - (y3 - py) * sin(angle));
    int y3_rotated = (py + (x3 - px) * sin(angle) + (y3 - py) * cos(angle));
    myLine3(x2_rotated, y2_rotated, x3_rotated, y3_rotated, color, 3);
    myLine3(x3_rotated, y3_rotated, x1_rotated, y1_rotated, color, 3);
}
void drawArrowhead(int x1, int y1, int angle) {
    x1 = x1 - 3;
    int x2 = x1 + 7;
    int x3 = (x1 + x2) / 2;
    int y3 = y1 + 10;
    RotateArrowhead(x1, y1, x2, y1, x3 , y3, angle, 4);
}
void drawArrowheadBlack(int x1, int y1, int angle) {
    x1 = x1 - 3;
    int x2 = x1 + 7;
    int x3 = (x1 + x2) / 2;
    int y3 = y1 + 10;
    RotateArrowhead(x1, y1, x2, y1, x3 , y3, angle,0);
}
void extractCommand(char source[], char destination[]) {
    int j = 0;
    int size = strlen(source);
    for (int i = 0; i < size; ++i) {
        if ((source[i] >= 'A' && source[i] <= 'Z') || (source[i] >= 'a' && source[i] <= 'z')) {
            destination[j++] = source[i];
        }
    }
    destination[j] = '\0';
}
int extractValue(char command[20] ) {
    int i = 0;
    for (i = 0; (command[i] >= 'A' && command[i] <= 'Z') || (command[i] >= 'a' && command[i] <= 'z') || (command[i] == ' '); i++);

    int num = 0, val = 0;
    for (int j = i; command[j] != '\0' && command[j] != '['; j++) {
        if (command[j] >= 48 && command[j] <= 57) {
            num = command[j] - 48;
            val = val * 10;
            val = val + num;
        }
    }
    return val;
}
void inRepeat(char input[]) {
    char delimiter = ' ';
    char currentPair[20];  // Adjust the size as needed
    int length = strlen(input);
    char text[10];
    char valu[10];
    int a = 0;
    for (int i = 0; i < length; ++i) {//at odd iterations retrieving commands and at even iterations retrieving value and calling draw function to execute command
        int j = 0;
        while (input[i] != ' ' && input[i] != '\0') {
            currentPair[j++] = input[i++];
        }
        currentPair[j] = '\0';
        if (j > 0) {
            a++;
            if (a % 2 == 1)
                strcpy_s(text, currentPair);
            else if (a % 2 == 0)
            {
                strcpy_s(valu, currentPair);
                int num = 0, val = 0;
                for (int j = 0; valu[j] != '\0' ; j++) {
                    if (valu[j] >= 48 && valu[j] <= 57) {
                        num = valu[j] - 48;
                        val = val * 10;
                        val = val + num;
                    }
                }
                char arr[10];
                Draw(text, val,arr,0);
            }

        }
    }
}
void moveInDirection(int& x, int& y, int angle, int magnitude) {
    double radianAngle = angle * 3.142 / 180.0;
    x -= magnitude * cos(radianAngle);
    y -= magnitude * sin(radianAngle);
}
void circle(int cx, int cy, int radius, int color, int width) {
    int x1 = cx - radius;
    int y1 = cy - radius;
    int x2 = cx + radius;
    int y2 = cy + radius;
    myEllipse(x1, y1, x2, y2,color, width);
}
//repeat 4[fd 10 rt 90]
void Draw(char array2[], int val, char og[] , bool flag ) {//flag 1 to store command in history and 0 to doesn't store

    if(flag == 1)
    {
        strcpy_s(history[commandindex], og);
        commandindex++;
    }
    if (strcmp(array2, "fd\0") == 0 || strcmp(array2, "forward\0") == 0) {
        nx1 = cx1;//updating coordinates
        ny1 = cy1;
        moveInDirection(nx1, ny1, cangle, val);
    }
    else if (strcmp(array2, "bk\0") == 0 || strcmp(array2, "backward\0") == 0) {
        nx1 = cx1;;//updating coordinates
        ny1 = cy1;
        moveInDirection(nx1, ny1, cangle-180, val);
    }
    else if (strcmp(array2, "rt\0") == 0) {
        cangle = cangle + val;
    }
    else if (strcmp(array2, "lt\0") == 0) {
        cangle = cangle - val;
    }
    else if (strcmp(array2, "pu\0") == 0) {
        cpen = 0;
    }
    else if (strcmp(array2, "pd\0") == 0) {
        cpen = 1;
    }
    else if (strcmp(array2, "width\0") == 0) {
        cwidth = val;
    }
    else if (strcmp(array2, "color\0") == 0) {
        color = val ;
    }
    else if (strcmp(array2, "circle\0") == 0) {
        LineorCircle = 0;//1 for line and 0 for circle

    }
    else if (array2[0] == 'r' && array2[1] == 'e' && array2[2] == 'p' && array2[3] == 'e' && array2[4] == 'a' && array2[5] == 't') {
        int i, j;
        char incommands[100];//repeat 4[fd 10 rt 90]
        for (i = 0; og[i] != '['; i++) {
        }
        i++;
        for (j = i; og[j] != ']'; j++) {
            incommands[j - i] = og[j];
        }
        incommands[j - i] = '\0';
        for (int k = 0; k < val; k++) {
            inRepeat(incommands);
        }
    }
    else if (strcmp(array2, "cs\0") == 0) {
        //system("cls");
        myRectangle(0, 0, 1500, 800, 0, 100, 0);
        ResetDefault();
    }
    else if (array2[0] == 's' && array2[1] == 'a' && array2[2] == 'v' && array2[3] == 'e') {
        int i, j;
        char filing[100];
        for (i = 0; og[i] != '\"'; i++) {
        }
        i++;
        for (j = i; og[j] != '\"'; j++) {
            filing[j - i] = og[j];
        }
        filing[j - i] = '\0';
        //cout << filing;
        ofstream fout(filing);
        for (int k = 0; k < commandindex - 1; k++) 
        {
            fout << history[k] << endl;
        }
    }
    else if (array2[0] == 'l' && array2[1] == 'o' && array2[2] == 'a' && array2[3] == 'd') {
        int i, j;
        int k = 0;
        char filing[100];
        for (i = 0; og[i] != '\"'; i++) {
        }
        i++;
        for (j = i; og[j] != '\"'; j++) {
            filing[j - i] = og[j];
        }
        filing[j - i] = '\0';
        //cout << filing;
        ifstream fin(filing);
        while (fin.eof() != 1) {
            fin.getline(history[k],100);
            k++;
        }
        commandindex = k;
        GetAllHisory();
    }
    else {
        strcpy_s(history[commandindex-1], "Command does not exist");
    }
    pindex++;
    
    drawArrowheadBlack(cx1, cy1, prevangle);
    if (cpen == 1) {

        if (LineorCircle == 1) {
            myLine3(cx1, cy1, nx1, ny1, color, cwidth);
        }
        else {
            circle(cx1, cy1,val,color,cwidth);
            //cout<<val<<endl;
        }
    }
    if (LineorCircle == 0) {
        LineorCircle = 1;
    }
    drawArrowhead(nx1, ny1, cangle);
    cx1 = nx1;
    cy1 = ny1;
    prevangle = cangle ;
}
void GetAllHisory() {
    char command[100];
    for (int i = 0; i < commandindex; i++) {
        char array2[200];
        strcpy_s(command, history[i]);
        extractCommand(command, array2);
        int value = extractValue(command);
        Draw(array2, value, command,1);
    }
}
void printhistory() {
    int j = 0;
    for (int i = 0; i < 9; i++) {
        cout << "\x1b[1A" << "\x1b[2K";
    }
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "_________________________"<<endl;
    for (int i = commandindex; i >= commandindex - 5; i--) {
        if (i==0) {
            break;
        }
        j++;
        cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|  ";
        cout << history[i] << endl;
    }
    for (int k = j; k < 7; k++) {
        cout << endl;
    }
}
void ResetDefault()
{
    cpen = 1;
    color = 4;
    LineorCircle = 1;
    currentvalue = 0;
    commandindex = 1 ;
    nx1 = 600;
    ny1 = 390;
    cx1 = 600;
    cy1 = 390;
    cangle = 90;
    pindex = 0;
    cwidth = 2;
    cpen = 1;
    color - 4 ;
    LineorCircle = 1;
    currentvalue = 0;

}
void FullScreen()//from stackoverflow
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;
    int Status = SetConsoleScreenBufferSize(hOut, newSize);
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    system("cls");
    for (int i = 0; i < 45; i++) {
        cout << endl;
    }

}
int main()
{
    FullScreen();
    ResetDefault();
    char command[200];
    do{
        printhistory();
        cout << "__________________________________________________________________________________________________________________________________________________________________________" << endl;
        cin.getline(command, 200);
        cout << "\x1b[1A" << "\x1b[2K";//from stackoverflow to move 1 line up
        char array2[18];
        extractCommand(command, array2);
        int value;

        if (GetCommand(command,  value)) {
            value = extractValue(command);
            Draw(array2, value, command,1);
        }
        else {
            if (value==0) {
                strcpy_s(history[commandindex], "incomplete command");
            }
            else 
            {
                    commandindex--;

            }
            commandindex++;
        }

    }while(command[0] != 'e' );
    return 0;

}
