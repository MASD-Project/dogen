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
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.modeling/types/helpers/name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/registrar.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/registrar_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("generation.cpp.fabric.registrar_factory"));

const std::string simple_name("registrar");

}

namespace masd::dogen::generation::cpp::fabric {

boost::shared_ptr<fabric::registrar> registrar_factory::
make(const modeling::meta_model::name& model_name) const {
    modeling::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(model_name, simple_name));
    auto r(boost::make_shared<registrar>());
    r->name(n);
    r->meta_name(meta_name_factory::make_registrar_name());
    return r;
}

std::list<boost::shared_ptr<modeling::meta_model::element>>
registrar_factory::make(const modeling::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating registrars.";

    std::list<boost::shared_ptr<modeling::meta_model::element>> r;

    auto rg(make(m.name()));
    using modeling::meta_model::origin_types;
    rg->origin_type(origin_types::target);
    for (const auto& l : m.leaves())
        rg->leaves().push_back(l);

    const auto lambda([](const modeling::meta_model::name& a,
            const modeling::meta_model::name& b) {
            return a.id() < b.id();
        });
    rg->leaves().sort(lambda);

    for (const auto& pair : m.references()) {
        const auto origin_type(pair.second);
        if (origin_type == origin_types::proxy_reference)
            continue;

        const auto ref(pair.first);
        rg->model_dependencies().push_back(ref);

        auto ref_rg(make(ref));
        ref_rg->origin_type(origin_type);
        r.push_back(ref_rg);
        rg->registrar_dependencies().push_back(ref_rg->name());
    }

    r.push_back(rg);
    BOOST_LOG_SEV(lg, debug) << "Generated registrars: " << r.size();
    return r;
}

}
