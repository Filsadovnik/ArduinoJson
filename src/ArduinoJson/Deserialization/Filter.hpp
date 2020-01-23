// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Namespace.hpp>

namespace ARDUINOJSON_NAMESPACE {

struct Filter {
  Filter(JsonDocument& d) : doc(d) {}

  JsonDocument& doc;
};

}  // namespace ARDUINOJSON_NAMESPACE
