#include <header.h>


using namespace std;

int main()
{

     testSpecialNumber();
     testOdnoRozryadResult();
     testDivToOneRozryad(); // test div to one rozryad
     testDivRevToMult();
     testDiv(); // test for div
     testSimpleMulHexAndInt(); // mul BigInt and Int
     testKarazuba512(); // test for length >512bit
     testKarazuba(); // karazuba :)
     testSimpleMul();   // C = Mul(A,B)
     testBigIntConstruct(); //BigInt( bigint : &BigInt ) // a = b
     testUnarySub();		//unary "-"
     testIntConstruct(); //BigInt( digit : int )
     testMoreAndEq();	//	operation ">="
     testLessAndEq();	//	operation "<="
     testMore();		// operation ">"
     testLess();		// operation "<"
     testNotEqual(); // operation "!="
     testEqual();   // operation "=="
     testSum();     // operation "+"
     testSub();     // operation "-"


    BigInt W("84880796000000000001C085F7F572FD0000000000000000000000000000000000000000000000000000000000000006DD722D17B86D4E0000000000000000000000000000073F5664898A070520001886D8E1FF8212A76226F0000000000000000000000000000000000000000000000000000000601A5DC79FC24ED913599BA00000000000000000000000008F2AFE486C48710279");

    BigInt u("C7939F0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000AE9DC1BB8EB505");
    //AA0000000000000000023F53E30000000000000000000000000000000000000000000000000000000000000000000008CE4D7FF2000000000000000000000000000000000000000D1E5
    BigInt Res = W/u;
    cout<<"Res: "<<Res<<endl;
/*
    BigInt A("0");
    BigInt B("-123123123121212121212121212121121231231231224342BCDA32320322C1");
    BigInt C;
    C = Mul(A,B);
    if(C.toString()=="0")
        cout<<"Success!!"<<endl;
    else
        cout<<"ERROR"<<C.toString()<<endl;

*/




    std::vector<int> lines(10,5);
    std::vector<int> split_lo;
    // fill
    std::size_t const half_size = lines.size() / 2;
    split_lo.reserve(half_size);
    split_lo.insert(split_lo.end(),lines.begin(), lines.begin() + half_size);
    for(int i = 0; i < split_lo.size();i++)
        cout<<split_lo[i]<<endl;



    return 0;
}


