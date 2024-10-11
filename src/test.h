#include <string>
#include <vector>

using namespace std;

long long solution(int r1, int r2) {
    long long answer = 0;
    for(int i=0;i<r2;i++){
        for(int j=0;j<r2;j++){
            if(i^2+j^2<=r2^2 &&i^2+j^2>=r1^2)
                answer++
        }
    }
    answer *=4;
    return answer;
}