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

class Main { -- Main class duplicate
    main(): Int {
        10
    };
};