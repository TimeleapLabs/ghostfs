@0xf38b28335c79ec7d;

struct WriteResponse {
  ino     @0 :UInt64;
  res     @1 :Int8;
  errno   @2 :Int8;
  written @3 :UInt64;
}
