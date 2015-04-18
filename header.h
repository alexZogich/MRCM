#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


const unsigned int countOfBits = 32;
const char chHex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


//unsigned int getSizeToConvert(unsigned int hexSize);
//vector <unsigned int> stringToVectorHex(string hex);
string clearZerosInFirstPos(string hexString);
bool inputRule(char chHex);
bool inputTest(string val);


class BigInt
{
    vector <unsigned int> digits;
    unsigned int length;
    bool sign; //false for positive, true for negative. 0 is positive

public:
    BigInt()
    {
        // Внесены изменения при реализации оператора "-" старые значения
        //digits.push_back(0);
        //length = 1
        length = 0;
        sign = false;
    }
    BigInt(int digit)
    {
        if(digit >= 0){
            digits.push_back(digit);
            length = 1;
            sign = 0;
        }
        else{
            digits.push_back(-1*digit);
            length = 1;
            sign = 1;
        }
    }
    BigInt(const BigInt &a)
    {
        this->digits = a.digits;
        this->length = a.length;
        this->sign = a.sign;
    }

    /*
     *  test carefully, need a lot of tests
    */
    BigInt(string val)
    {
        inputTest(val);
        string hexString;
        char chHex[9];
        unsigned int rest = 0, countOfZero = 0, number = 0;
        if(val[0] == '-'){
            this->sign = true;
            val = val.substr(1,val.size());
        }
        else
            this->sign = false;
        rest = val.size() & 7;
        if(rest != 0)
            countOfZero = 8 - rest;

        reverse(val.begin(), val.end());
        for(int i = 0; i < countOfZero; i++)
            val.push_back('0');
        //cout<<"val :"<<val<<" "<<val.size()<<endl;
        //cout<<"val : "<<(val.size()>>3)<<endl;

        for(int i = 0; i < (val.size() >> 3);i++)
        {
            hexString = val.substr(8*i,8);
            /*cout<<"val.substr: "<<val.substr(8,16)<<endl;
            cout<<"8*i "<<8*i<<" ";
            cout<<"8*(i+1) "<<8*(i+1)<<" ";
            cout<<"val.substr: "<<val.substr(8*i,(8*(i+1)))<<endl;*/
            reverse(hexString.begin(), hexString.end());
            //cout<<"hexString:"<<hexString<<endl;
            for(int j = 0; j < 8; j++){
                chHex[j] = hexString[j];
                //cout<<chHex[j];
            }
            /*
            cout<<endl;
            for(int i = 0; i < 10; i++)
                cout<<endl<<chHex[i]<<endl;
            cout<<"strtoul(chHex, NULL, 16) "<<strtoul(chHex, NULL, 16)<<endl;
            */
            digits.push_back(strtoul(chHex, NULL, 16));
        }
        this->length = digits.size();
        /*
        for(int i = 0; i<digits.size(); i++)
            cout<<digits[i]<<endl;
            */
    }

    unsigned int getLenght();
    vector<unsigned int> getDigits();
    unsigned int getSign();


    string toString();

    friend BigInt operator + (const BigInt &a, const BigInt &b);
    friend BigInt operator - (const BigInt &a, const BigInt &b); //not implement

    friend BigInt operator-(const BigInt& a);
    friend bool operator == (const BigInt &a, const BigInt &b);
    friend bool operator != (const BigInt &a, const BigInt &b);
    friend bool operator < (const BigInt &a, const BigInt &b);
    friend bool operator > (const BigInt &a, const BigInt &b);
    friend bool operator >= (const BigInt &a, const BigInt &b);
    friend bool operator <= (const BigInt &a, const BigInt &b);
    friend ostream& operator << (ostream &out, BigInt &b);
};



void testBigIntConstruct(); //BigInt( bigint : &BigInt ) // a = b
void testUnarySub();		//unary "-"
void testIntConstruct(); //BigInt( digit : int )
void testMoreAndEq();		//operation ">="
void testLessAndEq();		//operation "<="
void testMore();		//operation ">"
void testLess();		//operation "<"
void testNotEqual(); //operation "!="
void testEqual();   //operation "=="
void testSum();     //operation "+"
void testSub();     //operation "-"

#endif // HEADER_H

/*
    Questions:
    1.What operators does we need a friend  or implicit?
    2.what kind of operators for each operator we must to declarate?
    3.If we need to use implicit, will we use a one-operand operators?
    http://stackoverflow.com/questions/11229074/overloading-operator-complaining-of-must-take-exactly-one-argument
    c++ operator != must take exactly one argument


*/
