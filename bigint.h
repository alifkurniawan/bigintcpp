#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class BigInt {
	
public:
	vector<int> digits;
	BigInt();
	BigInt(int a);
	BigInt(string num="0");
	BigInt operator +(BigInt a);
	void operator +=(BigInt a);
	void operator =(int a);
};

struct Ascii2Int { 
	int operator()(int c) {
		return c-'0';
	} 
};

BigInt::BigInt(string num) {
	transform(num.rbegin(), num.rend(), back_inserter(digits),Ascii2Int());
}

BigInt::BigInt(int num) {
	digits.push_back(num);
}

BigInt BigInt::operator +(BigInt a) {

	int num = 0;
	int carry = 0;
	BigInt temp("0");
	
	temp.digits = a.digits.size() > this->digits.size()? a.digits : this->digits;

	for (unsigned int i = 0; i < temp.digits.size(); i++) {
		int digit_val = i >= digits.size()? 0 : this->digits[i];
		int a_val = i >= a.digits.size()? 0 : a.digits[i];

		num = digit_val + a_val + carry;
		if (num >= 10) {
			num = num - 10;
			carry = 1;
		} else {
			carry = 0;
		}

		temp.digits[i] = num;
		
	}
	
	if (carry == 1) {
	 	temp.digits.push_back(1);
	}

	return temp;

}

void BigInt::operator +=(BigInt a) {
	*this = *this + a;
}

void BigInt::operator =(int a) {
	this->digits.push_back(a);
}

ostream& operator << (std::ostream& out,BigInt a)
{
   for(unsigned int i = 0 ; i < a.digits.size() ; i++){
      out << a.digits[a.digits.size() - 1 - i];
   }
   return out;
}