// preprocessor
#if <NAME>
#ifdef <NAME>
#ifndef <NAME>
#if defined(<NAME>)
#if !defined <NAME>
#else if <NAME>
#elif <NAME>

// keywords
for(;;) {

}
while() {

}
if() {

}

/* Some comment */

/*
hi!
*/

// decimal
int d1 = 1023;
unsigned int d2 = 3;
long int d3 = 1;
long long d4 = 2;
unsigned long long d5 = 100'500;
unsigned long d6 = 11249102uL;
123'''666';

// oct
int o = 0553;

// hex
int h1 = 0x5A;
int h2 = 0X998a;

// byte
int b1 = 0b10101;
int b2 = 0B00001;

// floats
float f1 = 58.;
float f2 = 4e2;
float f3 = 123.456e-67;
float f4 = 123.456e-67f;
float f5 = .1E4f;
float f6 = 0x10.1p0;
float f7 = 0x1p5;
float f8 = 0x1e5;
float f9 = 3.14'15'92;
float f10 = 1.18e-4932l;
float f11 = 3.4028234e38f;
float f12 = 3.4028234e38;
float f13 = 3.4028234e38l;

// comparison
int a = 1, b = 2;
bool com = a == b;
com = a != b;
com = a < b;
com = a > b;
com = a <= b;
com = a >= b;

// assignment
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

// member access
a[b] = 1;
*a = 1;
&a = nullptr;
a.b = 1;
a->b = nullptr;
a.*b = 1;
a->*b = 1;
wrong-accessor{1};

// chars
char c1 = 'a';
char c2 = '\77';
char c3 = '\xa7';
char8_t C1 = u8'a';
char16_t uc1 = u'a';
char32_t Uc1 = U'a';
wchar_t wc1 = L'a';

// strings
const char* p = "abcdef";
std::string s = "hello, world!";
const char* p = "";
const wchar_t* s4 = L"hey" L"HELLO";
const wchar_t* s5 = L"ALPHABET";
const char32_t* s6 = U"Jekyll" "JKL";
const char32_t* s7 = U"Very Good";
const char16_t* s9 = "one" u"two" "three";
const char16_t* sA = u"!!";

// user-defined literals
1.2_w;
u"one"_w;
12_km;
L"A" "B" "C"_x;
"abc"_x2;