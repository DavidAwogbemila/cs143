class A inherits C{
  my_int_1: Int <- my_int_2 <- 8;
  my_int_2: Int <- 8;
  my_int_0: Int <- my_int_0;
};

class B inherits A{
  myattr: Int <- my_int_0;
  my_int_1: Int <- myattr;
};

class C {
  my_int_0: Int <- 0;
};
