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
#include "dogen/annotations/io/scope_types_io.hpp"
#include "dogen/annotations/types/object.hpp"
#include "dogen/annotations/io/scribble_group_io.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/annotations_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.annotations_expander"));

}

namespace dogen {
namespace yarn {

class updater {
public:
    updater(const yarn::name& model_name,
        const std::unordered_map<std::string, annotations::annotation_group>&
        annotation_groups);

private:

    template<typename Extensible>
    void update_extensible(Extensible& e) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        const auto i(annotation_groups_.find(id));
        if (i == annotation_groups_.end()) {
            BOOST_LOG_SEV(lg, debug) << "No scribble groups for element: "
                                     << id;
            return;
        }

        e.annotation(i->second.parent());
        BOOST_LOG_SEV(lg, debug) << "Updated annotations for element.";
    }

    template<typename ExtensibleAndStateful>
    void update_extensible_and_stateful(ExtensibleAndStateful& eas) {
        const auto id(eas.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        const auto i(annotation_groups_.find(id));
        if (i == annotation_groups_.end()) {
            BOOST_LOG_SEV(lg, debug) << "No scribble group for element: " << id;
            return;
        }

        const auto& ag(i->second);
        eas.annotation(ag.parent());

        for (auto& attr : eas.local_attributes()) {
            const auto n(attr.name().simple());
            const auto j(ag.children().find(n));
            if (j == ag.children().end()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute has no annotation: " << n
                                         << ". Element: " << eas.name().id();
                continue;
            }

            attr.annotation(j->second);
            BOOST_LOG_SEV(lg, debug) << "Created annotations for attribute: "
                                     << n;
        }
        BOOST_LOG_SEV(lg, debug) << "Created annotations for element.";
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
    const std::unordered_map<std::string, annotations::annotation_group>&
    annotation_groups_;
};

updater::updater(const yarn::name& model_name,
    const std::unordered_map<std::string, annotations::annotation_group>&
    annotation_groups) : model_name_(model_name),
                         annotation_groups_(annotation_groups) {}

void annotations_expander::
expand(const annotations::repository& drp, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Starting annotations expansion for model: "
                             << im.name().id();
    BOOST_LOG_SEV(lg, debug) << "Scribble groups: "
                             << im.indices().scribble_groups();

    const annotations::annotation_groups_factory f(drp);
    const auto sgrps(f.build(im.name().id(), im.indices().scribble_groups()));
    updater u(im.name(), sgrps);
    yarn::elements_traversal(im, u);

    BOOST_LOG_SEV(lg, debug) << "Finished annotations expansion.";
}

} }
