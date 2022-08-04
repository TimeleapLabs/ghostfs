@0xa8566d6a8911c127;

struct TokenRequest {
  user    @0 :Text;
  token   @1 :Text;
  retries @2 :Int64;
  expires @3 :UInt64;
}