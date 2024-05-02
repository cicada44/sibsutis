Class List inherits IO {
        (* Since abort() returns Object, we need something of
	   type Bool at the end of the block to satisfy the typechecker.
           This code is unreachable, since abort() halts the program. *)
	isNil() : Bool { { abort(); true; } };

	cons(hd : Int) : Cons {
	  (let new_cell : Cons <- new Cons in
		new_cell.init(hd,self)
	  )
	};

	(*
	   Since abort "returns" type Object, we have to add
	   an expression of type Int here to satisfy the typechecker.
	   This code is, of course, unreachable.
    *)

	car() : Int { { abort(); new Int; } };

	cdr() : List { { abort(); new List; } };

	rev() : List { cdr() };

	sort() : List { cdr() };

	insert(i : Int) : List { cdr() };

	rcons(i : Int) : List { cdr() };

	print_list() : Object { abort() };
};

Class Cons inherits List {
	xcar : Int;  -- We keep the car in cdr in attributes.
	xcdr : List; -- Because methods and features must have different names,
		     -- we use xcar and xcdr for the attributes and reserve
		     -- cons and car for the features.

	isNil() : Bool { false };

	init(hd : Int, tl : List) : Cons {
	  {
	    xcar <- hd;
	    xcdr <- tl;
	    self;
	  }
	};

	car() : Int { xcar };

	cdr() : List { xcdr };

	rev() : List { (xcdr.rev()).rcons(xcar) };

	sort() : List { (xcdr.sort()).insert(xcar) };

	insert(i : Int) : List {
		if i < xcar then
			(new Cons).init(i,self)
		else
			(new Cons).init(xcar,xcdr.insert(i))
		fi
	};

	rcons(i : Int) : List { (new Cons).init(xcar, xcdr.rcons(i)) };

	print_list() : Object {
		{
		     out_int(xcar);
		     out_string("\n");
		     xcdr.print_list();
		}
	};
};

Class Nil inherits List {
	isNil() : Bool { true };

    rev() : List { self };

	sort() : List { self };

	insert(i : Int) : List { rcons(i) };

	rcons(i : Int) : List { (new Cons).init(i,self) };

	print_list() : Object { true };
};

Class Main inherits IO {
	l : List;

	(* iota maps its integer argument n into the list 0..n-1 *)
	iota(i : Int) : List {
	    {
		l <- new Nil;
		(let j : Int <- 0 in
		   while j < i
		   loop
		     {
		       l <- (new Cons).init(j,l);
		       j <- j + 1;
		     }
		   pool
		);
		l;
	    }
	};

	main() : Object {
	   {
	     out_string("How many numbers to sort?");
	     iota(in_int()).rev().sort().print_list();
	   }
	};
};
