
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <iomanip>
using namespace std;

vector<string> instr;
vector<string> format;
vector<string> oam;
vector<string> taam;
vector<string> obj;

string mnemoniclib(string val)
{
    map<string, string> mnemonicmap;
    mnemonicmap.insert({"18", "ADD"});
    mnemonicmap.insert({"58", "ADDF"});
    mnemonicmap.insert({"90", "ADDR"}); // format2
    mnemonicmap.insert({"40", "AND"});
    mnemonicmap.insert({"b4", "CLEAR"}); // format2
    mnemonicmap.insert({"28", "COMP"});
    mnemonicmap.insert({"88", "COMPF"});
    mnemonicmap.insert({"a0", "COMPR"}); // format2
    mnemonicmap.insert({"24", "DIV"});
    mnemonicmap.insert({"64", "DIVF"});
    mnemonicmap.insert({"9c", "DIVR"}); // format2
    mnemonicmap.insert({"3c", "J"});
    mnemonicmap.insert({"30", "JEQ"});
    mnemonicmap.insert({"34", "JGT"});
    mnemonicmap.insert({"38", "JLT"});
    mnemonicmap.insert({"48", "JSUB"});
    mnemonicmap.insert({"00", "LDA"});
    mnemonicmap.insert({"68", "LDB"});
    mnemonicmap.insert({"50", "LDCH"});
    mnemonicmap.insert({"70", "LDF"});
    mnemonicmap.insert({"08", "LDL"});
    mnemonicmap.insert({"6c", "LDS"});
    mnemonicmap.insert({"74", "LDT"});
    mnemonicmap.insert({"04", "LDX"});
    mnemonicmap.insert({"d0", "LPS"});
    mnemonicmap.insert({"20", "MUL"});
    mnemonicmap.insert({"60", "MULF"});
    mnemonicmap.insert({"98", "MULR"}); // format2
    mnemonicmap.insert({"44", "OR"});
    mnemonicmap.insert({"d8", "RD"});
    mnemonicmap.insert({"ac", "RMO"}); // format2
    mnemonicmap.insert({"4c", "RSUB"});
    mnemonicmap.insert({"a4", "SHIFTL"}); // format2
    mnemonicmap.insert({"a8", "SHIFTR"}); // format2
    mnemonicmap.insert({"ec", "SSK"});
    mnemonicmap.insert({"0c", "STA"});
    mnemonicmap.insert({"78", "STB"});
    mnemonicmap.insert({"54", "STCH"});
    mnemonicmap.insert({"80", "STF"});
    mnemonicmap.insert({"d4", "STI"});
    mnemonicmap.insert({"14", "STL"});
    mnemonicmap.insert({"7c", "STS"});
    mnemonicmap.insert({"e8", "STSW"});
    mnemonicmap.insert({"84", "STT"});
    mnemonicmap.insert({"10", "STX"});
    mnemonicmap.insert({"1c", "SUB"});
    mnemonicmap.insert({"5c", "SUBF"});
    mnemonicmap.insert({"94", "SUBR"}); // format2
    mnemonicmap.insert({"b0", "SVC"});  // format2
    mnemonicmap.insert({"eO", "TD"});
    mnemonicmap.insert({"2c", "TIX"});
    mnemonicmap.insert({"b8", "TIXR"}); // format2
    mnemonicmap.insert({"dc", "WD"});

    auto it = mnemonicmap.find(val);
    return it->second;
}

string hextobin(string hexnum)
{
    int i = 0;
    while (hexnum[i])
    {

        switch (hexnum[i])
        {
        case '0':
            return "0000";
            break;
        case '1':
            return "0001";
            break;
        case '2':
            return "0010";
            break;
        case '3':
            return "0011";
            break;
        case '4':
            return "0100";
            break;
        case '5':
            return "0101";
            break;
        case '6':
            return "0110";
            break;
        case '7':
            return "0111";
            break;
        case '8':
            return "1000";
            break;
        case '9':
            return "1001";
            break;
        case 'A':
        case 'a':
            return "1010";
            break;
        case 'B':
        case 'b':
            return "1011";
            break;
        case 'C':
        case 'c':
            return "1100";
            break;
        case 'D':
            return "1101";
            break;
        case 'E':
            return "1110";
            break;
        case 'F':
            return "1111";
            break;
        }
        i++;
    }
    return 0;
}

string binaryToHex(int n)
{
    int num = n;
    int dec_value = 0;

    int base = 1;

    int temp = num;
    while (temp)
    {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }
    stringstream ss;
    ss << hex << dec_value;
    string result = ss.str();

    return result;
}

int stringToInt(string stringval)
{
    int stringtoint = 0;
    stringstream ss(stringval); // converts string to int
    ss >> stringtoint;
    return stringtoint;
}

bool isFormat2(string s)
{
    if (s == "90")
    {
        return true;
    }
    if (s == "b4")
    {
        return true;
    }
    if (s == "a0")
    {
        return true;
    }
    if (s == "9c")
    {
        return true;
    }
    if (s == "98")
    {
        return true;
    }
    if (s == "ac")
    {
        return true;
    }
    if (s == "a4")
    {
        return true;
    }
    if (s == "a8")
    {
        return true;
    }
    if (s == "94")
    {
        return true;
    }
    if (s == "b0")
    {
        return true;
    }
    if (s == "b8")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void dissasembler(vector<char> vect)
{
    instr.push_back("INSTR");
    format.push_back("FORMAT");
    oam.push_back("OAM");
    taam.push_back("TAAM");
    obj.push_back("OBJ");
    string targetaddress = "";
    string nixbpeval = "";

    string hex = "";
    for (int i = 9; i < vect.size() - 1; i += 6)
    {

        vector<char> format2binvect;
        for (int ja = i; ja < i + 4; ja++) // first goes through the process of checking for format 2
        {
            string hex = "";
            string binstring2 = "";
            hex = hex + vect.at(ja);    // creates a string of hex digits
            binstring2 = hextobin(hex); // creates a string of binary digits
            for (char k1 : binstring2)
            {
                format2binvect.push_back(k1);
            }
        }

        vector<char> format2opcode;
        for (int z = 0; z < 6; z++)
        {
            format2opcode.push_back(format2binvect.at(z));
        }

        string format2opcodestring(format2opcode.begin(), format2opcode.end());
        format2opcodestring.append("00"); // gets it into the right opcode format
        string format2opcodetohex = binaryToHex(stringToInt(format2opcodestring));
        if (format2opcodetohex.size() < 2)
        {
            format2opcodetohex = "0" + format2opcodetohex; // formats opcode correctly
        }

        if (isFormat2(format2opcodetohex) == true) // if opcode matches format 2 mnemonic key, outputs corresponding vals
        {

            string hexstring2 = "";
            for (int hs = i; hs < i + 4; hs++)
            {
                hexstring2 = hexstring2 + vect.at(hs); // creates a string of hex digits
            }
            format.push_back("2");

            instr.push_back(mnemoniclib(format2opcodetohex));
            oam.push_back(" ");
            taam.push_back(" ");
            obj.push_back(hexstring2);
            i -= 2;
        }
        else
        {

            vector<char> binvect;
            for (int j = i; j < i + 6; j++) 
            {
                string hexformat = "";
                string binstring = "";
                hexformat = hexformat + vect.at(j); // creates a string of hex digits
                binstring = hextobin(hexformat);    // creates a string of binary digits
                for (char k : binstring)
                {
                    binvect.push_back(k);
                }
            }
            vector<char> opcode; // sets up opcode for format 3/4
            for (int a = 0; a < 6; a++)
            {
                opcode.push_back(binvect.at(a));
            }
            while (binvect.size() < 24) // makes sure binary string is constant size by appending 0s to beginning
            {
                binvect.insert(binvect.begin(), '0');
            }

            string opcodestring(opcode.begin(), opcode.end());
            opcodestring.append("00"); // gets into proper format
            string opcodetohex = binaryToHex(stringToInt(opcodestring));
            if (opcodetohex.size() < 2)
            {
                opcodetohex = "0" + opcodetohex;
            }
            string hexformat = "";

            for (int hx = i; hx < i + 6; hx++)
            {
                hexformat = hexformat + vect.at(hx); // creates a string of hex digits
            }
            if (binvect.at(11) == '1') // checks if format 4
            {
                hexformat.push_back(vect.at(i + 6));
                hexformat.push_back(vect.at(i + 7));
                instr.push_back(mnemoniclib(opcodetohex));
                i += 2;
                format.push_back("4");
            }
            if (binvect.at(11) == '0') // checks if format 3
            {
                format.push_back("3");
                instr.push_back(mnemoniclib(opcodetohex));
            }
            obj.push_back(hexformat);
            if ((binvect.at(6) == '0') && (binvect.at(7) == '1') && (binvect.at(8) == '0')) // checks corresponding nixbpe instructions
            {
                oam.push_back("immediate");
            }
            if ((binvect.at(6) == '1') && (binvect.at(7) == '0') && (binvect.at(8) == '0'))
            {
                oam.push_back("indirect");
            }
            if ((binvect.at(6) == '1') && (binvect.at(7) == '1'))
            {
                oam.push_back("simple");
            }
            if ((binvect.at(6) == '0') && (binvect.at(7) == '0'))
            {
                oam.push_back("simple");
            }
            if ((binvect.at(9) == '1') && (binvect.at(10) == '0'))
            {
                if (binvect.at(8) == '1')
                {
                    taam.push_back("base_indexed");
                }
                else
                {
                    taam.push_back("base");
                }
            }

            if ((binvect.at(9) == '0') && (binvect.at(10) == '1'))
            {
                if (binvect.at(8) == '1')
                {
                    taam.push_back("pc_indexed");
                }
                else
                {
                    taam.push_back("pc");
                }
            }
            if ((binvect.at(9) == '0') && (binvect.at(10) == '0'))
            {
                taam.push_back("absolute");
            }
        }
    }
}

int main(int argc, char *argv[])
{
    fstream myfile(argv[1]);
    char element;
    vector<char> objectfile;
    if (myfile.is_open())
    {
        myfile.ignore(100, '\n'); // ignores the first line of the object file
        while (myfile >> element)
        {
            objectfile.push_back(element);
        }
    }
    myfile.close();
    vector<char> reformattedobjectfile; // reformats the object file so that it skips E000000 and modification statements
    for (int i = 0; i < objectfile.size() - 7; i++)
    {
        if (objectfile.at(i) == 'M')
        {
            break;
        }
        else
        {
            reformattedobjectfile.push_back(objectfile.at(i));
        }
    }
    dissasembler(reformattedobjectfile);

    ofstream outputfile;
    outputfile.open("obj_struct.txt");
    for (int i = 0; i < format.size(); i++)
    {
        outputfile << setw(20) << left << instr[i] << setw(20) << left << format[i]
                   << setw(20) << left << oam[i] << setw(20) << left << taam[i] << setw(20) << left << obj[i] << "\n";
    }
    outputfile.close();
    return 0;
}