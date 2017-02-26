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
#include <boost/make_shared.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.fabric.odb_options_factory"));

const std::string odb_options_name("options.odb");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

odb_options_factory::type_group odb_options_factory::
make_type_group(const annotations::type_repository& atrp) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    const auto& od = formatters::odb::traits::odb_database();
    r.odb_database = s.select_type_by_name(od);

    return r;
}

std::list<std::string> odb_options_factory::make_databases(const type_group& tg,
    const annotations::annotation& ra) const {

    const annotations::entry_selector s(ra);

    const auto& od(tg.odb_database);
    if (!s.has_entry(od))
        return std::list<std::string>();

    return s.get_text_collection_content(od);
}

boost::shared_ptr<yarn::element>
odb_options_factory::make(const annotations::type_repository& atrp,
    const yarn::intermediate_model& im) const {

    BOOST_LOG_SEV(lg, debug) << "Generating ODB Options.";

    yarn::name_factory nf;
    const auto n(nf.build_element_in_model(im.name(), odb_options_name));
    auto r(boost::make_shared<odb_options>());
    r->name(n);
    r->origin_type(im.origin_type());

    const auto ra(im.root_module().annotation());
    const auto tg(make_type_group(atrp));
    r->databases(make_databases(tg, ra));

    BOOST_LOG_SEV(lg, debug) << "Generated ODB Options.";

    return r;
}

} } } }
