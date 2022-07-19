// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: getattr.response.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(dd821ab072c02b16);
CAPNP_DECLARE_SCHEMA(83b19428b48c1bec);

}  // namespace schemas
}  // namespace capnp


struct GetattrResponse {
  GetattrResponse() = delete;

  class Reader;
  class Builder;
  class Pipeline;
  struct Attr;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(dd821ab072c02b16, 1, 2)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

struct GetattrResponse::Attr {
  Attr() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(83b19428b48c1bec, 11, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class GetattrResponse::Reader {
public:
  typedef GetattrResponse Reads;

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

  inline bool hasUuid() const;
  inline  ::capnp::Text::Reader getUuid() const;

  inline bool hasAttr() const;
  inline  ::GetattrResponse::Attr::Reader getAttr() const;

  inline  ::int8_t getRes() const;

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

class GetattrResponse::Builder {
public:
  typedef GetattrResponse Builds;

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

  inline bool hasUuid();
  inline  ::capnp::Text::Builder getUuid();
  inline void setUuid( ::capnp::Text::Reader value);
  inline  ::capnp::Text::Builder initUuid(unsigned int size);
  inline void adoptUuid(::capnp::Orphan< ::capnp::Text>&& value);
  inline ::capnp::Orphan< ::capnp::Text> disownUuid();

  inline bool hasAttr();
  inline  ::GetattrResponse::Attr::Builder getAttr();
  inline void setAttr( ::GetattrResponse::Attr::Reader value);
  inline  ::GetattrResponse::Attr::Builder initAttr();
  inline void adoptAttr(::capnp::Orphan< ::GetattrResponse::Attr>&& value);
  inline ::capnp::Orphan< ::GetattrResponse::Attr> disownAttr();

  inline  ::int8_t getRes();
  inline void setRes( ::int8_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class GetattrResponse::Pipeline {
public:
  typedef GetattrResponse Pipelines;

  inline Pipeline(decltype(nullptr)): _typeless(nullptr) {}
  inline explicit Pipeline(::capnp::AnyPointer::Pipeline&& typeless)
      : _typeless(kj::mv(typeless)) {}

  inline  ::GetattrResponse::Attr::Pipeline getAttr();
private:
  ::capnp::AnyPointer::Pipeline _typeless;
  friend class ::capnp::PipelineHook;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
};
#endif  // !CAPNP_LITE

class GetattrResponse::Attr::Reader {
public:
  typedef Attr Reads;

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

  inline  ::uint16_t getStDev() const;

  inline  ::uint64_t getStIno() const;

  inline  ::uint64_t getStMode() const;

  inline  ::uint16_t getStNlink() const;

  inline  ::int64_t getStUid() const;

  inline  ::int64_t getStGid() const;

  inline  ::uint16_t getStRdev() const;

  inline  ::int64_t getStSize() const;

  inline  ::int64_t getStAtime() const;

  inline  ::int64_t getStMtime() const;

  inline  ::int64_t getStCtime() const;

  inline  ::uint64_t getStBlksize() const;

  inline  ::uint64_t getStBlocks() const;

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

class GetattrResponse::Attr::Builder {
public:
  typedef Attr Builds;

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

  inline  ::uint16_t getStDev();
  inline void setStDev( ::uint16_t value);

  inline  ::uint64_t getStIno();
  inline void setStIno( ::uint64_t value);

  inline  ::uint64_t getStMode();
  inline void setStMode( ::uint64_t value);

  inline  ::uint16_t getStNlink();
  inline void setStNlink( ::uint16_t value);

  inline  ::int64_t getStUid();
  inline void setStUid( ::int64_t value);

  inline  ::int64_t getStGid();
  inline void setStGid( ::int64_t value);

  inline  ::uint16_t getStRdev();
  inline void setStRdev( ::uint16_t value);

  inline  ::int64_t getStSize();
  inline void setStSize( ::int64_t value);

  inline  ::int64_t getStAtime();
  inline void setStAtime( ::int64_t value);

  inline  ::int64_t getStMtime();
  inline void setStMtime( ::int64_t value);

  inline  ::int64_t getStCtime();
  inline void setStCtime( ::int64_t value);

  inline  ::uint64_t getStBlksize();
  inline void setStBlksize( ::uint64_t value);

  inline  ::uint64_t getStBlocks();
  inline void setStBlocks( ::uint64_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class GetattrResponse::Attr::Pipeline {
public:
  typedef Attr Pipelines;

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

inline bool GetattrResponse::Reader::hasUuid() const {
  return !_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline bool GetattrResponse::Builder::hasUuid() {
  return !_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS).isNull();
}
inline  ::capnp::Text::Reader GetattrResponse::Reader::getUuid() const {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_reader.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline  ::capnp::Text::Builder GetattrResponse::Builder::getUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::get(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}
inline void GetattrResponse::Builder::setUuid( ::capnp::Text::Reader value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::set(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), value);
}
inline  ::capnp::Text::Builder GetattrResponse::Builder::initUuid(unsigned int size) {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::init(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), size);
}
inline void GetattrResponse::Builder::adoptUuid(
    ::capnp::Orphan< ::capnp::Text>&& value) {
  ::capnp::_::PointerHelpers< ::capnp::Text>::adopt(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::capnp::Text> GetattrResponse::Builder::disownUuid() {
  return ::capnp::_::PointerHelpers< ::capnp::Text>::disown(_builder.getPointerField(
      ::capnp::bounded<0>() * ::capnp::POINTERS));
}

inline bool GetattrResponse::Reader::hasAttr() const {
  return !_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline bool GetattrResponse::Builder::hasAttr() {
  return !_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS).isNull();
}
inline  ::GetattrResponse::Attr::Reader GetattrResponse::Reader::getAttr() const {
  return ::capnp::_::PointerHelpers< ::GetattrResponse::Attr>::get(_reader.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline  ::GetattrResponse::Attr::Builder GetattrResponse::Builder::getAttr() {
  return ::capnp::_::PointerHelpers< ::GetattrResponse::Attr>::get(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
#if !CAPNP_LITE
inline  ::GetattrResponse::Attr::Pipeline GetattrResponse::Pipeline::getAttr() {
  return  ::GetattrResponse::Attr::Pipeline(_typeless.getPointerField(1));
}
#endif  // !CAPNP_LITE
inline void GetattrResponse::Builder::setAttr( ::GetattrResponse::Attr::Reader value) {
  ::capnp::_::PointerHelpers< ::GetattrResponse::Attr>::set(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), value);
}
inline  ::GetattrResponse::Attr::Builder GetattrResponse::Builder::initAttr() {
  return ::capnp::_::PointerHelpers< ::GetattrResponse::Attr>::init(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}
inline void GetattrResponse::Builder::adoptAttr(
    ::capnp::Orphan< ::GetattrResponse::Attr>&& value) {
  ::capnp::_::PointerHelpers< ::GetattrResponse::Attr>::adopt(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS), kj::mv(value));
}
inline ::capnp::Orphan< ::GetattrResponse::Attr> GetattrResponse::Builder::disownAttr() {
  return ::capnp::_::PointerHelpers< ::GetattrResponse::Attr>::disown(_builder.getPointerField(
      ::capnp::bounded<1>() * ::capnp::POINTERS));
}

inline  ::int8_t GetattrResponse::Reader::getRes() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::int8_t GetattrResponse::Builder::getRes() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Builder::setRes( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint16_t GetattrResponse::Attr::Reader::getStDev() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t GetattrResponse::Attr::Builder::getStDev() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStDev( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t GetattrResponse::Attr::Reader::getStIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t GetattrResponse::Attr::Builder::getStIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t GetattrResponse::Attr::Reader::getStMode() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t GetattrResponse::Attr::Builder::getStMode() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStMode( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::uint16_t GetattrResponse::Attr::Reader::getStNlink() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t GetattrResponse::Attr::Builder::getStNlink() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStNlink( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<1>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t GetattrResponse::Attr::Reader::getStUid() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}

inline  ::int64_t GetattrResponse::Attr::Builder::getStUid() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStUid( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<3>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t GetattrResponse::Attr::Reader::getStGid() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}

inline  ::int64_t GetattrResponse::Attr::Builder::getStGid() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStGid( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<4>() * ::capnp::ELEMENTS, value);
}

inline  ::uint16_t GetattrResponse::Attr::Reader::getStRdev() const {
  return _reader.getDataField< ::uint16_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}

inline  ::uint16_t GetattrResponse::Attr::Builder::getStRdev() {
  return _builder.getDataField< ::uint16_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStRdev( ::uint16_t value) {
  _builder.setDataField< ::uint16_t>(
      ::capnp::bounded<2>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t GetattrResponse::Attr::Reader::getStSize() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}

inline  ::int64_t GetattrResponse::Attr::Builder::getStSize() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStSize( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<5>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t GetattrResponse::Attr::Reader::getStAtime() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}

inline  ::int64_t GetattrResponse::Attr::Builder::getStAtime() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStAtime( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<6>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t GetattrResponse::Attr::Reader::getStMtime() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}

inline  ::int64_t GetattrResponse::Attr::Builder::getStMtime() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStMtime( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<7>() * ::capnp::ELEMENTS, value);
}

inline  ::int64_t GetattrResponse::Attr::Reader::getStCtime() const {
  return _reader.getDataField< ::int64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::int64_t GetattrResponse::Attr::Builder::getStCtime() {
  return _builder.getDataField< ::int64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStCtime( ::int64_t value) {
  _builder.setDataField< ::int64_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t GetattrResponse::Attr::Reader::getStBlksize() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t GetattrResponse::Attr::Builder::getStBlksize() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStBlksize( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}

inline  ::uint64_t GetattrResponse::Attr::Reader::getStBlocks() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t GetattrResponse::Attr::Builder::getStBlocks() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS);
}
inline void GetattrResponse::Attr::Builder::setStBlocks( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<10>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

