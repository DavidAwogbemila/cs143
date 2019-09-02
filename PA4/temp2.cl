class A {
  x: Int <- 0;
  y: Int <- x <- (new Int);
};

class B inherits A {
  i: Int <- x <- j;
  j: Int <- 5000 + 50000;
};
