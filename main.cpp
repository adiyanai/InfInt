#include <iostream>
#include <cstring>
#include <cstdlib>

#include "LargeIntegers.h"

using namespace std;

// make sure the programs does not take too long to run!
int main()
{
    InfInt test;
    bool test2;
    InfInt n0("86821447646456089524285253792986");
    InfInt n1("35188382967490645373120012351712373104282483824");
    InfInt n2("928450997227214408095194374507739636518959954727480989580469229456009308420247");
    InfInt n3("9033541564");
    InfInt n4("28023686735046156467151609079944110881102361495");
    int s0 = 1421;
    int s1 = 350;
    test = n0 + n1;
    cout<<"test 0 ";
    cout << (test == InfInt("35188382967490732194567658807801897389536276810") ? "passed" : "failed") << endl;
    test = n4 - n3;
    cout<<"test 1 ";
    cout << (test == InfInt("28023686735046156467151609079944110872068819931") ? "passed" : "failed") << endl;
    test = n4 / n2;
    cout<<"test 2 ";
    cout << (test == InfInt("0") ? "passed" : "failed") << endl;
    test = n2 % n1;
    cout<<"test 3 ";
    cout << (test == InfInt("15159896899146713242308545254279595761494240343") ? "passed" : "failed") << endl;
    test = n1 ^ n4;
    cout<<"test 4 ";
    cout << (test == InfInt("15728207241445796392057443781906438152654114791") ? "passed" : "failed") << endl;
    test = n0 & n4;
    cout<<"test 5 ";
    cout << (test == InfInt("81506339747521164660607453147282") ? "passed" : "failed") << endl;
    test = n2 | n1;
    cout<<"test 6 ";
    cout << (test == InfInt("928450997227214408095194374507751074367966564769167034603668793533368991792375") ? "passed" : "failed") << endl;
    test2 = n2 < n0;
    cout<<"test 7 ";
    cout << (test2 == false ? "passed" : "failed") << endl;
    test2 = n2 == n3;
    cout<<"test 8 ";
    cout << (test2 == false ? "passed" : "failed") << endl;
    test2 = n3 > n1;
    cout<<"test 9 ";
    cout << (test2 == false ? "passed" : "failed") << endl;
    test2 = n4 <= n3;
    cout<<"test 10 ";
    cout << (test2 == false ? "passed" : "failed") << endl;
    test2 = n1 >= n1;
    cout<<"test 11 ";
    cout << (test2 == true ? "passed" : "failed") << endl;
    test = n3 << s0;
    cout<<"test 12 ";
    cout << (test == InfInt("524181737004945467049174847531189421588135251842024415797796345941397249399606573946003462369870999541606626175747267638067607684087252528756514807518298623666584503273952972957256757191951544344768909109018412683576771222288883352639993986686226340828435303346288770097409954912762953127478223284180516905220472347368945877573833591191619593025788164236120975411322183972352879349915102791734094788050998043291085279519614104229776457728") ? "passed" : "failed") << endl;
    test = n0 >> s0;
    cout<<"test 13 ";
    cout << (test == InfInt("0") ? "passed" : "failed") << endl;


    return 0;
}