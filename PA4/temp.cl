
class A inherits C {
  my_func_1(): A { 
    {
      self;
      let var1: Int <- true, var2: Int <- 0 in var2 + var1;
      var <- (new B);
      if true then (new IO).in_string() else 9 fi;
      case 9 of
        a: B => var <- (new B);
        b: Int => (new Int) + 9;
        c: SELF_TYPE => self.my_func_1();
      esac;
    }
  };
  my_func_2(): A { self };
};


class B inherits A {
  my_b_func(): C { var.my_b_func() };
  my_func_1(): String { my_func_2() };
  my_int_1: Int <- { my_int_1@Object.abort(); };
};


class C inherits IO {
  var: B;
  my_test_func(): Int { var.my_func_1() };
};

