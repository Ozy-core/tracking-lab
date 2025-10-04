
#include <iostream>
#include <functional>
#include <cassert>
#include <string>

using namespace std;
template<typename x, typename y, typename result>

class tracker
{
    private: 
    function <result(x,y)> func;
    int track;
    result lastResult;

    public:
    tracker(function<result(x,y)> f: func(f),track(0), lastResult()){}

    result apply(x,y){
        lastResult= func(x,y);
        track++;
        return lastResult;
    }

    
    //getters
    void getCount()
    {
        cout << track << endl;
    }

    void getResult()
    {
        cout<< lastResult << endl;
    }

};