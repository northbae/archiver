/*#include "AC.h"

bool AC::comp(unsigned int k1, unsigned int k2)
{
    if (k1 > k2)
        return 1;
    return 0;
}
bool AC::encode(const shared_ptr<vector<char>>& inpVect, const string& path)
{
  
    ofstream codedtext(path, ios::binary);
    if (codedtext.is_open() == 0)
    {
        cout << "can't open codedway";
        return 0;
    }
    map<char, int> table;
    map<char, int>::iterator it;
    char s;

    for (int i = 0; i < inpVect->size(); ++i)
		{
			table[inpVect->at(i)]++;
    

    list<Interval> List;
    list<Interval>::iterator iter;
    for (it = table.begin(); it != table.end(); it++)
    {
        Interval i;
        i.sym = it->first;
        i.key = it->second;
        List.push_back(i);
    }
    int board = 0;
    List.sort(comp);
    for (iter = List.begin(); iter != List.end(); iter++)
    {
        iter->left = board;
        iter->right = board + iter->key;
        board = iter->right;
    }
    int size = table.size();
    codedtext.write((char *)&size, sizeof(size));
    for (it = table.begin(); it != table.end(); it++)
    {
        codedtext.write((char *)&it->first, sizeof(it->first));
        codedtext.write((char *)&it->second, sizeof(it->second));
    } // записали шапку
    unsigned short l = 0;
    unsigned short h = 65535;
    int delitel = List.back().right;
    unsigned short First_qtr = (h + 1) / 4;   //16384
    unsigned short Half = First_qtr * 2;      //32768
    unsigned short Third_qtr = First_qtr * 3; //49152
    int bits_to_follow = 0;                   // сколько битов сбрасывать
    int count = 0;
    char tmp = 0;

    while (!text.eof())
    {
        int s = text.get();
        for (iter = List.begin(); ((iter->sym != s) && (iter != List.end())); iter++)
        {
        }
        int range = h - l + 1;
        h = l + iter->right * range / delitel - 1;
        l = l + iter->left * range / delitel;
        while (true)
        {
            if (h < Half)
            {
                count++;
                if (count == 8)
                {
                    codedtext.put(tmp);
                    tmp = 0;
                    count = 0;
                }
                for (; bits_to_follow > 0; bits_to_follow--)
                {
                    tmp = tmp | (1 << (7 - count));
                    count++;
                    if (count == 8)
                    {
                        codedtext.put(tmp);
                        tmp = 0;
                        count = 0;
                    }
                }
            }
            else if (l >= Half)
            {
                tmp = tmp | (1 << (7 - count));
                count++;
                if (count == 8)
                {
                    codedtext.put(tmp);
                    tmp = 0;
                    count = 0;
                }
                for (; bits_to_follow > 0; bits_to_follow--)
                {
                    count++;
                    if (count == 8)
                    {
                        codedtext.put(tmp);
                        tmp = 0;
                        count = 0;
                    }
                }
                h -= Half;
                l -= Half;
            }
            else if ((l >= First_qtr) && (h < Third_qtr))
            {
                bits_to_follow++;
                h -= First_qtr;
                l -= First_qtr;
            }
            else
                break;
            h += h + 1;
            l += l;
        }
    }
    text.close();
    codedtext.close();

    return 1;
}

bool ar_decode(char *codedway, char *decodedway)
{
    ifstream coded(codedway, ios::binary);
    if (coded.is_open() == 0)
    {
        cout << "can't open codedway";
        return 0;
    }

    ofstream decoded(decodedway, ios::binary);
    if (decoded.is_open() == 0)
    {
        cout << "can't open decodedway";
        return 0;
    }
    unsigned long length;
    int sym_freq;
    int n;
    char s;
    map<char, int> table;
    map<char, int>::iterator it;
    coded.read((char *)&n, sizeof(n));
    for (int i = 0; i < n; i++)
    {
        coded.read((char *)&s, sizeof(s));
        coded.read((char *)&sym_freq, sizeof(sym_freq));
        table[s] = sym_freq;
        length = length + sym_freq;
    }
    for (it = table.begin(); it != table.end(); it++)
    {
        cout << "sym :" << it->first << " freq = " << it->second << endl;
    }
    list<interval> List;
    list<interval>::iterator iter;
    for (it = table.begin(); it != table.end(); it++)
    {
        interval i;
        i.sym = it->first;
        i.key = it->second;
        List.push_back(i);
    }
    int board = 0;
    List.sort(comp);
    for (iter = List.begin(); iter != List.end(); iter++)
    {
        iter->left = board;
        iter->right = board + iter->key;
        board = iter->right;
    }

    unsigned short l = 0;
    unsigned short h = 65535;
    int delitel = List.back().right;
    cout << "delitel= " << delitel << endl;
    cout << "length= " << length << endl;
    cout << "mod%delitel= " << length % delitel << endl;
    unsigned short First_qtr = (h + 1) / 4;   //16384
    unsigned short Half = First_qtr * 2;      //32768
    unsigned short Third_qtr = First_qtr * 3; //49152
    int value = (coded.get() << 8) | coded.get();
    int tmp = coded.get();
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        int range = h - l + 1;
        unsigned int freq = (((value - l + 1) * delitel) - 1) / range;
        for (iter = List.begin(); ((iter->right <= freq)); iter++)
        {
        }
        h = l + iter->right * range / delitel - 1;
        l = l + iter->left * range / delitel;
        while (true)
        {
            if (h < Half)
                ;
            else if (l >= Half)
            {
                value -= Half;
                l -= Half;
                h -= Half;
            }
            else if ((l >= First_qtr) && (h < Third_qtr))
            {
                value -= First_qtr;
                l -= First_qtr;
                h -= First_qtr;
            }
            else
                break;

            h += h + 1;
            l += l;
            value += value;
            value += ((tmp & (1 << (7 - count))) >> (7 - count));
            count++;
            if (count == 8)
            {
                tmp = coded.get();
                count = 0;
            }
        }
        decoded << iter->sym;
    }

    coded.close();
    decoded.close();
    return 1;
}
bool File_compare(char *textway, char *decoded_textway)
{
    ifstream text(textway, ios::out | ios::binary);
    if (text.is_open() == 0)
    {
        cout << "can't open textway" << endl;
        return 0;
    }
    ifstream decoded_text(decoded_textway, ios::out | ios::binary);
    if (decoded_text.is_open() == 0)
    {
        cout << "can't open decoded_textway" << endl;
        return 0;
    }
    char s, sym;
    while ((!text.eof()) && (!decoded_text.eof()))
    {
        s = text.get();
        sym = decoded_text.get();
        if (s != sym)
        {
            text.close();
            decoded_text.close();
            return 0;
        }
    }
    text.close();
    decoded_text.close();
    return 1;
}
int main()
{
    char textway[] = "C:\\Users\\12\\Desktop\\c_labs\\haffman\\Long_text.txt";
    char codedway[] = "C:\\Users\\12\\Desktop\\c_labs\\haffman\\coded_text.txt";
    char decodedway[] = "C:\\Users\\12\\Desktop\\c_labs\\haffman\\decoded_text.txt";
    bool k = ar_code(textway, codedway);
    bool m = ar_decode(codedway, decodedway);
    bool res = File_compare(textway, decodedway);
    if (res == 1)
        cout << "Files equal" << endl;
    ifstream text(textway, ios::binary);
    if (text.is_open() == 0)
    {
        cout << "can't open codedway";
        return 0;
    }
    ifstream coded(codedway, ios::binary);
    if (coded.is_open() == 0)
    {
        cout << "can't open codedway";
        return 0;
    }
    float ntx = 0;
    float ncode = 0;
    char tmp;
    while (!text.eof())
    {
        tmp = text.get();
        ntx++;
    }
    while (!coded.eof())
    {
        tmp = coded.get();
        ncode++;
    }
    float compress = ncode / ntx;
    cout << "compression = " << compress << endl;
    text.close();
    coded.close();
    return 0;
}*/