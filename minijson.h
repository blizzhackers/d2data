/**
 * Minimal JSON DOM reader, enough for the population sim output.
 * Objects keep their key order. Throws std::runtime_error on malformed input.
 */

#pragma once

#include <cstdlib>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace MiniJson {

    struct Value {
        enum Type { Null, Bool, Number, String, Array, Object };

        Type type = Null;
        bool b = false;
        double num = 0;
        std::string str;
        std::vector<Value> arr;
        std::vector<std::pair<std::string, Value>> obj;

        bool isObject() const { return type == Object; }
        bool isArray() const { return type == Array; }
        bool isNull() const { return type == Null; }

        // Returns nullptr when the key is absent or this isn't an object.
        const Value* get(const std::string& key) const {
            if (type != Object) {
                return nullptr;
            }
            for (const auto& [k, v] : obj) {
                if (k == key) {
                    return &v;
                }
            }
            return nullptr;
        }

        double number(const std::string& key, double fallback = 0) const {
            const Value* v = get(key);
            return v && v->type == Number ? v->num : fallback;
        }

        std::string string(const std::string& key) const {
            const Value* v = get(key);
            return v && v->type == String ? v->str : std::string();
        }
    };

    class Reader {
    public:
        explicit Reader(const std::string& text) : s(text) {}

        Value parse() {
            Value v = value();
            ws();
            if (pos != s.size()) {
                fail("trailing data");
            }
            return v;
        }

    private:
        const std::string& s;
        size_t pos = 0;

        [[noreturn]] void fail(const char* what) {
            throw std::runtime_error(std::string("JSON parse error: ") + what + " at offset " + std::to_string(pos));
        }

        void ws() {
            while (pos < s.size() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r' || s[pos] == '\t')) {
                pos++;
            }
        }

        bool lit(const char* word) {
            size_t n = 0;
            while (word[n]) {
                n++;
            }
            if (s.compare(pos, n, word) == 0) {
                pos += n;
                return true;
            }
            return false;
        }

        std::string string() {
            if (s[pos] != '"') {
                fail("expected string");
            }
            pos++;
            std::string out;
            while (pos < s.size() && s[pos] != '"') {
                char ch = s[pos++];
                if (ch != '\\') {
                    out += ch;
                    continue;
                }
                if (pos >= s.size()) {
                    fail("bad escape");
                }
                char e = s[pos++];
                switch (e) {
                    case 'n': out += '\n'; break;
                    case 't': out += '\t'; break;
                    case 'r': out += '\r'; break;
                    case 'b': out += '\b'; break;
                    case 'f': out += '\f'; break;
                    case 'u': {
                        if (pos + 4 > s.size()) {
                            fail("bad unicode escape");
                        }
                        unsigned code = std::stoul(s.substr(pos, 4), nullptr, 16);
                        pos += 4;
                        // Names here are ASCII; encode anything else as UTF-8 for completeness.
                        if (code < 0x80) {
                            out += static_cast<char>(code);
                        }
                        else if (code < 0x800) {
                            out += static_cast<char>(0xC0 | (code >> 6));
                            out += static_cast<char>(0x80 | (code & 0x3F));
                        }
                        else {
                            out += static_cast<char>(0xE0 | (code >> 12));
                            out += static_cast<char>(0x80 | ((code >> 6) & 0x3F));
                            out += static_cast<char>(0x80 | (code & 0x3F));
                        }
                        break;
                    }
                    default: out += e; break;
                }
            }
            if (pos >= s.size()) {
                fail("unterminated string");
            }
            pos++;
            return out;
        }

        Value value() {
            ws();
            if (pos >= s.size()) {
                fail("unexpected end");
            }
            Value v;
            char ch = s[pos];
            if (ch == '{') {
                v.type = Value::Object;
                pos++;
                ws();
                if (s[pos] == '}') {
                    pos++;
                    return v;
                }
                for (;;) {
                    ws();
                    std::string key = string();
                    ws();
                    if (s[pos] != ':') {
                        fail("expected ':'");
                    }
                    pos++;
                    v.obj.emplace_back(std::move(key), value());
                    ws();
                    if (s[pos] == ',') {
                        pos++;
                        continue;
                    }
                    if (s[pos] == '}') {
                        pos++;
                        return v;
                    }
                    fail("expected ',' or '}'");
                }
            }
            if (ch == '[') {
                v.type = Value::Array;
                pos++;
                ws();
                if (s[pos] == ']') {
                    pos++;
                    return v;
                }
                for (;;) {
                    v.arr.push_back(value());
                    ws();
                    if (s[pos] == ',') {
                        pos++;
                        continue;
                    }
                    if (s[pos] == ']') {
                        pos++;
                        return v;
                    }
                    fail("expected ',' or ']'");
                }
            }
            if (ch == '"') {
                v.type = Value::String;
                v.str = string();
                return v;
            }
            if (lit("true")) {
                v.type = Value::Bool;
                v.b = true;
                return v;
            }
            if (lit("false")) {
                v.type = Value::Bool;
                return v;
            }
            if (lit("null")) {
                return v;
            }
            const char* start = s.c_str() + pos;
            char* end = nullptr;
            v.num = std::strtod(start, &end);
            if (end == start) {
                fail("unexpected character");
            }
            v.type = Value::Number;
            pos += static_cast<size_t>(end - start);
            return v;
        }
    };

    inline Value parseFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open " + filename);
        }
        std::stringstream ss;
        ss << file.rdbuf();
        std::string text = ss.str();
        return Reader(text).parse();
    }

}
