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
#include <boost/make_shared.hpp>
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/cpp/types/expansion/workflow.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/expansion/expander.hpp"

namespace dogen {
namespace cpp {
namespace expansion {

std::string expander::name() const {
    static std::string name("cpp.expansion.expander");
    return name;
}

const std::forward_list<std::string>& expander::dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r { options_copier::static_name() };
    return r;
}

void expander::setup(const dynamic::expansion::expansion_context& ec) {
    const auto& fc(formatters::workflow::registrar().formatter_container());
    const auto& m(ec.model());
    const auto& opts(ec.cpp_options());
    const auto& rp(ec.repository());

    workflow w;
    expansion_inputs_ = w.execute(opts, rp, fc, m);
}

void expander::
expand(const sml::qname& /*qn*/, const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& /*o*/) const {
}

} } }
