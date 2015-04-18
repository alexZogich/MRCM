#include <header.h>


using namespace std;

int main()
{

    testBigIntConstruct();
    testIntConstruct(); //BigInt( digit : int )
    testUnarySub();		//unary "-"
    testNotEqual();// operation "!="
    testEqual();//   operation "=="
    testLess();//need more tests		//operation "<"
    testMore();//need more tests
    testMoreAndEq();//operation ">="
    testLessAndEq();//operation "<="
    testSum();//     operation "+"


    BigInt A("-CAF3A4345433BE444FFF23BCD434228A");
    BigInt B("ABCBC353BCD4343FFABFFFF45FFECCD");
    BigInt C;
   // C = (A) + (B);//Bug от большего по модулю надо вычитать
    //C = - A - B;
    //C = A - B;
    //C = A - (-B);



    cout<<"C == "<<C.toString()<<endl;

    return 0;
}


