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
#include <boost/throw_exception.hpp>
#include "dogen/sml/types/workflow.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/engine/types/model_source.hpp"
#include "dogen/engine/types/director.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("engine.director"));
const std::string merged("merged_");

}

namespace dogen {
namespace engine {

director::director(const config::settings& settings)
    : settings_(settings), verbose_(settings_.troubleshooting().verbose()),
      persister_(settings) { }

boost::optional<sml::model> director::create_model() const {
    const bool add_system_models(true);
    const bool add_versioning_types(!settings_.cpp().disable_versioning());
    sml::workflow w(add_system_models, add_versioning_types);

    model_source source(settings_);
    const auto pair(w.execute(source));
    const auto& m(pair.second);

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    persister_.save_model(m, merged);

    BOOST_LOG_SEV(lg, debug) << "Totals: pods: " << m.pods().size()
                             << " enumerations: " << m.enumerations().size()
                             << " exceptions: " << m.exceptions().size()
                             << " primitives: " << m.primitives().size();

    const auto has_generatable_types(pair.first);
    if ((has_generatable_types))
        return boost::optional<sml::model>(m);

    BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
    return boost::optional<sml::model>();
}

} }
