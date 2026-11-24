/**
 * Evaluator for the calc expressions used in the .txt files, such as
 * "(skill('Fire Ball'.blvl)+skill('Meteor'.blvl))*par8" or "min(24,ln12)".
 *
 * Arithmetic is integer, like the game's: division truncates toward zero and
 * division by zero yields 0. The parser is tolerant of a missing closing
 * parenthesis at the end of an expression, which occurs in the shipped data
 * (Fire Wall's EDmgSymPerCalc).
 */

#pragma once

#include <cctype>
#include <cstdint>
#include <functional>
#include <string>

namespace D2Calc {

    struct Context {
        // Resolves a bare identifier: par1, lvl, blvl, ln12, dm34, clc1, ...
        std::function<int64_t(const std::string& name)> ident;
        // Resolves a reference call: skill('Name'.blvl), miss('name'.rang), stat('name'.accr).
        std::function<int64_t(const std::string& fn, const std::string& arg, const std::string& prop)> ref;
    };

    class Parser {
    public:
        Parser(const std::string& text, const Context& ctx) : s(text), c(ctx) {}

        int64_t run() {
            skip();
            if (pos >= s.size()) {
                return 0;
            }
            return ternary();
        }

    private:
        const std::string& s;
        const Context& c;
        size_t pos = 0;

        // Cells containing commas are wrapped in double quotes in the .txt
        // files ("min(24,ln12)"); treat those quotes as whitespace.
        void skip() {
            while (pos < s.size() && (std::isspace(static_cast<unsigned char>(s[pos])) || s[pos] == '"')) {
                pos++;
            }
        }

        bool eat(const char* op) {
            skip();
            size_t n = 0;
            while (op[n]) {
                n++;
            }
            if (s.compare(pos, n, op) == 0) {
                pos += n;
                return true;
            }
            return false;
        }

        int64_t ternary() {
            int64_t v = logical();
            if (eat("?")) {
                int64_t a = ternary();
                eat(":");
                int64_t b = ternary();
                return v ? a : b;
            }
            return v;
        }

        int64_t logical() {
            int64_t v = comparison();
            for (;;) {
                if (eat("&&")) {
                    int64_t r = comparison();
                    v = (v && r) ? 1 : 0;
                }
                else if (eat("||")) {
                    int64_t r = comparison();
                    v = (v || r) ? 1 : 0;
                }
                else {
                    return v;
                }
            }
        }

        int64_t comparison() {
            int64_t v = additive();
            for (;;) {
                if (eat("<=")) { v = v <= additive(); }
                else if (eat(">=")) { v = v >= additive(); }
                else if (eat("==")) { v = v == additive(); }
                else if (eat("!=")) { v = v != additive(); }
                else if (eat("<")) { v = v < additive(); }
                else if (eat(">")) { v = v > additive(); }
                else { return v; }
            }
        }

        int64_t additive() {
            int64_t v = term();
            for (;;) {
                if (eat("+")) { v += term(); }
                else if (eat("-")) { v -= term(); }
                else { return v; }
            }
        }

        int64_t term() {
            int64_t v = unary();
            for (;;) {
                if (eat("*")) {
                    v *= unary();
                }
                else if (eat("/")) {
                    int64_t d = unary();
                    v = d ? v / d : 0;
                }
                else if (eat("%")) {
                    int64_t d = unary();
                    v = d ? v % d : 0;
                }
                else {
                    return v;
                }
            }
        }

        int64_t unary() {
            if (eat("-")) {
                return -unary();
            }
            if (eat("+")) {
                return unary();
            }
            return primary();
        }

        std::string word() {
            skip();
            size_t start = pos;
            while (pos < s.size() && (std::isalnum(static_cast<unsigned char>(s[pos])) || s[pos] == '_')) {
                pos++;
            }
            return s.substr(start, pos - start);
        }

        int64_t primary() {
            skip();
            if (pos >= s.size()) {
                return 0;
            }

            if (eat("(")) {
                int64_t v = ternary();
                eat(")"); // Tolerates a missing ')'.
                return v;
            }

            if (std::isdigit(static_cast<unsigned char>(s[pos]))) {
                int64_t v = 0;
                while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos]))) {
                    v = v * 10 + (s[pos] - '0');
                    pos++;
                }
                return v;
            }

            std::string name = word();
            if (name.empty()) {
                pos++; // Skip an unexpected character rather than looping forever.
                return 0;
            }

            if (!eat("(")) {
                return c.ident ? c.ident(name) : 0;
            }

            skip();
            if (pos < s.size() && s[pos] == '\'') {
                // name('Arg'.prop)
                pos++;
                size_t start = pos;
                while (pos < s.size() && s[pos] != '\'') {
                    pos++;
                }
                std::string arg = s.substr(start, pos - start);
                if (pos < s.size()) {
                    pos++;
                }
                std::string prop;
                if (eat(".")) {
                    prop = word();
                }
                eat(")");
                return c.ref ? c.ref(name, arg, prop) : 0;
            }

            int64_t a = ternary();
            int64_t b = 0;
            bool two = false;
            if (eat(",")) {
                b = ternary();
                two = true;
            }
            eat(")");

            if (name == "min") {
                return two ? (a < b ? a : b) : a;
            }
            if (name == "max") {
                return two ? (a > b ? a : b) : a;
            }
            return 0;
        }
    };

    inline int64_t eval(const std::string& expr, const Context& ctx) {
        return Parser(expr, ctx).run();
    }

    // "ln12" style linear and "dm12" style diminishing parameter pairs, as
    // defined in skillcalc.txt.
    inline int64_t linear(int64_t a, int64_t b, int64_t lvl) {
        return a + (lvl - 1) * b;
    }

    inline int64_t diminishing(int64_t a, int64_t b, int64_t lvl) {
        int64_t d = 100 * (lvl + 6);
        return d ? ((110 * lvl) * (b - a)) / d + a : a;
    }

}
