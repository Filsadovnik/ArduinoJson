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
    SECTION("can skip an integer") {
      checkJsonFilter("{\"an_integer\":666,answer:42}", "{\"answer\":true}",
                      "{\"answer\":42}");
    }

    SECTION("can skip a float") {
      checkJsonFilter("{\"a_float\":12.34e-6,answer:42}", "{\"answer\":true}",
                      "{\"answer\":42}");
    }

    SECTION("can skip a boolean") {
      checkJsonFilter("{\"a_bool\":false,answer:42}", "{\"answer\":true}",
                      "{\"answer\":42}");
    }

    SECTION("can skip a double-quoted string") {
      checkJsonFilter("{\"a_double_quoted_string\":\"hello\",answer:42}",
                      "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip a single-quoted string") {
      checkJsonFilter("{\"a_single_quoted_string\":'hello',answer:42}",
                      "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an empty array") {
      checkJsonFilter("{\"an_empty_array\":[],answer:42}", "{\"answer\":true}",
                      "{\"answer\":42}");
    }

    SECTION("can skip an empty array with spaces in it") {
      checkJsonFilter("{\"an_empty_array\":[\t],answer:42}",
                      "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an array") {
      checkJsonFilter("{\"an_array\":[1,2,3],answer:42}", "{\"answer\":true}",
                      "{\"answer\":42}");
    }

    SECTION("can skip an empty object") {
      checkJsonFilter("{\"an_empty_object\":{},answer:42}", "{\"answer\":true}",
                      "{\"answer\":42}");
    }

    SECTION("can skip an object") {
      checkJsonFilter("{\"an_empty_object\":{a:1,'b':2,\"c\":3},answer:42}",
                      "{\"answer\":true}", "{\"answer\":42}");
    }

    SECTION("can skip an object with spaces in it") {
      checkJsonFilter(
          "{\"an_empty_object\" : { a : 1 , 'b' : 2 , \"c\" : 3 } ,answer:42}",
          "{\"answer\":true}", "{\"answer\":42}");
    }
  }

  SECTION("{\"level1\":{\"level2\":true}}") {
    checkJsonFilter(
        "{\"an_integer\": 0,\"answer\":{\"type\":\"int\",\"value\":42}}",
        "{\"answer\":{\"value\":true}}", "{\"answer\":{\"value\":42}}");
  }
}
