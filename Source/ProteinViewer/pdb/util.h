//
// Created by Konstantin Moskalenko on 23.11.2021.
//

#ifndef RIBBON_UTIL_H
#define RIBBON_UTIL_H


inline std::string parseString(
        const std::string &str,
        const std::string::size_type startPos,
        const std::string::size_type endPos
) {
    std::string sub = str.substr(startPos, endPos - startPos);

    // Trim whitespaces
    auto pred = [](unsigned char ch) { return !std::isspace(ch); };
    sub.erase(sub.begin(), std::find_if(sub.begin(), sub.end(), pred));
    sub.erase(std::find_if(sub.rbegin(), sub.rend(), pred).base(), sub.end());

    return sub;
}

inline int parseInt(
        const std::string &str,
        const std::string::size_type startPos,
        const std::string::size_type endPos
) {
    return std::stoi(parseString(str, startPos, endPos));
}

inline double parseFloat(
        const std::string &str,
        const std::string::size_type startPos,
        const std::string::size_type endPos
) {
    return std::stod(parseString(str, startPos, endPos));
}


#endif //RIBBON_UTIL_H
