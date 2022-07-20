@0xe16f6a3b0b74ec20;

struct Mknod {
    parent @0 :UInt64;
    name   @1 :Text;
    mode   @2 :UInt64;
    rdev   @3 :UInt16;
    uuid   @4 :Text;
}