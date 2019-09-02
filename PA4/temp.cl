
class A inherits C {
  my_func_1(): A { 
    {
      self;
      let var1: Int <- 0, var2: Int <- 0 in var2 + var1;
      var <- (new B);
      if true then (new IO).in_string() else 9 fi;
      case 9 of
        a: A => (new A);
        b: A => (new A);
        c: A => (new A);
      esac;
    }
  };
  my_func_2(): A { self };
};


class B inherits A {
  my_b_func(): B { var.my_b_func() };
  my_func_1(): A { my_func_2() };
  my_int_1: Int <- { my_test_func(); };
};


class C inherits IO {
  var: B;
  my_test_func(): Int { var.my_func_1() };
};

