#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
 
const int CHOEAK = 987654321; //최악의난이도 큰숫자아무거나넣은듯
string WJY;
int cache[10000];
 
int nanido(int begin, int end){
  //부분숫자열 불러오기
  string S = WJY.substr(begin, end-begin+1);
 
  //난이도1 : 첫자리부터 쭉 같을때
  if( S == string(S.size(), S[0]) ){
	return 1;
  }
 
  //난이도2,5 : (공차가 +-1인)등차수열
  bool dngcha = true;
 
  for(int i=0; i<S.size()-1; i++){
	if(S[i+1] - S[i] != S[1] - S[0]){
	  dngcha = false;
	}
  }
 
  //	난이도2
  if( dngcha && abs(S[1] - S[0])==1 ){
	return 2;
  }
 
  //난이도4 : 숫자 번갈아등장
  bool bungara = true;
 
  for(int i=0; i<S.size(); i++){
	if(S[i] != S[i%2]){
	  bungara = false;
	}
  }
 
  if(bungara){
	return 4;
  }
 
  //	난이도5
  if(dngcha){
	return 5;
  }
 
  //난이도10 : 위에 아무것도 해당 안된경우
  return 10;
}
 
int memoization(int begin){
  //기저사례 : 탐색이 수열 끝에 도달
  if(begin == WJY.size()){
	return 0;
  }
 
  //메모이제이션 : 이미 계산한적 있으면 그거 리턴
  int& ret = cache[begin];
  if(ret != -1){
	return ret;
  }
 
  //본연산
  ret = CHOEAK;
  for(int jari=3; jari<=5; jari++){
	if(begin + jari <= WJY.size()){
	  ret = min(ret, nanido(begin, begin+jari-1)+memoization(begin+jari));
	  //앞(최악,3,4,5자리)의난이도+그뒤숫자들의최소값 비교
	}
  }
 
  return ret;
}
 
int main(void){
  int c;
  cin >> c;
  if(c<1 || c>50){
	exit(-1);
  }
 
  for(int i=0; i<c; i++){
	memset(cache, -1, sizeof(cache));
	cin >> WJY;
 
	cout << memoization(0) << "\n";
 
	WJY.clear();
  }
 
  return 0;
}