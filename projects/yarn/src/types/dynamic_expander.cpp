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
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/dynamic_expander.hpp"


namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.dynamic_expander"));

}

namespace dogen {
namespace yarn {

class updater {
public:
    updater(const dynamic::repository& drp,
        const std::unordered_map<std::string, dogen::yarn::raw_kvp> raw_kvps);

private:
    dynamic::object make(const yarn::name& n) const;

public:
    void operator()(yarn::module& m) { m.extensions(make(m.name())); }
    void operator()(yarn::concept& c) { c.extensions(make(c.name())); }
    void operator()(yarn::primitive& p) { p.extensions(make(p.name())); }
    void operator()(yarn::enumeration& e) { e.extensions(make(e.name())); }
    void operator()(yarn::object& o) { o.extensions(make(o.name())); }
    void operator()(yarn::exception& e) { e.extensions(make(e.name())); }
    void operator()(yarn::visitor& v) { v.extensions(make(v.name())); }

private:
    const dynamic::workflow workflow_;
    const std::unordered_map<std::string, dogen::yarn::raw_kvp>& raw_kvps_;
};

/*dynamic::object updater::make(const yarn::name& n) const {
    const auto i(raw_kvps_.find(n.id()));
    if (i == raw_kvps_.end()) {
    }

    
    }*/

void dynamic_expander::
expand(const dynamic::repository& drp, intermediate_model& im) const {
    updater u(drp, im.indices().raw_kvps());
    yarn::elements_traversal(im, u);
}

} }
