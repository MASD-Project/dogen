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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/dynamic/io/scope_types_io.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/dynamic/io/raw_aggregate_io.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
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
    updater(const yarn::name& model_name,
        const std::unordered_map<std::string, dynamic::object_aggregate>&
        object_aggregates);

private:

    template<typename Extensible>
    void update_extensible(Extensible& e) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        const auto i(object_aggregates_.find(id));
        if (i == object_aggregates_.end()) {
            BOOST_LOG_SEV(lg, debug) << "No dynamic objects for element: "
                                     << id;
            return;
        }

        e.extensions(i->second.element());
        BOOST_LOG_SEV(lg, debug) << "Updated dynamic object for element.";
    }

    template<typename ExtensibleAndStateful>
    void update_extensible_and_stateful(ExtensibleAndStateful& eas) {
        const auto id(eas.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        const auto i(object_aggregates_.find(id));
        if (i == object_aggregates_.end()) {
            BOOST_LOG_SEV(lg, debug) << "No dynamic objects for element: "
                                     << id;
            return;
        }

        const auto& oa(i->second);
        eas.extensions(oa.element());

        for (auto& attr : eas.local_attributes()) {
            const auto n(attr.name().simple());
            const auto j(oa.attributes().find(n));
            if (j == oa.attributes().end()) {
                BOOST_LOG_SEV(lg, debug) << "No kvps for attribute: " << n
                                         << ". Element: " << eas.name().id();
                continue;
            }

            attr.extensions(j->second);
            BOOST_LOG_SEV(lg, debug) << "Created dynamic object for attribute: "
                                     << n;
        }
        BOOST_LOG_SEV(lg, debug) << "Created dynamic object for element.";
    }

public:
    void operator()(yarn::module& m) { update_extensible(m); }
    void operator()(yarn::concept& c) { update_extensible_and_stateful(c); }
    void operator()(yarn::primitive& p) { update_extensible(p); }
    void operator()(yarn::enumeration& e) { update_extensible(e); }
    void operator()(yarn::object& o) { update_extensible_and_stateful(o); }
    void operator()(yarn::exception& e) { update_extensible(e); }
    void operator()(yarn::visitor& v) { update_extensible(v); }

private:
    const yarn::name model_name_;
    const std::unordered_map<std::string, dynamic::object_aggregate>&
    object_aggregates_;
};

updater::updater(const yarn::name& model_name,
    const std::unordered_map<std::string, dynamic::object_aggregate>&
    object_aggregates) : model_name_(model_name),
                         object_aggregates_(object_aggregates) {}

void dynamic_expander::
expand(const dynamic::repository& drp, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Starting dynamic expansion for model: "
                             << im.name().id();
    BOOST_LOG_SEV(lg, debug) << "Raw kvps: " << im.indices().raw_aggregates();

    const dynamic::workflow w(drp);
    const auto oas(w.execute(im.name().id(), im.indices().raw_aggregates()));
    updater u(im.name(), oas);
    yarn::elements_traversal(im, u);

    BOOST_LOG_SEV(lg, debug) << "Finished dynamic expansion.";
}

} }
