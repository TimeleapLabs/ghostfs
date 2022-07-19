@0xce9fa223fdadc118;

struct GetattrResponse {
  uuid    @0 :Text;
  attr    @1 :Attr;
  res     @2 :Int8;

  struct Attr {
    stDev     @0  :UInt16;
    stIno     @1  :UInt64;
    stMode    @2  :UInt64;
    stNlink   @3  :UInt16;
    stUid     @4  :Int64;
    stGid     @5  :Int64;  
    stRdev    @6  :UInt16;
    stSize    @7  :Int64;
    stAtime   @8  :TimeSpec;
    stMtime   @9  :TimeSpec;
    stCtime   @10 :Int64;
    stBlksize @11 :UInt64;
    stBlocks  @12 :UInt64;

    struct TimeSpec {
      tvSec        @0 :Int64;
      tvNSec       @1 :Int64;
    }
  }
}
