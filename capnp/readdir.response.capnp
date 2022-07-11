@0xf2f589d21924da65;

struct ReaddirResponse {
  uuid      @0 :Text;
  res       @1 :Int8;
  entries   @2 :List(Entry);

  struct Entry {
    name  @0 :Text;
    ino   @1 :UInt64;
  }
}
