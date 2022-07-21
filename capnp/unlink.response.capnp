@0xbc9fe315ba0d7810;

struct UnlinkResponse {
  ino    @0 :UInt64;
  uuid   @1 :Text;
  res    @2 :Int8;
  errno  @3 :Int8;
}