@0xe8f7e533ce1c491c;

struct LookupResponse {
  ino   @0 :UInt64;
  attr  @1 :Attr;
  res   @2 :Int8;
  errno @3 :Int8;

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
