#include <iostream>
#pragma once
# pragma once
#

std::string s = "hello, regex";
char* standard = "abcdef";
char* empty = "";
wchar_t* pie = L"pie" L"PIE";
wchar_t* elphabet = L"ALPHABET";
char32_t* hp = U"HAVEFUN" "HF";
char32_t* vg = U"Very Good";
char16_t* oth = "one" u"two" "three";
char16_t* WOW = u"!!";

int d = 42;
int o = 052;
int x = 0x2a;
int X = 0X2A;
int b = 0b101010; // C++14
unsigned long long l1 = 18446744073709550592ull; // C++11
unsigned long long l2 = 18'446'744'073'709'550'592llu; // C++14
unsigned long long l3 = 1844'6744'0737'0955'0592uLL; // C++14
unsigned long long l4 = 184467'440737'0'95505'92LLU; // C++14

// comment
/* comment */
/*
comment*/
/*
comment
*/

char8_t cu8 = u8'a';
char16_t cu = u'a';
char32_t cU = U'a';
wchar_t wc1 = L'a';
char cnormal1 = 'a';
char cascii = '\01';
char casciihex = '\xb0';

for (;;)

while ()

if ()

int d1 = 1023;
unsigned int d2 = 3;
long int d3 = 1;
long long d4 = 2;
unsigned long long d5 = 100500'';
unsigned long d6 = 11249102uL;

int o = 0553;
int h1 = 0x5A;
int h2 = 0X998a;
int b1 = 0b10101;
int b2 = 0B00001;
float f1 = 58.;
float f2 = 4e2;
float f3 = 123.456e-67;
float f4 = 123.456e-67f;
float f5 = .1E4f;
float f6 = 0x10.1p0;
float f7 = 0x1p5;
float f9 = 3.14'15'92;
float f10 = 1.18e-4932l;
float f11 = 3.4028234e38f;
float f12 = 3.4028234e38;

a[b] = 1;
*a = 1;
&a = nullptr;
a.b = 1;
a->b = nullptr;
a.*b = 1;
a->*b = 1;
non-accessor{1};

int a = 1, b = 2;
bool com = a == b;
com = a != b;
com = a < b;
com = a > b;
com = a <= b;
com = a >= b;

a = b;
a += b;
a -= b;
a *= b;
a /= b;
a %= b;
a &= b;
a |= b;
a ^= b;
a <<= b;
a >>= b;
