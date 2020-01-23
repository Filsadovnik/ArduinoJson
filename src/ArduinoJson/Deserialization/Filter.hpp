// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Namespace.hpp>

namespace ARDUINOJSON_NAMESPACE {

class Filter {
 public:
  explicit Filter(VariantConstRef v) : _variant(v) {}

  bool operator==(bool rhs) const {
    return rhs == true;
  }

  template <typename TKey>
  Filter operator[](const TKey& key) const {
    if (_variant == true)
      return Filter(_variant);  // accept all children
    else
      return Filter(_variant[key]);
  }

  operator bool() const {
    return _variant;
  }

 private:
  VariantConstRef _variant;
};

struct AllowAllFilter {
  bool operator==(bool rhs) const {
    return rhs == true;
  }

  template <typename TKey>
  AllowAllFilter operator[](const TKey&) const {
    return AllowAllFilter();
  }

  operator bool() const {
    return true;
  }
};

}  // namespace ARDUINOJSON_NAMESPACE
