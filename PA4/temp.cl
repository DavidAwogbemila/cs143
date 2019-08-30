class A inherits C{
  my_int_1: Int <- my_int_2 <- 8;
  my_int_2: Int <- 8;
  my_int_0: Int <- my_int_0;
  my_func_1 (): Int{ x };
};

class B inherits A{
  myattr: Int <- my_int_0;
  my_int_1: Int <- myattr;
  my_int_1: Int;
};

class C {
  my_int_0: Int <- (new Object);
};
