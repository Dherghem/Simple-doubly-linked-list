#include <iostream>
#include <iomanip>
#include <fstream>
#include "list.hpp"

using namespace std;
using List_i32  = List<int32_t>;
using cList_i32 = const List<int32_t>;

template                    <class UnaryPredicat>
List_i32 getConSeq          (UnaryPredicat p ,  cList_i32& originSeq);
List_i32 getSeqWithoutSome  (cList_i32& lst1,   cList_i32& lst2);

int main()
{
    ifstream fin("dat");
    List_i32     sourceLst;
    cin  >> sourceLst;

    List_i32     divThreeLst     = getConSeq (
                 [] (const int32_t & a) { return a % 3 == 0; },
                 sourceLst);

    List_i32     divTwoLst       = getConSeq (
                 [] (const int32_t & a) { return a % 2 == 0; },
                 sourceLst);

    List_i32     withoutSomeElem = getSeqWithoutSome (
                 divThreeLst, divTwoLst);

    cout << "Source List: "                << sourceLst       << endl << endl;
    cout << "Divide by three list: "       << divThreeLst     << endl << endl;
    cout << "Divide by two list: "         << divTwoLst       << endl << endl;
    cout << "Without some elements list: " << withoutSomeElem << endl << endl;

    for (auto i: divThreeLst) {
      cout << i << endl;
    }

    return 0;
}

template       <class UnaryPredicat>
List_i32 getConSeq (UnaryPredicat p, cList_i32& originSeq)
{
    List_i32 resLst;
    auto it = originSeq.find(p);
    while (it != originSeq.cend()) {
        resLst.push_end(*it);
        it = originSeq.find_after(p, it);
    }
    return resLst;
}


List_i32 getSeqWithoutSome (cList_i32& lst1, cList_i32& lst2)
{
    List_i32 resLst = lst1;
    for (auto it = lst2.cbegin(); it != lst2.cend(); ++it) {
        if (!resLst.remove_if(
                    [it] (const int32_t & a) { return a == *it; })
                ) {
            resLst.push_end(*it);
        }
    }
    return resLst;
}
