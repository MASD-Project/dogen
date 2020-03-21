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
#include <sstream>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.m2t/io/formatters/infix_configuration_io.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.formatters.sequence_formatter"));

const std::string empty;
const std::string comma(",");

}

namespace dogen::m2t::formatters {

bool sequence_formatter::is_first() const {
    return position_ == 0;
}

bool sequence_formatter::is_last() const {
    return position_ == sequence_size_ - 1;
}

bool sequence_formatter::is_single() const {
    return is_first() && is_last();
}

std::string sequence_formatter::
value_for_position(const infix_configuration& ic) const {
    if (is_single()) {
        if (!ic.first().empty()) {
            // when we are single, first takes priority if supplied.
            return ic.first();
        }
        return ic.last();
    } else if (is_first() && !ic.first().empty()) {
        // if is first and first has been supplied, it takes precedence.
        return ic.first();
    } else if (!is_last() && !ic.not_last().empty()) {
        // if we are not last (including first) and not last has been
        // supplied.
        return ic.not_last();
    } else if (!is_first() && (!is_last() || !ic.not_first().empty())) {
        // when we are last, not first takes precedence if supplied.
        return ic.not_first();
    } else if (is_last())
        return ic.last();

    return empty;
}

infix_configuration& sequence_formatter::prefix_configuration() {
    return prefix_configuration_;
}

infix_configuration& sequence_formatter::postfix_configuration() {
    return postfix_configuration_;
}

std::string sequence_formatter::prefix() const {
    log_current_state();
    const auto r(value_for_position(prefix_configuration_));
    BOOST_LOG_SEV(lg, trace) << "about to return: " << r;
    return r;
}

std::string sequence_formatter::postfix(const bool skip) const {
    if (skip)
        return empty;

    std::ostringstream s;
    s << value_for_position(postfix_configuration_);
    if (!is_last())
        s << element_separator_;

    return s.str();
}

unsigned int sequence_formatter::current_position() const {
    return position_;
}

void sequence_formatter::log_current_state() const {
    BOOST_LOG_SEV(lg, trace) << "Position: " << position_
                             << " element separator: " << element_separator_
                             << " is first: " << is_first()
                             << " is last: " << is_last()
                             << " is single: " << is_single();

    BOOST_LOG_SEV(lg, trace) << "Prefix configuration: "
                             << prefix_configuration_;
    BOOST_LOG_SEV(lg, trace) << "Value for prefix position: "
                             << value_for_position(prefix_configuration_);

    BOOST_LOG_SEV(lg, trace) << "Postfix configuration: "
                             << postfix_configuration_;
    BOOST_LOG_SEV(lg, trace) << "Value for postfix position: "
                             << value_for_position(postfix_configuration_);
}

void sequence_formatter::element_separator(const std::string& s) {
    element_separator_ = s;
}

void sequence_formatter::next() {
    ++position_;
}

void sequence_formatter::reset() {
    position_ = 0;
    element_separator_ = comma;
    prefix_configuration_ = infix_configuration();
    postfix_configuration_ = infix_configuration();
}

}
