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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/helpers/printing_error.hpp"
#include "dogen.logical/types/helpers/pretty_printer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("assets.helpers.pretty_printer"));

constexpr char space(' ');
constexpr std::string_view comma_space(", ");
constexpr std::string_view double_colon("::");
constexpr std::string_view dot(".");
constexpr char less_than('<');
constexpr char greater_than('>');

const std::string unsupported_separator("Unsupported separator");
const std::string empty_child("Attempt to add an empty child.");

}

namespace dogen::logical::helpers {

pretty_printer::pretty_printer()
    : has_children_(false), last_child_had_children_(false),
      separator_(separators::angle_brackets) { }

pretty_printer::pretty_printer(const separators s)
    : has_children_(false), last_child_had_children_(false),
      separator_(s) { }

std::list<std::string> pretty_printer::
to_list(const meta_model::name& n, const bool model_name_mode) const {
    std::list<std::string> r;
    auto lambda([&](const std::string& s) {
            if (!s.empty())
                r.push_back(s);
        });

    const auto& l(n.location());
    for (const auto& m : l.external_modules())
        lambda(m);

    for (const auto& m : l.model_modules())
        lambda(m);

    for (const auto& m : l.internal_modules())
        lambda(m);

    if (!l.element().empty())
        lambda(l.element());

    /*
     * If the name we are printing is a model name, we must not add
     * the simple name as it is already in the model module path.
     */
    if (!model_name_mode)
        lambda(n.simple());

    return r;
}

void pretty_printer::print_enclosed(const std::list<std::string>& l) {
    for (const auto& c : l)
        stream_ << less_than << c << greater_than;
}

void pretty_printer::
print_scoped(std::string_view separator, const std::list<std::string>& l) {
    bool is_first(true);

    for (const auto& c : l) {
        if (!is_first)
            stream_ << separator;
        stream_ << c;
        is_first = false;
    }
}

void pretty_printer::
add(const meta_model::name& n, const bool model_name_mode) {
    const auto l(to_list(n, model_name_mode));

    switch (separator_) {
    case separators::angle_brackets:
        print_enclosed(l);
        break;
    case separators::double_colons:
        print_scoped(double_colon, l);
        break;
    case separators::dots:
        print_scoped(dot, l);
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_separator << ": "
                                 << static_cast<unsigned int>(separator_);
        BOOST_THROW_EXCEPTION(printing_error(unsupported_separator));
    }
}

void pretty_printer::add(const std::string& c) {
    stream_ << c;
}

void pretty_printer::add_child(const std::string& c) {
    if (c.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_child;
        BOOST_THROW_EXCEPTION(printing_error(empty_child));
    }

    /*
     * If we are the first child to be added, open the angle brackets;
     * otherwise, separate the siblings.
     */
    if (!has_children_)
        stream_ << less_than;
    else
        stream_ << comma_space;

    stream_ << c;
    has_children_ = true;

    /*
     * Remember if the last name tree child also had children.
     */
    last_child_had_children_ = c.back() == greater_than;
}

std::string pretty_printer::print() {
    /*
    * If we do not have any children, the printing is finished.
    */
    if (!has_children_)
        return stream_.str();

    /*
     * If we did have some children and the last child had children,
     * add a space between template markers. Not really required for
     * C++ 11 and above, but we will leave it for now to avoid
     * spurious differences.
     */
    if (last_child_had_children_)
        stream_ << space;

    /*
     * Close the children separators.
     */
    stream_ << greater_than;

    return stream_.str();
}

void pretty_printer::clear() {
    stream_.str("");
}

}
