#pragma once

/* Basically a raw string literal is a string in which the escape characters (like \n \t or \" )
 * of C++ are not processed. A raw string literal starts with R"<delimiter>( and ends in )<delimiter>"
 * <delimeter> is optional
 *
 * A first application of the concept of a raw string is in simplifying the syntax of
 * the regular expressions. The coder can put his effort in writing a regular expression
 * conformal to the ECMAScript standard and not in ensuring that his regular expression
 * will be correctly processed by the compiler.
 */

#include <string>
#include <iostream>
#include <regex>

/* Note -
 * ----
 * The null character ('\0', L'\0', char16_t(), etc) is always appended to
 * the string literal: thus, a string literal "Hello" is a const char[6]
 * holding the characters 'H', 'e', 'l', 'l', 'o', and '\0'.
 */

int main () {
    std::regex integer ("(\\+|-)?[[:digit:]]+"); //using normal string literal
    std::regex integer_raw (R"((\+|-)?[[:digit:]]+)"); //using raw string literal, \\->\

    std::string inStr = "agfdg 345iu 78jhjh09kkk88";
    if (std::regex_search(inStr, integer_raw)) {
        std::cout << "Integer found!" << std::endl;
        auto it = std::sregex_iterator(inStr.begin(), inStr.end(), integer_raw);
        auto eit = std::sregex_iterator();
        for (;it != eit;++it) {
             std::smatch match = (*it);
             std::cout << match.str() << std::endl;
        }
    }
    else std::cout << "Integer NOT found!" << std::endl;

    std::string raw_str = R"(This is a raw string with delimiter, can still contain (" \n )";
    /*
     * Below ### is delimiter this is optional
     * when is it mandatory?
     * It is mandatory when your string contains )"
     * consider raw_str2
     */
    std::string raw_str2 = R"###(This is a raw string with )")###";
    std::cout << raw_str << std::endl;
    std::cout << raw_str2 << std::endl;
}
