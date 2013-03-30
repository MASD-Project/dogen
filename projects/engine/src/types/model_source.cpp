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
#include <boost/filesystem.hpp>
#include "dogen/dia/types/hydrator.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/dia_to_sml.hpp"
#include "dogen/engine/types/model_source.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("engine.model_source"));
std::string empty;

}

namespace dogen {
namespace engine {

model_source::model_source(const config::settings& settings) :
    settings_(settings), persister_(settings_) {}

dia::diagram model_source::
hydrate_diagram(const boost::filesystem::path& path) const {
    dia::hydrator h(path);
    dia::diagram r(h.hydrate());
    persister_.save_diagram(r, path.stem().string());
    return r;
}

sml::model model_source::to_sml(const dia::diagram& d, config::reference ref,
    const bool is_target) const {

    const std::string file_name(ref.path().stem().string());
    const std::string epp(ref.external_package_path());
    const std::string name(settings_.modeling().disable_model_package() ?
        empty : file_name);
    const bool verbose(settings_.troubleshooting().verbose());

    using dogen::dia_to_sml::dia_to_sml;
    dia_to_sml dia_to_sml(d, name, epp, is_target, verbose);

    sml::model m(dia_to_sml.transform());
    persister_.save_model(m, empty);
    return std::move(m);
}

std::list<sml::model> model_source::references() const {
    const bool is_target(true);
    std::list<sml::model> r;
    for (const auto ref : settings_.modeling().references()) {
        const dia::diagram d(hydrate_diagram(ref.path()));
        r.push_back(to_sml(d, ref, is_target));
    }
    return r;
}

dogen::sml::model model_source::target() const {
    config::reference ref;
    ref.path(settings_.modeling().target());
    ref.external_package_path(settings_.modeling().external_package_path());

    const dia::diagram d(hydrate_diagram(ref.path()));

    const bool is_target(true);
    return to_sml(d, ref, is_target);
}

} }
