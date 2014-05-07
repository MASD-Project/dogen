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
#include "dogen/dia/types/hydrator.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/dia_to_sml/types/workflow.hpp"
#include "dogen/knit/types/provider.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("knit.provider"));
std::string empty;

}

namespace dogen {
namespace knit {

provider::provider(const config::knitting_settings& s)
    : settings_(s), persister_(s) { }

provider::~provider() noexcept { }

dia::diagram
provider::hydrate_diagram(const boost::filesystem::path& path) const {
    dia::hydrator h(path);
    dia::diagram r(h.hydrate());
    persister_.persist(r, path.stem().string());
    return r;
}

sml::model provider::to_sml(const dia::diagram& d,
    const std::string& model_name,
    const std::string& external_module_path,
    const bool is_target) const {

    const bool dmp(settings_.input().disable_model_module());
    const std::string name(dmp ? empty : model_name);

    dogen::dia_to_sml::workflow w;
    sml::model r(w.execute(d, name, external_module_path, is_target));
    persister_.persist(r, empty);
    return std::move(r);
}

sml::model provider::provide(const boost::filesystem::path& p,
    const std::string& external_module_path,
    const bool is_target) {

    const dia::diagram d(hydrate_diagram(p));
    const std::string model_name(p.stem().string());
    return to_sml(d, model_name, external_module_path, is_target);
}

} }
