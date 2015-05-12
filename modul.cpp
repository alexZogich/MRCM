#include "header.h"


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
    while(res.digits[res.digits.size() - 1] == 0 && res.digits.size() != 1)
    {
        res.digits.pop_back();
        res.length--;
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

    while(res.digits[res.digits.size() - 1] == 0 && res.digits.size() != 1)
    {
        res.digits.pop_back();
        res.length--;
    }
    return res;
}

BigInt Mul(const BigInt &u, const unsigned int v)// Unsigned int mul
{
    BigInt w;
    if((u.digits[0] == 0 && u.length == 1) ||(v == 0)){
        w.setZero();
        return w;
    }
    unsigned int rest = 0,
                 m = u.length;
    long long unsigned int temp = 0;

    w.length = u.length + 1;
    w.sign = u.sign;

    for(int i = 0; i < w.length; i++)
        w.digits.push_back(0);

    for(int i = 0; i < m; i++){
        temp = (long long unsigned int) u.digits[i] * v + rest;
        w.digits[i] = temp;
        rest = temp >> 32;
    }

    if(rest != 0){
        w.digits[u.length] = rest;
    }
    else{
        w.digits.pop_back();
        w.length = w.length - 1;
    }
    while(w.digits[w.digits.size() - 1] == 0 && w.digits.size() != 1)
    {
        w.digits.pop_back();
        w.length--;
    }
    return w;
}

BigInt Div(const BigInt &u, const BigInt &v)
{
   if(v.length != 1)
       return u/v;
   vector <unsigned int> value(u.length,0);
   BigInt w;
   w.concVector(value,0);
   w.sign = u.sign ^ v.sign;
   unsigned int r = 0;
   int j = u.length - 1;

   while(j>=0)
   {
       w.digits[j] = (r * BASE + u.digits[j]) / v.digits[0];
       r = (r * BASE + u.digits[j]) % v.digits[0];
       j--;
   }
   while(w.digits[w.digits.size()-1] == 0 && w.digits.size() != 1)
   {
       w.digits.pop_back();
       w.length--;
   }
   return w;
}

BigInt Mul(const BigInt &u, const BigInt &v)
{
    BigInt w;
    if(u == BigInt(0) || v == BigInt(0))//((u.digits[0] == 0 && u.length == 1) ||(v.digits[0] == 0 && v.length == 1))
        return BigInt(0);
    if(v.length == 1)
        return Mul(u,v.digits[0]);
    unsigned int rest = 0, n = v.length, m = u.length;
    long long unsigned int temp = 0;

    w.length = u.length + v.length;
    w.sign = u.sign ^ v.sign;
    for(int i = 0; i < w.length; i++)
        w.digits.push_back(0);
    for(int j = 0; j < n; j++)
    {
        if(v.digits[j] == 0){
            w.digits[j + u.length] = 0;
            continue;
        }
        else{
            rest = 0;
            for(int i = 0; i < m; i++){
                temp = (long long unsigned int) u.digits[i]*v.digits[j] + w.digits[i+j] + rest;
                w.digits[i+j] = temp;
                rest = temp >> 32;
            }
            w.digits[j + u.length] = rest;
        }
    }
    while(w.digits[w.digits.size()-1] == 0 && w.digits.size() != 1)
    {
        w.digits.pop_back();
        w.length--;
    }

    return w;
}
vector<BigInt> knutDivision(const BigInt &u, const BigInt &v)// first div,second mod
{
    vector<BigInt> vecRes;
    // Предпроверка деления на нуль
    if(v == BigInt(0))
    {
        cout<<"knutDivision: Input Error(division on Zero)!!! "<<endl;
        vecRes.push_back(BigInt(0));
        vecRes.push_back(BigInt(0));
        return vecRes;
    }
    BigInt Q;
    Q.sign = u.sign ^ v.sign;
    BigInt U = u,
           V = v;
    if(U.sign == true || V.sign == true){
        V.sign = U.sign = false;
    }
        //Если U < V возвращаем нуль???
    if((U == BigInt(0)) || U < V ){
        vecRes.push_back(BigInt(0));
        U.sign = Q.sign;
        vecRes.push_back(U);
        return vecRes;
    }
    if(v.length == 1)
    {
        BigInt div = Div(U,V);
        BigInt mod = U - (V*div);
        div.sign = Q.sign;
        vecRes.push_back(div);
        if(div.sign == true)
            mod = mod + V;
        vecRes.push_back(mod);
        return vecRes;
    }
    //Нормализация
    int m = U.length - V.length,
        n = V.length;
    vector<unsigned int> mZeros(m+1,0);
    Q.concVector(mZeros,1);
    long long unsigned int q = 0,
                           r = 0,
                           temp = 0,
    d = BASE /(V.digits[n - 1] + 1);

    if(d == 1){
       U.digits.push_back(0);
       U.length +=1;
    }
    else{
       U = Mul(U,d);
    }
       V = Mul(V,d);

    vector <unsigned int> nPlusOneZeros(n+1,0);
    BigInt hiU,loU, bPowNplusOne;

    bPowNplusOne =  BigInt(1);
    bPowNplusOne.concVector(nPlusOneZeros,1);

    unsigned int tempLenght;
    int j = m;
    bool flag = false;
    if (U.length==j+n) {
        U.digits.insert(U.digits.end(), 0);
        U.length++;
     }

    while(j >= 0)
    {
            //D3 шаг
            temp = (long long unsigned int)U.digits[j + n] * BASE + U.digits[j + n - 1];
            q = (long long unsigned int)temp / V.digits[n - 1];
            r = (long long unsigned int)temp %  V.digits[n - 1];
            do
            {

                if((q == BASE) || ((long long unsigned int)q*V.digits[n - 2] > (long long unsigned int)BASE*r + U.digits[ j + n - 2])){
                    q --;
                    r += V.digits[n - 1];
                }
                else{
                    break;
                }

            }
            while(r < BASE);
            //D4 шаг
            loU = U.split(j,0);
            hiU = U.split(j,1);
            hiU = hiU - Mul(V,q);
            flag = false;

            if(hiU.sign == true){
                flag = true;
                hiU = hiU + bPowNplusOne;

            }
            //D5 + D6 шаги
            Q.digits[j] = q;
            if(flag == true)
            {
                Q.digits[j]--;
                tempLenght = hiU.length;
                hiU = hiU + V;
                if(tempLenght!= hiU.length){
                    hiU.digits.pop_back();
                    hiU.length -=1;
                }
            }
            for(int i = 0; i<U.digits.size() - hiU.digits.size(); i++)
                hiU.digits.push_back(0);
            hiU.length = hiU.digits.size();
            U = concBigInt(hiU,loU);
            j--;
    }
    while(Q.digits[Q.digits.size()-1] == 0 && Q.digits.size() != 1)
    {
        Q.digits.pop_back();
        Q.length--;
    }
    vecRes.push_back(Q);
    vecRes.push_back(Div(U,BigInt(d)));
    return vecRes;
}

BigInt operator / (const BigInt &u, const BigInt &v)
{
    vector<BigInt> Res = knutDivision(u,v);
    return Res[0];
}

BigInt operator % (const BigInt &u, const BigInt &v)
{
    vector<BigInt> Res = knutDivision(u,v);
    return Res[1];
}

BigInt findMu(const BigInt &mod)
{
    BigInt bPowTwoK(1);
    unsigned int k = mod.length;
    vector<unsigned int> twoKzeros(2*k,0);
    bPowTwoK.concVector(twoKzeros,1);
    return bPowTwoK/mod;
}

BigInt modBarret(const BigInt &x, const BigInt &m,const BigInt &mu)
{

    unsigned int k = m.length,
                 n = x.length;
    if(x == BigInt(0))
        return BigInt(0);
    if(m == BigInt(0)){
        cout<<"modBarret Error: Zero modul!!!"<<endl;
        return BigInt(0);
    }
    if(m.sign == true){
        cout<<"modBarret Error: Negative modul!!!"<<endl;
        return BigInt(0);
    }
    if(n > 2*k){
        return x%m;
    }
    BigInt  X = x,
            M = m;
    if(x.sign == true)
        X.sign = false;
    if(X < M)
    {
        if(x.sign == false)
            return X;
        else
            return M - X;
    }

    BigInt  q1 = X.split(k-1,1);
    BigInt  r1 = X.split(k+1,0);
    q1 = q1 * mu;
    q1 = q1.split(k+1,1);

    BigInt bPowKpusOne(1);
    vector<unsigned int> kPusOneZeros(k+1,0);
    bPowKpusOne.concVector(kPusOneZeros,1);

    BigInt r;
    BigInt r2 = q1*M;
    r2 = r2.split(k+1,0);
    if(r1 >= r2)
        r = r1 - r2;
    else
        r = bPowKpusOne + r1 - r2;

    while(r >= M)
        r = r - M;

    if(x.sign == false)
        return r;
    else
        return M - r;
}

BigInt Pow(const BigInt &x, const BigInt &exp, const BigInt &m)
{
    BigInt mu = findMu(m),
           X = x,
           res(1);
    unsigned int bit;
    for(int i = 0; i < exp.digits.size(); i++)
    {
        for(int j = 0; j < countOfBits; j++)
        {
            bit = (exp.digits[i] >> j) & 1;
            if(bit!=0){
                res = modBarret( res*X, m, mu);
                //res = (res*X)%m;
            }
            //X = (X*X)%m;
            X = modBarret( X*X, m, mu);
        }
    }

    //temp1 = exp.digits[exp.digits.size()-1];
    //while(temp!=0)werqwerqwertwetwetwert
    //{
    //    bit = temp1 & 1;
    //}
    return res;
}

/*
BigInt operator / (const BigInt &u, const BigInt &v)
{
    // Предпроверка деления на нуль
    if(v == BigInt(0))
    {
        cout<<"Operator Div: Input Error(division on Zero)!!! "<<endl;
        return BigInt(0);
    }
    BigInt Q;
    Q.sign = u.sign ^ v.sign;
    BigInt U = u,
           V = v;
    if(U.sign == true || V.sign == true){
        V.sign = U.sign = false;
    }
        //Если U < V возвращаем нуль???
    if((U == BigInt(0)) || U < V ){
        return BigInt(0);
    }
    if(v.length == 1)
        return Div(u,v);
    //Нормализация
    int m = U.length - V.length,
        n = V.length;
    vector<unsigned int> mZeros(m+1,0);
    Q.concVector(mZeros,1);
    long long unsigned int q = 0,
                           r = 0,
                           temp = 0,
    d = BASE /(V.digits[n - 1] + 1);

    if(d == 1){
       U.digits.push_back(0);
       U.length +=1;
    }
    else{
       U = Mul(U,d);
    }
       V = Mul(V,d);

    vector <unsigned int> nPlusOneZeros(n+1,0);
    BigInt hiU,loU, bPowNplusOne;

    bPowNplusOne =  BigInt(1);
    bPowNplusOne.concVector(nPlusOneZeros,1);

    unsigned int tempLenght;
    int j = m;
    bool flag = false;
    if (U.length==j+n) {
        U.digits.insert(U.digits.end(), 0);
        U.length++;
     }

    BigInt tempU;
    while(j >= 0)
    {
            //D3 шаг
            temp = (long long unsigned int)U.digits[j + n] * BASE + U.digits[j + n - 1];
            q = (long long unsigned int)temp / V.digits[n - 1];
            r = (long long unsigned int)temp %  V.digits[n - 1];
            //cout<<endl<<"j "<<j<<endl;
            //cout<<"q "<<q<<endl;
            //cout<<"r "<<r<<endl;
            do
            {

                if((q == BASE) || ((long long unsigned int)q*V.digits[n - 2] > (long long unsigned int)BASE*r + U.digits[ j + n - 2])){
                    q --;
                    r += V.digits[n - 1];
                }
                else{
                    break;
                }

            }
            while(r < BASE);

            //D4 шаг
            loU = U.split(j,0);
            hiU = U.split(j,1);
            hiU = hiU - Mul(V,q);
            //cout<<"hiU "<<hiU<<endl;
            flag = false;

            if(hiU.sign == true){
                //cout<<"D4"<<hiU<<endl;
                flag = true;
                hiU = hiU + bPowNplusOne;

            }
            //D5 + D6 шаги
            Q.digits[j] = q;

            if(flag == true)
            {
                Q.digits[j]--;
                tempLenght = hiU.length;
                hiU = hiU + V;
                if(tempLenght!= hiU.length){
                    hiU.digits.pop_back();
                    hiU.length -=1;
                }
            }
            for(int i = 0; i<U.digits.size() - hiU.digits.size(); i++)
                hiU.digits.push_back(0);
            hiU.length = hiU.digits.size();
            U = concBigInt(hiU,loU);
            //cout<<endl<<"U "<<U<<endl;
            j--;
    }
    while(Q.digits[Q.digits.size()-1] == 0 && Q.digits.size() != 1)
    {
        Q.digits.pop_back();
        Q.length--;
    }
    return Q;
}
*/

/*
u0.digits.reserve(halfSize);
v0.digits.reserve(halfSize);
v1.digits.reserve(v.length - halfSize);
u1.digits.reserve(u.length - halfSize);

u0.digits.insert(u0.digits.end(),u.digits.begin(),u.digits.begin() + halfSize);
v0.digits.insert(v0.digits.end(),v.digits.begin(),v.digits.begin() + halfSize);
u1.digits.insert(u1.digits.end(),u.digits.begin()+halfSize,u.digits.end());
v1.digits.insert(v1.digits.end(),v.digits.begin()+halfSize,v.digits.end());

u0.length = u0.digits.size();
u1.length = u1.digits.size();
v0.length = v0.digits.size();
v1.length = v1.digits.size();
*/
/*
v1.digits.reserve(v.length - halfSize);
v0.digits.insert(v0.digits.end(),v.digits.begin(),v.digits.begin() + halfSize);
v1.digits.insert(v1.digits.end(),v.digits.begin() + halfSize,v.digits.end());
v0.length = v0.digits.size();
v1.length = v1.digits.size();
*/
/*
u0.digits.reserve(halfSize);
u1.digits.reserve(u.length - halfSize);
u0.digits.insert(u0.digits.end(),u.digits.begin(),u.digits.begin() + halfSize);
u1.digits.insert(u1.digits.end(),u.digits.begin() + halfSize,u.digits.end());
u0.length = u0.digits.size();
*/

BigInt concBigInt(const BigInt& hi, const BigInt& lo)
{
    BigInt Res;
    if(hi == BigInt(0))
        return lo;
    Res.length = hi.length + lo.length;
    Res.digits.reserve(Res.length);
    Res.digits.insert( Res.digits.end(), lo.digits.begin(), lo.digits.end());
    Res.digits.insert( Res.digits.end(), hi.digits.begin(), hi.digits.end());
    Res.sign = hi.sign;
    return Res;
}

BigInt operator * (const BigInt &u, const BigInt &v)
{
    if(u.length < 10 && v.length < 10)
    {
        return Mul(u,v);
    }
    BigInt U = u, V = v, u0, v0, u1, v1, A, B ,C,Res;
    bool sign = u.sign ^ v.sign;
    //cout<<"sign "<<sign<<endl;
    unsigned int size = max(u.length,v.length),
                 flag = 0;
    unsigned int halfSize = (size >> 1) + (size & 1);//?????
    if(halfSize < u.length && halfSize < v.length)
    {
        u0 = U.split(halfSize,0);
        u1 = U.split(halfSize,1);
        v0 = V.split(halfSize,0);
        v1 = V.split(halfSize,1);
        A = u1*v1;
        B = u0*v0;
        C = ((u1+u0)*(v1+v0));
        /*
        A = Mul(u1,v1);
        B = Mul(u0,v0);
        C = Mul(u1+u0,v1+v0);
        */
    }
    else
    {
        flag = 1;
        if(u.length <= halfSize)
        {
            u0 = U;
            v0 = V.split(halfSize,0);
            v1 = V.split(halfSize,1);
            //C = Mul(u0,v1+v0);
            C = u0*(v1+v0);
        }
        else
        {
            v0 = V;
            u0 = U.split(halfSize,0);
            u1 = U.split(halfSize,1);
            //C = Mul(u0+u1,v0);
            C = (u0+u1)*v0;
        }
        //B = Mul(u0,v0);
        B = u0*v0;
    }
    vector<unsigned int> halfSizeZeros(halfSize,0);
    if(flag == 0) // A*b^2n +(C - A - B)*b^n + B
    {
        vector<unsigned int> twoHalfSizeZeros(2*halfSize,0);
        Res = ((C - A) - B);
        Res.concVector(halfSizeZeros,1);//?
        A.concVector(twoHalfSizeZeros,1);
        Res = Res + B + A;
    }
    else //(C - B)*b^n + B
    {
        Res = C - B;
        Res.concVector(halfSizeZeros,1);
        Res = Res + B;
    }
    while(Res.digits[Res.digits.size() - 1] == 0 && Res.digits.size() != 1)
    {
        Res.digits.pop_back();
        Res.length--;
    }
    return Res;
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


