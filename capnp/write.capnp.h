// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: write.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(931883f8920c7515);
CAPNP_DECLARE_SCHEMA(8b019c210166c03d);

}  // namespace schemas
}  // namespace capnp


struct Write {
  Write() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct FuseFileInfo;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(931883f8920c7515, 3, 3)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct Write::FuseFileInfo {
  FuseFileInfo() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(8b019c210166c03d, 11, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class Write::Reader {
public:
  typedef Write Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::uint64_t getIno() const;

  inline bool hasBuf() const;
  inline  ::capnp::Text::Reader getBuf() const;

  inline  ::uint64_t getSize() const;

  inline  ::int64_t getOff() const;

  inline bool hasFi() const;
  inline  ::Write::FuseFileInfo::Reader getFi() const;

  inline bool hasUuid() const;
  inline  ::capnp::Text::Reader getUuid() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Write::Builder {
public:
  typedef Write Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::uint64_t getIno();
  inline void setIno( ::uint64_t value);

  inline bool hasBuf();
  inline  ::capnp::Text::Builder getBuf();
  inline void setBuf( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initBuf(unsigned int size);
  inline void adoptBuf(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownBuf();

  inline  ::uint64_t getSize();
  inline void setSize( ::uint64_t value);

  inline  ::int64_t getOff();
  inline void setOff( ::int64_t value);

  inline bool hasFi();
  inline  ::Write::FuseFileInfo::Builder getFi();
  inline void setFi( ::Write::FuseFileInfo::Reader value);
  inline  ::Write::FuseFileInfo::Builder initFi();
  inline void adoptFi(::capnp::Orphan< ::Write::FuseFileInfo>&& value);
  inline ::capnp::Orphan< ::Write::FuseFileInfo> disownFi();

  inline bool hasUuid();
  inline  ::capnp::Text::Builder getUuid();
  inline void setUuid( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initUuid(unsigned int size);
  inline void adoptUuid(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownUuid();

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Write::Pipeline {
public:
  typedef Write Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::Write::FuseFileInfo::Pipeline getFi();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class Write::FuseFileInfo::Reader {
public:
  typedef FuseFileInfo Reads;

  Reader() = default;
  inline explicit Reader(::capnp::_::StructReader base): _reader(base) {}

  inline ::capnp::MessageSize totalSize() const {
    return _reader.totalSize().asPublic();
  }

#if !CAPNP_LITE
  inline ::kj::StringTree toString() const {
    return ::capnp::_::structString(_reader, *_capnpPrivate::brand());
  }
#endif  // !CAPNP_LITE

  inline  ::int8_t getFlags() const;

  inline  ::uint64_t getWritepage() const;

  inline  ::uint64_t getDirectIo() const;

  inline  ::uint64_t getKeepCache() const;

  inline  ::uint64_t getFlush() const;

  inline  ::uint64_t getNonseekable() const;

  inline  ::uint64_t getCacheReaddir() const;

  inline  ::uint64_t getPadding() const;

  inline  ::uint64_t getFh() const;

  inline  ::uint64_t getLockOwner() const;

  inline  ::uint32_t getPollEvents() const;

  inline  ::uint64_t getNoflush() const;

private:
  ::capnp::_::StructReader _reader;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::List;
  friend class ::capnp::MessageBuilder;
  friend class ::capnp::Orphanage;
};

class Write::FuseFileInfo::Builder {
public:
  typedef FuseFileInfo Builds;

  Builder() = delete;  // Deleted to discourage incorrect usage.
                       // You can explicitly initialize to nullptr instead.
  inline Builder(decltype(nullptr)) {}
  inline explicit Builder(::capnp::_::StructBuilder base): _builder(base) {}
  inline operator Reader() const { return Reader(_builder.asReader()); }
  inline Reader asReader() const { return *this; }

  inline ::capnp::MessageSize totalSize() const { return asReader().totalSize(); }
#if !CAPNP_LITE
  inline ::kj::StringTree toString() const { return asReader().toString(); }
#endif  // !CAPNP_LITE

  inline  ::int8_t getFlags();
  inline void setFlags( ::int8_t value);

  inline  ::uint64_t getWritepage();
  inline void setWritepage( ::uint64_t value);

  inline  ::uint64_t getDirectIo();
  inline void setDirectIo( ::uint64_t value);

  inline  ::uint64_t getKeepCache();
  inline void setKeepCache( ::uint64_t value);

  inline  ::uint64_t getFlush();
  inline void setFlush( ::uint64_t value);

  inline  ::uint64_t getNonseekable();
  inline void setNonseekable( ::uint64_t value);

  inline  ::uint64_t getCacheReaddir();
  inline void setCacheReaddir( ::uint64_t value);

  inline  ::uint64_t getPadding();
  inline void setPadding( ::uint64_t value);

  inline  ::uint64_t getFh();
  inline void setFh( ::uint64_t value);

  inline  ::uint64_t getLockOwner();
  inline void setLockOwner( ::uint64_t value);

  inline  ::uint32_t getPollEvents();
  inline void setPollEvents( ::uint32_t value);

  inline  ::uint64_t getNoflush();
  inline void setNoflush( ::uint64_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class Write::FuseFileInfo::Pipeline {
public:
  typedef FuseFileInfo Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

// =======================================================================================

inline  ::uint64_t Write::Reader::getIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::Builder::getIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Write::Builder::setIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline bool Write::Reader::hasBuf() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool Write::Builder::hasBuf() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader Write::Reader::getBuf() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder Write::Builder::getBuf() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void Write::Builder::setBuf( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder Write::Builder::initBuf(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), size);
}
inline void Write::Builder::adoptBuf(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> Write::Builder::disownBuf() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline  ::uint64_t Write::Reader::getSize() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::Builder::getSize() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Write::Builder::setSize( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t Write::Reader::getOff() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::int64_t Write::Builder::getOff() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Write::Builder::setOff( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline bool Write::Reader::hasFi() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool Write::Builder::hasFi() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::Write::FuseFileInfo::Reader Write::Reader::getFi() const {
  return ::capnp::_::PointerHelpers< ::Write::FuseFileInfo>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::Write::FuseFileInfo::Builder Write::Builder::getFi() {
  return ::capnp::_::PointerHelpers< ::Write::FuseFileInfo>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::Write::FuseFileInfo::Pipeline Write::Pipeline::getFi() {
  return  ::Write::FuseFileInfo::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void Write::Builder::setFi( ::Write::FuseFileInfo::Reader value) {
  ::capnp::_::PointerHelpers< ::Write::FuseFileInfo>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::Write::FuseFileInfo::Builder Write::Builder::initFi() {
  return ::capnp::_::PointerHelpers< ::Write::FuseFileInfo>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void Write::Builder::adoptFi(
    ::capnp::Orphan< ::Write::FuseFileInfo>&& value) {
  ::capnp::_::PointerHelpers< ::Write::FuseFileInfo>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::Write::FuseFileInfo> Write::Builder::disownFi() {
  return ::capnp::_::PointerHelpers< ::Write::FuseFileInfo>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline bool Write::Reader::hasUuid() const {
  return !_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline bool Write::Builder::hasUuid() {
  return !_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader Write::Reader::getUuid() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder Write::Builder::getUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}
inline void Write::Builder::setUuid( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder Write::Builder::initUuid(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), size);
}
inline void Write::Builder::adoptUuid(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> Write::Builder::disownUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<2>() * ::capnp::POINTERS));
}

inline  ::int8_t Write::FuseFileInfo::Reader::getFlags() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int8_t Write::FuseFileInfo::Builder::getFlags() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setFlags( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getWritepage() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getWritepage() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setWritepage( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getDirectIo() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getDirectIo() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setDirectIo( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getKeepCache() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getKeepCache() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setKeepCache( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getFlush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getFlush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setFlush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getNonseekable() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getNonseekable() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setNonseekable( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getCacheReaddir() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getCacheReaddir() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setCacheReaddir( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getPadding() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getPadding() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setPadding( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getFh() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getFh() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setFh( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getLockOwner() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getLockOwner() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setLockOwner( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline  ::uint32_t Write::FuseFileInfo::Reader::getPollEvents() const {
  return _reader.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint32_t Write::FuseFileInfo::Builder::getPollEvents() {
  return _builder.getDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setPollEvents( ::uint32_t value) {
  _builder.setDataField< ::uint32_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t Write::FuseFileInfo::Reader::getNoflush() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t Write::FuseFileInfo::Builder::getNoflush() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void Write::FuseFileInfo::Builder::setNoflush( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

