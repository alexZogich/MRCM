#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


const unsigned int countOfBits = 32;
const long long unsigned int BASE = 4294967296;
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
    BigInt(unsigned int digit)
    {
        //if(digit >= 0){
            digits.push_back(digit);
            length = 1;
            sign = false;
        //}
        //else{
          //  digits.push_back(-1*digit);
           // length = 1;
           // sign = 1;
        //}
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
         while(this->digits[this->digits.size()-1] == 0 && this->digits.size() != 1)
        {
            this->digits.pop_back();
            this->length--;
        }
        /*
        for(int i = 0; i<digits.size(); i++)
            cout<<digits[i]<<endl;
            */
    }

    unsigned int getLenght();
    vector<unsigned int> getDigits();
    unsigned int getSign();

    void concVector(vector <unsigned int> value, unsigned int direction)// direction == 0 then vector+BigInt.digits
    {
        this->digits.reserve(this->digits.size() + value.size());
        this->length += value.size();
            if(direction == 0)
            {
                this->digits.insert(this->digits.end(), value.begin(), value.end());
            }
            else
            {
                this->digits.insert(this->digits.begin(), value.begin(), value.end());
            }
    }

    void setZero()//need tests
    {
        this->sign = false;
        this->length = 1;
        this->digits.push_back(0);
    }

    void setOne()//need tests
    {
        this->sign = false;
        this->length = 1;
        this->digits.push_back(1);
    }

    BigInt split(unsigned int spliter, unsigned int part)//need tests!!!
    {
        BigInt res;
        if(spliter > (this->length)){
            //cout<<"Split Error: spliter > length!!"<<endl;
            //res.setZero();
            //return res;
            return *this;
        }
        res.sign = this->sign;
        if(part == 0){
            res.digits.reserve(spliter);
            res.digits.insert(res.digits.end(),this->digits.begin(), this->digits.begin() + spliter);
        }
        else{
            res.digits.reserve(this->length - spliter);
            res.digits.insert(res.digits.end(),this->digits.begin() + spliter, this->digits.end());
        }
        res.length = res.digits.size();
        return res;
    }

    string toString();

    friend BigInt operator + (const BigInt &a, const BigInt &b);
    friend BigInt operator - (const BigInt &a, const BigInt &b);
    friend BigInt operator * (const BigInt &u, const BigInt &v);

    friend BigInt Pow(const BigInt &x, const BigInt &exp,const BigInt &m);
    friend BigInt modBarret(const BigInt &x, const BigInt &m,const BigInt &mu);//need tests
    friend BigInt findMu(const BigInt &mod);//need tests
    friend BigInt operator % (const BigInt &u, const BigInt &v);
    friend BigInt operator / (const BigInt &u, const BigInt &v);
    friend vector<BigInt> knutDivision(const BigInt &u, const BigInt &v);// first div,second mod
    friend BigInt Div(const BigInt &u, const BigInt &v);
    friend BigInt Mul(const BigInt &u, const BigInt &v);
    friend BigInt Mul(const BigInt &u, const unsigned int v);

    friend BigInt operator-(const BigInt& a);
    friend bool operator == (const BigInt &a, const BigInt &b);
    friend bool operator != (const BigInt &a, const BigInt &b);
    friend bool operator < (const BigInt &a, const BigInt &b);
    friend bool operator > (const BigInt &a, const BigInt &b);
    friend bool operator >= (const BigInt &a, const BigInt &b);
    friend bool operator <= (const BigInt &a, const BigInt &b);
    friend ostream& operator << (ostream &out, BigInt &b);
    friend BigInt concBigInt(const BigInt& hi, const BigInt& lo);

};
vector<unsigned int> BBS(const BigInt &seed,const BigInt &p,const BigInt &q, unsigned int count);

//    Tests
void testFerma();
void testFindMu();
void testXEXPModM();
void testModRed();
void testSpecialNumber();
void testOdnoRozryadResult();
void testDivToOneRozryad(); // test div to one rozryad
void testDivRevToMult();
void testDiv(); // test for div
void testSimpleMulHexAndInt(); // mul BigInt and Int
void testKarazuba512(); // test for length >512bit
void testKarazuba(); // karazuba :)
void testSimpleMul();   // C = Mul(A,B)
void testBigIntConstruct(); //BigInt( bigint : &BigInt ) // a = b
void testUnarySub();		//unary "-"
void testIntConstruct(); //BigInt( digit : int )
void testMoreAndEq();	//	operation ">="
void testLessAndEq();	//	operation "<="
void testMore();		// operation ">"
void testLess();		// operation "<"
void testNotEqual(); // operation "!="
void testEqual();   // operation "=="
void testSum();     // operation "+"
void testSub();     // operation "-"

#endif // HEADER_H

/*
    Questions:
    1.What operators does we need a friend  or implicit?
    2.what kind of operators for each operator we must to declarate?
    3.If we need to use implicit, will we use a one-operand operators?
    http://stackoverflow.com/questions/11229074/overloading-operator-complaining-of-must-take-exactly-one-argument
    c++ operator != must take exactly one argument


*/
