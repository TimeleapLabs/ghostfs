#include <ghostfs/uuid.h>
#include <uuid_v4.h>

UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

std::string gen_uuid() {
  UUIDv4::UUID uuid = uuidGenerator.getUUID();
  return uuid.str();
}
