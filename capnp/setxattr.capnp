@0xe378f0954c487a37;

struct Setxattr {
  ino       @0  :UInt64;
  name      @1  :Text;
  value     @2  :Text;
  size      @3  :UInt64;
  flags     @4  :Int32;
  position  @5 :UInt32;
  uuid      @6  :Text;
}