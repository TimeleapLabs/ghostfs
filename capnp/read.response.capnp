@0xb71ff6604c28bbcd;

struct ReadResponse {
  ino    @0 :UInt64;
  buf    @1 :Data;
  res    @2 :Int8;
  errno  @3 :Int8;
}
