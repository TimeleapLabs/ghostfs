@0xb71ff6604c28bbcd;

struct ReadResponse {
  ino   @0 :UInt64;
  buf   @1 :Data;
  uuid  @2 :Text;
  res   @3 :Int8;
  errno   @4 :Int8;
}
