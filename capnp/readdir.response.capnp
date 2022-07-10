@0xf2f589d21924da65;

struct ReaddirResponse {
  uuid      @0 :Text;
  res       @1 :Int8;
  dirbuf    @2 :Dirbuf;

  struct Dirbuf {
    p     @0  :Text;  
    size  @1  :UInt64;
  }

}
