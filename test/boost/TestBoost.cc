#include <iostream>
#include <boost/tuple/tuple.hpp>
int main()
{
    using namespace std;
    int i;
    char c;
    double d;
    boost::tuples::tie(i,c,d);
    boost::tuples::tie(i,c,d) = boost::tuples::tuple <int,char,double>(1,'A',0.68);
    cout << d <<endl;
}