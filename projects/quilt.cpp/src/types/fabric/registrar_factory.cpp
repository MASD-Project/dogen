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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.fabric.registrar_factory"));

const std::string simple_name("registrar");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

boost::shared_ptr<fabric::registrar> registrar_factory::
build(const yarn::name& model_name) const {
    yarn::name_factory nf;
    const auto n(nf.build_element_in_model(model_name, simple_name));
    auto r(boost::make_shared<fabric::registrar>());
    r->name(n);
    return r;
}

std::list<boost::shared_ptr<yarn::element>>
registrar_factory::build(const yarn::intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Generating registrars.";

    std::list<boost::shared_ptr<yarn::element>> r;

    auto rg(build(im.name()));
    rg->generation_type(yarn::generation_types::full_generation);
    for (const auto& l : im.leaves())
        rg->leaves().push_back(l);

    const auto lambda([](const yarn::name& a, const yarn::name& b) {
            return a.id() < b.id();
        });
    rg->leaves().sort(lambda);

    for (const auto& pair : im.references()) {
        const auto origin_type(pair.second);
        if (origin_type == yarn::origin_types::proxy_reference)
            continue;

        const auto ref(pair.first);
        rg->model_dependencies().push_back(ref);

        auto ref_rg(build(ref));
        ref_rg->generation_type(yarn::generation_types::no_generation);
        r.push_back(ref_rg);
        rg->registrar_dependencies().push_back(ref_rg->name());
    }

    r.push_back(rg);
    BOOST_LOG_SEV(lg, debug) << "Generated registrars: " << r.size();
    return r;
}

} } } }
