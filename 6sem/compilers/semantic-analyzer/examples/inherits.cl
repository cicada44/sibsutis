-- wrong

class A inherits B {

};

class B inherits A { -- inheritance loop

};

class C inherits D { -- unknown class D

};

-- right

class E {

};

class F inherits E {

};

-- no Main class