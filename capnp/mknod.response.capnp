@0xc60b7156590c083d;

struct MknodResponse {
  ino    @0 :UInt64;
  res    @1 :Int8;
  errno  @2 :Int8;
  attr   @3 :Attr;

  struct Attr {
    stDev     @0  :UInt16;
    stIno     @1  :UInt64;
    stMode    @2  :UInt64;
    stNlink   @3  :UInt16;
    stUid     @4  :Int64;
    stGid     @5  :Int64;  
    stRdev    @6  :UInt16;
    stSize    @7  :Int64;
    stAtime   @8  :Int64;
    stMtime   @9  :Int64;
    stCtime   @10 :Int64;
    stBlksize @11 :UInt64;
    stBlocks  @12 :UInt64;
  }
}