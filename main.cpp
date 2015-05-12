#include <header.h>


using namespace std;

int main()
{

     testFerma();
     testFindMu();
     testXEXPModM();
     testModRed();
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

    BigInt x("1AC7D2D2BA0A7CBB8FADC343CA530506FC0BFACDB8119D9E1DAB27D236E4A2E756D669");
    BigInt exp("E2C3E16884868BA45CD3AB5DE75732A110F0820C53E219F35275DCD78030C71B7285B9F05201B26D161127C5AADF59CDE9621CAF312670F8B6532C93C640F06D112B71E67518EFD6DBC77B4915BDC418F7BE129720");
    BigInt m("E2C3E16884868BA45CD3AB5DE75732A110F0820C53E219F35275DCD78030C71B7285B9F05201B26D161127C5AADF59CDE9621CAF312670F8B6532C93C640F06D112B71E67518EFD6DBC77B4915BDC418F7BE129721");
    //BigInt mu = findMu(m);
    //cout<<"mu "<<mu<<endl;
    //345a3b1dbad082b25f7410

    BigInt Res = Pow(x,exp,m);//modBarret(x,m,mu);//
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


