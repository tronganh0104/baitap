/*
Tên chương trình : XO game
Mục đích : tạo ra 1 trò chơi x o 3x3

Verson 1
1 AI engine
    + tạo ra một bàn cờ 3x3 ..
    + kiểm tra trò chơi kết thúc chưa ..
    + tạo ra tất cả trạng thái của bàn cờ ..
    + tính toán giá trị của từng trạng thái cờ ..
    + chọn ra nước đi hợp lí ..
    + kiểm tra ai là người thắng ..
    + kiểm tra người đi lượt hiện tại ..
2 User interface
    + in ra bàn cờ 3x3 ..
    + phản hồi nếu bước đi bị sai .
    + cho người chơi chọn nước đi .
    + in ra màn hình nước đi của máy .
    + in ra kết quả kết thúc .
*/

#include <iostream>
#include <vector>

typedef std::vector<std::vector<char> > state;

//in ra màn hình bàn cờ
//input : banco
//output : in ra màn hình
void printChess(state banco)
{
    std::cout << "-------------\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout <<"|";
        for (int j = 0; j < 3; j++)
        {
            std::cout << " " << banco[i][j] << " |";
        }
        std::cout << "\n";
        std::cout << "------------- \n";
    }
}

//kiểm tra xem thắng hay thua
//kiểm tra hàng
//input : banco
//output : trả về kết quả của hàng
bool checkHang(state banco)
{
    for (int i = 0; i < 3; i++)
    {
        if(banco[i][0] == banco[i][1] && banco[i][1] == banco[i][2] && banco[i][0] != '.') return true;
    }
    return false;
}

//kiểm tra cột
//input : banco
//output : trả về kết quả của cột
bool checkCot(state banco)
{
    for (int i = 0; i < 3; i++)
    {
        if(banco[0][i] == banco[1][i] && banco[1][i] == banco[2][i] && banco[0][i] != '.') return true;
    }
    return false;
}

//kiểm tra đường chéo
//input : banco
//output : trả về kết quả của cột
bool checkCheo(state banco)
{
    if (banco[0][0] == banco[1][1]  && banco[1][1] == banco[2][2] && banco[1][1] != '.') return true;
    if (banco[2][0] == banco[1][1] && banco[1][1] == banco[0][2] && banco[1][1] != '.') return true;
    return false;
}

//kiểm tra kết quả của cả bàn cờ
//input : banco
//output : trả về kết quả bàn cờ
bool checkBanco(state banco)
{
    if (checkHang(banco)) return true;
    if (checkCot(banco)) return true;
    if (checkCheo(banco)) return true;
    int d = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (banco[i][j] != '.') d++;
        }
    }
    if (d == 9) return true;
    return false;
}

//kiểm tra ai là người thắng
//input : banco
//output : trả về kết quả người thắng
char whoWin(state banco)
{
    for (int i = 0; i < 3; i++)
    {
        if(banco[i][0] == banco[i][1] && banco[i][1] == banco[i][2] && banco[i][0] != '.') return banco[i][0];
    }
    for (int i = 0; i < 3; i++)
    {
        if(banco[0][i] == banco[1][i] && banco[1][i] == banco[2][i] && banco[0][i] != '.') return banco[0][i];
    }
    if (banco[0][0] == banco[1][1] && banco[1][1] == banco[2][2] && banco[1][1] != '.') return banco[1][1];
    if (banco[2][0] == banco[1][1] && banco[1][1] == banco[0][2] && banco[1][1] != '.') return banco[1][1];
    return '.';
}

//tính điểm của trạng thái cờ
//input : banco
//output : trả về giá trị của trạng thái cờ
int scoreChess(state banco)
{
    if (whoWin(banco) == 'x') return 1;
    if (whoWin(banco) == 'o') return -1;
    return 0;
}

//kiểm tra lượt đi kế tiếp của ai
//input : banco
//output : trả về lượt đi hiện tại của bàn cờ
char luotDiHienTai(state banco)
{
    int x = 0; 
    int o = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (banco[i][j] == 'x') x++;
            if (banco[i][j] == 'o') o++;
        }
    }
    if (x == o) return 'x';
    else return 'o';
}

//tạo ra một bàn cờ copy
//input : banco
//output : banco copy
state copyChess(state banco)
{
    state copy (3, std::vector <char> (3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            copy[i][j] = banco[i][j];
        }
    }
    return copy;
}

//tạo ra tất cả trạng thái bàn cờ có thể xảy ra
//input : banco
//output : vector chứa tất cả trạng thái có thể xảy ra
std::vector <state> taoTrangThai(state banco)
{
    std::vector <state> trangthai;
    char nuocDi = luotDiHienTai(banco);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (banco[i][j] == '.')
            {
                state copy (3, std::vector <char> (3));
                copy = copyChess(banco);
                copy[i][j] = luotDiHienTai(banco);
                trangthai.push_back(copy);
            }
        }
    }
    return trangthai;
}

//tính điểm từng trạng thái
//input : một trạng thái của bàn cờ
//output : giá trị của trạng thái đó
int tinhdiem(state banco)
{
    if (checkBanco(banco))
    {
        if (whoWin(banco) == 'x') return 1;
        if (whoWin(banco) == 'o') return -1;
        if (whoWin(banco) == '.') return 0;
    }
    else
    {
        std::vector <state> trangthai(taoTrangThai(banco).size());
        
        trangthai = taoTrangThai(banco);
        int diemtrangthai[trangthai.size()];
        for (int i = 0; i < trangthai.size(); i++)
        {
            diemtrangthai[i] = 0;
        }
        for (int i = 0; i < trangthai.size(); i++)
        {
            
            diemtrangthai[i] = tinhdiem(trangthai[i]);
            
        }
        int m = 0;
        for (int i = 0; i < trangthai.size(); i++)
        {
            if (luotDiHienTai(banco) == 'x') if (diemtrangthai[m] < diemtrangthai[i]) m = i;
            if (luotDiHienTai(banco) == 'o') if (diemtrangthai[m] > diemtrangthai[i]) m = i;
        }
        return diemtrangthai[m];
    }
}

//tìm ra nước đi hợp lí
//input : banco
//output : sử dụng thuật toán minimax để đánh ra nước đi hợp lí
state comPlay(state banco)
{
    std::vector <state> trangthai(taoTrangThai(banco).size());
    int diemTungTrangThai[taoTrangThai(banco).size()];
    trangthai = taoTrangThai(banco);
    for (int i = 0; i < trangthai.size(); i++)
    {
        diemTungTrangThai[i] = tinhdiem(trangthai[i]);
    }
    int m = 0;
    for (int i = 0; i < trangthai.size(); i++)
    {
        if (diemTungTrangThai[i] >= diemTungTrangThai[m]) m = i;
    }
    return trangthai[m];
}

//cho người chơi chọn nước đi
//input : banco
//output : banco sau khi người chơi lựa chọn nước đi
void humanPlay(state &banco)
{
    
    
    int i,j;
    i = -1;
    j = -1;
    while (i < 0 || j < 0 || i > 2 || j > 2 || banco[i][j] != '.')
    {
        std::cout << "Your turn : ";
        std::cin >> i >> j;
        i--;
        j--;
        if (i < 0 || j < 0 || i > 2 || j > 2 || banco[i][j] != '.')
        std::cout << "No, it is invalid move. Again \n";
    }
    banco[i][j] = 'o';
}

//in ra kết quả khi game kết thúc
//input : banco
//output : x thắng, o thắng hoặc hòa
void endGame(state banco)
{
    char kq = whoWin(banco);
    if (kq == 'x') std::cout << "X win";
    if (kq == 'o') std::cout << "O win";
    if (kq == '.') std::cout << "Draw";
}


int main()
{
    state banco(3,std::vector <char> (3,'.'));
    banco[0][0] = '.'; banco[0][1] = '.'; banco[0][2] = '.';
    banco[1][0] = '.'; banco[1][1] = '.'; banco[1][2] = '.';
    banco[2][0] = '.'; banco[2][1] = '.'; banco[2][2] = '.';
    
    while (!checkBanco(banco))
    {
        std::cout << "My turn : \n";
        banco = comPlay(banco);
        printChess(banco);
        if (checkBanco(banco)) 
        {
            endGame(banco);
            break;
        }
        humanPlay(banco);
        
        if (checkBanco(banco)) 
        {
            printChess(banco);
            endGame(banco);
            break;
        }
    }
    return 0;
}