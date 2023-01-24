@0x84fa4a8767d90237;

struct CreateResponse {
  ino    @0 :UInt64;
  res    @1 :Int8;
  errno  @2 :Int8;
  fi     @3 :FuseFileInfo;
  attr   @4 :Attr;

  struct FuseFileInfo {
    flags         @0  :Int64;
    writepage     @1  :UInt64;
    directIo      @2  :UInt64;
    keepCache     @3  :UInt64;
    flush         @4  :UInt64;
    nonseekable   @5  :UInt64;
    cacheReaddir  @6  :UInt64;
    padding       @7  :UInt64;
    fh            @8  :UInt64;
    lockOwner     @9  :UInt64;
    pollEvents    @10 :UInt32;
    noflush       @11 :UInt64;
  }

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