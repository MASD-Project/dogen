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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/registrar.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/registrar_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.fabric.registrar_factory"));

const std::string simple_name("registrar");

}

namespace dogen::generation::cpp::fabric {

boost::shared_ptr<fabric::registrar> registrar_factory::
make(const assets::meta_model::name& model_name) const {
    assets::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(model_name, simple_name));
    auto r(boost::make_shared<registrar>());
    r->name(n);
    r->meta_name(meta_name_factory::make_registrar_name());
    r->intrinsic_technical_space(assets::meta_model::technical_space::cpp);
    r->configuration(
        boost::make_shared<variability::meta_model::configuration>());
    r->configuration()->name().simple(r->name().simple());
    r->configuration()->name().qualified(r->name().qualified().dot());
    return r;
}

std::list<boost::shared_ptr<assets::meta_model::element>>
registrar_factory::make(const generation::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating registrars.";

    std::list<boost::shared_ptr<assets::meta_model::element>> r;

    auto rg(make(m.name()));
    using assets::meta_model::origin_types;
    rg->origin_type(origin_types::target);
    for (const auto& l : m.leaves())
        rg->leaves().push_back(l);

    const auto lambda([](const assets::meta_model::name& a,
            const assets::meta_model::name& b) {
            return a.qualified().dot() < b.qualified().dot();
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
