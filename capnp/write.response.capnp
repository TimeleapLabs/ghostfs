@0xf38b28335c79ec7d;

struct WriteResponse {
  ino     @0 :UInt64;
  uuid    @1 :Text;
  res     @2 :Int8;
  errno   @3 :Int8;
  written @4 :UInt64;
}
