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
#include "dogen.injection/types/transforms/model_production_chain.hpp"
#include "dogen.engine/types/transforms/scoped_context_manager.hpp"
#include "dogen.engine/types/spec_dumper.hpp"
#include "dogen/types/spec_entry.hpp"
#include "dogen/types/spec_group.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("engine.spec_dumper"));

const std::string empty_output_directory;
const std::string activity("dumpspecs");

}

namespace dogen::engine {

specs spec_dumper::dump(const configuration& cfg) const {
    BOOST_LOG_SEV(lg, debug) << "Started dumping specs.";

    {
        using namespace transforms;
        scoped_context_manager scm(cfg, activity, empty_output_directory);
        specs r;

        spec_group injection;
        injection.name("Injection");
        injection.description("Read external formats into Dogen.");

        using injection::transforms::model_production_chain;
        auto& rg(model_production_chain::registrar());
        for (const auto& ext : rg.registered_decoding_extensions()) {
            const auto& d(rg.decoding_transform_for_extension(ext));
            spec_entry e;
            e.name(d.id());

            std::ostringstream s;
            s << d.description() << " Extension: '" << d.extension() << "'";
            e.description(s.str());
            injection.entries().push_back(e);
        }
        r.groups().push_back(injection);

        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished dumping specs.";
}

}
