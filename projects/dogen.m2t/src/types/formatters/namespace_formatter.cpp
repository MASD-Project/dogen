/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.logical/io/entities/technical_space_io.hpp"
#include "dogen.m2t/types/formatters/formatting_error.hpp"
#include "dogen.m2t/types/formatters/namespace_formatter.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("m2t.formatters.namespace_formatter"));

const std::string empty;
const std::string dot(".");
const std::string colon("::");
const std::string namespace_keyword("namespace ");
const std::string using_keyword("using ");

const std::string empty_namespace(
    "Technical space does not support empty namespaces: ");
const std::string invalid_technical_space(
    "Invalid or unsupported technical space: ");

}

namespace dogen::m2t::formatters {

namespace_formatter::namespace_formatter(std::ostream& s,
    const logical::entities::technical_space ts,
    const std::list<std::string>& ns,
    const bool add_new_line, const bool use_nesting)
    : stream_(s), technical_space_(ts), namespaces_(ns),
      add_new_line_(add_new_line),
      use_nesting_(use_nesting) {

    BOOST_LOG_SEV(lg, trace) << "Dumping initial configuration."
                             << " technical space: " << ts
                             << " namespaces: " << ns
                             << " add_new_line: " << add_new_line
                             << " use_nesting: " << use_nesting;
}

namespace_formatter::namespace_formatter(std::ostream& s,
    const logical::entities::technical_space ts,
    const std::string& ns,
    const bool add_new_line, const bool use_nesting)
    : namespace_formatter(s, ts,
        ns.empty() ? std::list<std::string> { }: std::list<std::string> { ns },
        add_new_line, use_nesting) {}

namespace_formatter::namespace_formatter(std::ostream& s,
    const logical::entities::technical_space ts,
    const bool add_new_line, const bool use_nesting)
    : namespace_formatter(s, ts, std::list<std::string> { },
        add_new_line, use_nesting) {}

void namespace_formatter::format_cpp_begin() {
    /*
     * Anonymous namespace.
     */
    if (namespaces_.empty()) {
        stream_ << namespace_keyword << "{" << std::endl;
        return;
    }

    /*
     * Single namespace, Multiple namespaces, with nesting.
     */
    if (namespaces_.size() == 1 || use_nesting_) {
        const auto joined(boost::algorithm::join(namespaces_, colon));
        stream_ << namespace_keyword << joined << " {" << std::endl;
        return;
    }

    /*
     * Multiple namespaces, without nesting.
     */
    for (auto ns : namespaces_)
        stream_ << namespace_keyword << ns << " {" << std::endl;
}

void namespace_formatter::format_csharp_begin() {
    if (namespaces_.empty()) {
        const auto s(boost::lexical_cast<std::string>(technical_space_));
        BOOST_LOG_SEV(lg, error) << empty_namespace << s;
        BOOST_THROW_EXCEPTION(formatting_error(empty_namespace + s));
    }

    const auto joined(boost::algorithm::join(namespaces_, dot));
    stream_ << namespace_keyword << joined << std::endl
            << "{" << std::endl;
}

void namespace_formatter::format_cpp_end() {
    if (namespaces_.empty() || use_nesting_ || namespaces_.size() == 1) {
        stream_ << "}";

        if (add_new_line_)
            stream_ << std::endl;

        return;
    }

    /*
     * Multiple namespaces, without nesting.
     */
    bool first(true);
    for (auto ns : namespaces_) {
        if (!first)
            stream_ << " ";

        stream_ << "}";
        first = false;
    }

    if (add_new_line_)
        stream_ << std::endl;
}


void namespace_formatter::format_csharp_end() {
    if (namespaces_.empty()) {
        const auto s(boost::lexical_cast<std::string>(technical_space_));
        BOOST_LOG_SEV(lg, error) << empty_namespace << s;
        BOOST_THROW_EXCEPTION(formatting_error(empty_namespace + s));
    }

    stream_ << "}" << std::endl;
}

void namespace_formatter::format_begin() {
    BOOST_LOG_SEV(lg, trace) << "Beginning namespace.";
    using logical::entities::technical_space;
    switch(technical_space_) {
    case technical_space::cpp:
        format_cpp_begin();
        break;
    case technical_space::csharp:
        format_csharp_begin();
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(technical_space_));
        BOOST_LOG_SEV(lg, error) << invalid_technical_space << s;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_technical_space + s));
    } }
}

void namespace_formatter::format_end() {
    BOOST_LOG_SEV(lg, trace) << "Ending namespace.";
    using logical::entities::technical_space;
    switch(technical_space_) {
    case technical_space::cpp:
        format_cpp_end();
        break;
    case technical_space::csharp:
        format_csharp_end();
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(technical_space_));
        BOOST_LOG_SEV(lg, error) << invalid_technical_space << s;
        BOOST_THROW_EXCEPTION(formatting_error(invalid_technical_space + s));
    } }
}

}
