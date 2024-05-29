class Int {};

class Bool {};

class Main {};

class String {};

class Main {
    a : Int;
    a : Int; -- class field duplicate

    main(b : Int): Int {
        {
            let b: Int <- 4 in false; -- class field override
            10;
        }
    };

    main(): Int { -- method duplicate
        10
    };
};

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
