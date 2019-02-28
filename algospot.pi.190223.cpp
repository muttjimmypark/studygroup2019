#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
 
const int CHOEAK = 987654321; //�־��ǳ��̵� ū���ھƹ��ų�������
string WJY;
int cache[10000];
 
int nanido(int begin, int end){
  //�κм��ڿ� �ҷ�����
  string S = WJY.substr(begin, end-begin+1);
 
  //���̵�1 : ù�ڸ����� �� ������
  if( S == string(S.size(), S[0]) ){
	return 1;
  }
 
  //���̵�2,5 : (������ +-1��)��������
  bool dngcha = true;
 
  for(int i=0; i<S.size()-1; i++){
	if(S[i+1] - S[i] != S[1] - S[0]){
	  dngcha = false;
	}
  }
 
  //	���̵�2
  if( dngcha && abs(S[1] - S[0])==1 ){
	return 2;
  }
 
  //���̵�4 : ���� �����Ƶ���
  bool bungara = true;
 
  for(int i=0; i<S.size(); i++){
	if(S[i] != S[i%2]){
	  bungara = false;
	}
  }
 
  if(bungara){
	return 4;
  }
 
  //	���̵�5
  if(dngcha){
	return 5;
  }
 
  //���̵�10 : ���� �ƹ��͵� �ش� �ȵȰ��
  return 10;
}
 
int memoization(int begin){
  //������� : Ž���� ���� ���� ����
  if(begin == WJY.size()){
	return 0;
  }
 
  //�޸������̼� : �̹� ������� ������ �װ� ����
  int& ret = cache[begin];
  if(ret != -1){
	return ret;
  }
 
  //������
  ret = CHOEAK;
  for(int jari=3; jari<=5; jari++){
	if(begin + jari <= WJY.size()){
	  ret = min(ret, nanido(begin, begin+jari-1)+memoization(begin+jari));
	  //��(�־�,3,4,5�ڸ�)�ǳ��̵�+�׵ڼ��ڵ����ּҰ� ��
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