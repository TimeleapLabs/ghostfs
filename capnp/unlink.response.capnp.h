// Generated by Cap'n Proto compiler, DO NOT EDIT
// source: unlink.response.capnp

#pragma once

#include <capnp/generated-header-support.h>
#include <kj/windows-sanity.h>
#if !CAPNP_LITE
#include <capnp/capability.h>
#endif  // !CAPNP_LITE

#if CAPNP_VERSION != 10002
#error "Version mismatch between generated code and library headers.  You must use the same version of the Cap'n Proto compiler and library."
#endif


CAPNP_BEGIN_HEADER

namespace capnp {
namespace schemas {

CAPNP_DECLARE_SCHEMA(cf560b3d781dc555);

}  // namespace schemas
}  // namespace capnp


struct UnlinkResponse {
  UnlinkResponse() = delete;

  class Reader;
  class Builder;
  class Pipeline;

  struct _capnpPrivate {
    CAPNP_DECLARE_STRUCT_HEADER(cf560b3d781dc555, 2, 0)
    #if !CAPNP_LITE
    static constexpr ::capnp::_::RawBrandedSchema const* brand() { return &schema->defaultBrand; }
    #endif  // !CAPNP_LITE
  };
};

// =======================================================================================

class UnlinkResponse::Reader {
public:
  typedef UnlinkResponse Reads;

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

  inline  ::int8_t getRes() const;

  inline  ::int8_t getErrno() const;

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

class UnlinkResponse::Builder {
public:
  typedef UnlinkResponse Builds;

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

  inline  ::int8_t getRes();
  inline void setRes( ::int8_t value);

  inline  ::int8_t getErrno();
  inline void setErrno( ::int8_t value);

private:
  ::capnp::_::StructBuilder _builder;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::ToDynamic_;
  friend class ::capnp::Orphanage;
  template <typename, ::capnp::Kind>
  friend struct ::capnp::_::PointerHelpers;
};

#if !CAPNP_LITE
class UnlinkResponse::Pipeline {
public:
  typedef UnlinkResponse Pipelines;

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

inline  ::uint64_t UnlinkResponse::Reader::getIno() const {
  return _reader.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}

inline  ::uint64_t UnlinkResponse::Builder::getIno() {
  return _builder.getDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS);
}
inline void UnlinkResponse::Builder::setIno( ::uint64_t value) {
  _builder.setDataField< ::uint64_t>(
      ::capnp::bounded<0>() * ::capnp::ELEMENTS, value);
}

inline  ::int8_t UnlinkResponse::Reader::getRes() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}

inline  ::int8_t UnlinkResponse::Builder::getRes() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS);
}
inline void UnlinkResponse::Builder::setRes( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<8>() * ::capnp::ELEMENTS, value);
}

inline  ::int8_t UnlinkResponse::Reader::getErrno() const {
  return _reader.getDataField< ::int8_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}

inline  ::int8_t UnlinkResponse::Builder::getErrno() {
  return _builder.getDataField< ::int8_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS);
}
inline void UnlinkResponse::Builder::setErrno( ::int8_t value) {
  _builder.setDataField< ::int8_t>(
      ::capnp::bounded<9>() * ::capnp::ELEMENTS, value);
}


CAPNP_END_HEADER

