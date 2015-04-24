/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/io/token_types_io.hpp"
#include "dogen/stitch/types/tokenization_error.hpp"
#include "dogen/stitch/types/tokenizer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.tokenizer"));

// const std::string new_line("\n");
// const std::string equals("=");

// const std::string unsupported_state("State is not supported: ");
// const std::string separator_not_found("Expected separator on kvp.");

}

namespace dogen {
namespace stitch {

tokenizer::tokenizer(const std::string& original_string)
    : original_string_(original_string),
      current_token_type_(token_types::invalid),
      position_(0) {

    BOOST_LOG_SEV(lg, debug) << "Tokeniser initialised with content: "
                             << original_string_;
}

token_types tokenizer::current_token_type() const {
    BOOST_LOG_SEV(lg, debug) << "Current token type: " << current_token_type_;
    return current_token_type_;
}

std::string tokenizer::current_token_content() const {
    BOOST_LOG_SEV(lg, debug) << "Current token content: "
                             << current_token_content_;
    return current_token_content_;
}

bool tokenizer::handle_new_line() {
    // const auto c(original_string_[position_]);
    // if (c == '\r') {
    //     if (position_ + 1 < len && original_string_[position_] == '\n')
    //         ++position_;
    // }

    // if (c == '\n') {
    //     current_token_type_ = token_types::eol;
    //     content_length_ = 0;
    //     ++position_;
    //     column_ = 0;
    //     ++line_;
    //     return true;
    // }
    return false;
}

bool tokenizer::handle_directive(const std::string& /*line*/) {
    // while (position_ < len) {

    // if (c =='<' && position_ + 2 < len &&
    //     original_string_[position_ + 1] == '#') {
    //     if (type == '@') {
    //         position_ += 3;
    return false;
}

std::string tokenizer::obtain_current_line() {
    // auto i(original_string_.find_first_of(position_, "\n"));
    // if (i std::string::npos)
    //     return original_string_.substr(position_);
    return std::string();
}

bool tokenizer::advance() {
    BOOST_LOG_SEV(lg, debug) << "Attempting to advance. Current position: "
                             << position_ << ". Length: "
                             << original_string_.length();

    // const auto len(original_string_.length());
    // if (position_ >= len) {
    //     BOOST_LOG_SEV(lg, debug) << "Already at the end.";
    //     return false;
    // }

    // BOOST_LOG_SEV(lg, debug) << "Starting advance.";
    // while (position_ < len) {
    //     if (handle_new_line())
    //         break;

    //     const auto line(obtain_current_line());
    // }
    return true;
}

} }
