@0xec6e6ddddb23b53a;

struct OpenResponse {
  ino   @0 :UInt64;
  fi    @1 :FuseFileInfo;
  res   @2 :Int8;
  errno @3 :UInt64;

  struct FuseFileInfo {
    flags         @0  :Int8;
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
}
