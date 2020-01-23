// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

static void checkJsonFilter(std::string input, std::string filter_json,
                            std::string expected_json) {
  DynamicJsonDocument filter(256);
  DynamicJsonDocument doc(256);

  deserializeJson(filter, filter_json);

  DeserializationError err = deserializeJson(
      doc, input.c_str(), DeserializationOption::Filter(filter));

  REQUIRE(err == DeserializationError::Ok);
  REQUIRE(doc.as<std::string>() == expected_json);
}

TEST_CASE("Filtering") {
  SECTION("empty") {
    checkJsonFilter("{\"hello\":\"world\"}", "null", "null");
  }

  SECTION("false") {
    checkJsonFilter("{\"hello\":\"world\"}", "false", "null");
  }

  SECTION("true") {
    checkJsonFilter("{\"hello\":\"world\"}", "true", "{\"hello\":\"world\"}");
  }

  SECTION("{}") {
    checkJsonFilter("{\"hello\":\"world\"}", "{}", "{}");
  }

  SECTION("{\"key\":true}") {
    checkJsonFilter("{\"a\":1,\"b\":2,\"c\":3}", "{\"b\":true}", "{\"b\":2}");
  }

  SECTION("{\"key\":false}") {
    checkJsonFilter("{\"a\":false}", "{\"a\":false}", "{}");
  }
}
