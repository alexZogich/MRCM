#include <header.h>


unsigned int BigInt::getLenght()
{
    return this->length;
}

vector<unsigned int> BigInt::getDigits()
{
    return this->digits;
}

unsigned int BigInt::getSign()
{
    return this->sign;
}

BigInt operator + (const BigInt &a, const BigInt &b)
{
    BigInt res, left = a, right = b;
    unsigned int rest = 0;
    long long unsigned int localRes = 0;
    if(a.sign == b.sign)
    {
        //**** Приведение к одной длине чисел
        unsigned int size = max(a.length,b.length);
        //не добавлено один элемент
        for(int i = 0; i < (size - res.length); i++)
            res.digits.push_back(0);
        res.length = size;
        if(a.length != size){
            for(int i = 0; i < (size - a.length); i++)
                left.digits.push_back(0);
            left.length = size;
        }
        else{
            for(int i = 0; i < (size - b.length); i++)
                right.digits.push_back(0);
            right.length = size;
        }
        for(int i = 0; i < size; i++){
            res.digits[i] = localRes = (long long unsigned int)left.digits[i] + right.digits[i] + rest;
            rest = (localRes >> countOfBits);
        }
        if(rest != 0){
            res.length = res.length + 1;
            res.digits.push_back(1);
        }
        //res.length = res.digits.size();
        res.sign = a.sign;
    }
    else
    {
        if(b.sign == true){
            res = left - (-right);
        }
        else{
            res = right - (-left);
        }
    }
    return res;
}

BigInt operator - (const BigInt &a, const BigInt &b)
{
    BigInt res, left = a, right = b,tempBigInt;
    //Решение проблемы разных знаков (-а)-(b)=>(-a) + (-b) и (a)-(-b)=>a + b
    if((a.sign == false && b.sign == true)||(a.sign == true && b.sign == false)){
        res = left + (-right);
        return res;
    }
    unsigned int size = max(a.length,b.length);
    left.sign = right.sign = false;
    if(left < right){
        tempBigInt = left;
        left = right;
        right = tempBigInt;
    }
    for(int i = 0; i < size - right.length; i++)
        right.digits.push_back(0);
    unsigned int rest = 0, counter = 0, mask = 0xFFFFFFFF;
    long long int temp = 0;
    for(int i = 0; i < left.length; i++)
    {
        temp = (long long int)left.digits[i] - right.digits[i] - rest;
        res.digits.push_back(temp);
        if(temp < 0)
            rest = 1;
        else
            rest = 0;
        if(temp != 0)
            counter = i;
    }
    for(int i = 0; i < (size - 1) - counter; i++)
        res.digits.pop_back();
    res.length = res.digits.size();
    if(a >= b)
        res.sign = false;
    else
        res.sign = true;
    return res;
    //Одинаковые знаки
//    unsigned int size = max(a.length,b.length);
//    bool bothSign = a.sign;
//    unsigned int flag = 0;
//    if(a >= b){
//        flag = 0;
//        res.sign = false;//?
//    }
//    else{
//        flag = 1;
//        res.sign = true;//?
//    }

    //Делаем вычитание от большего по модулю меньшее по модулю
//    if(bothSign == false && flag == 0) //|| (bothSign == true && flag == 1)){
//    {
//        left = a;
//        right = b;
//    }
    //+++++++++++
//    if(bothSign == true && flag == 1){
//        left = a;
//        right = b;
//    }
    //?+
//    if((bothSign == false && flag == 1) || (bothSign == true && flag == 0)){
//        left = b;
//        right = a;
//    }
    /*if(bothSign == true)
        left.sign = right.sign = false;*/

//    for(int i = 0; i < size - right.length; i++)
//        right.digits.push_back(0);

//    unsigned int rest = 0, counter = 0, mask = 0xFFFFFFFF;
//    long long int temp = 0;
//    for(int i = 0; i < left.length; i++)
//    {
//        temp = (long long int)left.digits[i] - right.digits[i] - rest;
//        res.digits.push_back(temp);
//        if(temp < 0)
//            rest = 1;
//        /*rest = temp >> 63;
//        if(rest == 1)
//            res.digits.push_back((temp^mask));
//        else
//           res.digits.push_back(temp);*/
//        if(temp != 0)
//            counter = i;
//    }
    // Обрезание
    //res.length = counter + 1;
//    for(int i = 0; i < (size - 1) - counter; i++)
//        res.digits.pop_back();
//    res.length = res.digits.size();
//    return res;
}

BigInt operator-(const BigInt& a)
{
    BigInt b = a;
    if(b.length == 1 && b.digits[0] == 0)
        return b;
    if(b.sign == false)
        b.sign = true;
    else
        b.sign = false;
    return b;
}

bool operator>=(const BigInt &a, const BigInt &b)
{
    if(a < b)
        return false;
    else
        return true;
}

bool operator <= (const BigInt &a, const BigInt &b)
{
    if(a > b)
        return false;
    else
        return true;

}

bool operator<(const BigInt &a, const BigInt &b) //for positiv
{
    if(a.sign == true && b.sign == false)
        return true;
    if(a.sign == false && b.sign == true)
        return false;
    BigInt c,d;

    bool sign = false;

    if(a.sign == true && b.sign == true){
        c = -a;
        d = -b;
        sign = true;
    }
    if(a.sign == false && b.sign == false){
        c = a;
        d = b;
    }
    if(c.length < d.length){
        if(sign == false)
            return true;
        else
            return false;
    }
    if(c.length > d.length){
        if(sign == false)
            return false;
        else
            return true;
    }

    for(int i = 0; i < c.length; i++)
    {
        if(c.digits[(c.length-1)- i] > d.digits[(d.length-1) - i])
            return false ^ sign;
        if(c.digits[(c.length-1)- i] < d.digits[(d.length-1) - i])
            return true ^ sign;
    }
    return false ^ sign;
}

bool operator == (const BigInt &a, const BigInt &b)
{
    if((a.length != b.length) || (a.sign != b.sign))
        return false;
    else
        for(int i = 0; i < a.length; i++)
            if(a.digits[i] != b.digits[i])
                return false;
    return true;
}

bool operator!=(const BigInt &a, const BigInt &b)
{
    if(a == b)
        return false;
    else
        return true;
}

bool operator > (const BigInt &a, const BigInt &b)
{
    if((a >= b) && (a != b))
        return true;
    else
        return false;
}

ostream& operator<<(ostream &out, BigInt &b)
{
    string convertBigInt = b.toString();
    out << convertBigInt;
    return out;

}

string BigInt::toString()
{
    string hexString;
    unsigned int mask = 0xF,intHexDigit = 0;
    for(int i = 0; i < this->length; i++){
        for(int j = 0; j < 8; j++){
            intHexDigit = ((this->digits[i] >> 4*j) & mask);
            hexString.push_back( chHex[intHexDigit]);
            intHexDigit = 0;
        }
    }
    //cout<<"hexString "<<hexString<<endl;
    reverse(hexString.begin(), hexString.end());

    hexString = clearZerosInFirstPos(hexString);
    //cout<<"hexString "<<hexString<<endl;

    if(this->sign == true)
        hexString  = hexString.insert(0,1,'-');
/*
    stringstream ss;
    string hexString;
    if(this->sign == true)
        hexString = "-";
    for(int i = 0; i < (this->length); i++)
    {
        ss << std::hex << digits[i] ;
        //hexString = std::to_string(ss);
       //hexString += intToString();
    }
*/
    return hexString;
}


bool inputTest(string val)
{
    if(val == "-0"){
        cout<<"Input Error: "+ val<<endl;
        return false;
    }
    if((val.size() == 1) && (val[0] == '-')){
        cout<<"Input Error: "+ val<<endl;
        return false;
    }
    /*if(((47 < val[0])&&(val[0] < 58))||((64 < val[0])&&(val[0] < 71))||(96 < val[0])&&(val[0] < 103)||(val[0] == 45)){
        for(int i = 1; i < val.size(); i++){
            if(((47 < val[i])&&(val[i] < 58))||((64 < val[i])&&(val[i] < 71))||(96 < val[i])&&(val[i] < 103)){}
            else
            {
                cout<<"Input Error: "+ val<<endl;
                return false;
            }
        }
    }
    else
        return true;
    */
    if(inputRule(val[0])||(val[0] == '-')){
               if(val.size() == 1){
                   return true;
               }
               else{
                   for(int i = 1; i < val.size(); i++){
                       if(!inputRule(val[i])){
                           cout<<"Input Error: "+ val<<endl;
                           return false;
                       }
                   }
               }
    }
    else
        return false;
}

string clearZerosInFirstPos(string hexString)//доработать
{
    unsigned int position = 0, counter = 0;
    for(int i = 0; i < hexString.size();i++){
        if(hexString[i] != '0'){
            position = i;break;
        }
        counter++;
    }

    string clearZerosString(hexString,position,hexString.size());
    //cout<<"clearZerosString:" << clearZerosString <<endl;
    //cout<<"position:" << position <<endl;
    if(position == 0 && counter == hexString.size())
        return "0";
    return clearZerosString;
}

bool inputRule(char chHex)
{
    int num = chHex;
    if((47 < num)&&(num < 58))
        return true;
    if((64 < num)&&(num < 71))
        return true;
    if((96 < num)&&(num < 103))
        return true;
    return false;
}
/*
vector <unsigned int> stringToVectorHex(string hex)
{
    vector <unsigned int> res(hex.size());
    bool flag = true;
    reverse(hex.begin(), hex.end());
    for(int i = 0; i < hex.size(); i++)
    {
        if(hex[i] >= 48 && hex[i]<= 57)
            res[i] = hex[i] - 48;
        else
            if(hex[i] >= 65 && hex[i]<= 70)
                res[i] = hex[i] - 55;
            else
                flag = false;
        if(flag == false)
        {
            reverse(hex.begin(), hex.end());
            cout<< "Input Error: " + hex << endl;
                break;
        }
    }
    return res;
}
*/
/*
unsigned int getSizeToConvert(unsigned int hexSize)
{
    int size = hexSize,rest = 0;
    rest = size & 7;
    size = size >> 3;
    if(rest != 0)
        size++;
    return size;
}
*/

