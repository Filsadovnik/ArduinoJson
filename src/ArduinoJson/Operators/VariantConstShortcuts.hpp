// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Array/ArrayShortcuts.hpp>
#include <ArduinoJson/Object/ObjectConstShortcuts.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <typename TVariant>
class VariantConstShortcuts : public ObjectConstShortcuts<TVariant>,
                              public ArrayShortcuts<TVariant> {
 public:
  using ArrayShortcuts<TVariant>::operator[];
  using ObjectConstShortcuts<TVariant>::operator[];
};
}  // namespace ARDUINOJSON_NAMESPACE
