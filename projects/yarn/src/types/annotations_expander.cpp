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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/io/scope_types_io.hpp"
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

class scribble_updater {
public:
    explicit scribble_updater(std::unordered_map<std::string,
        annotations::scribble_group>& sgrps) : scribble_groups_(sgrps) {}

private:
    void update_scribble(const element& e) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        if (e.stereotypes().empty()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no stereotypes.";
            return;
        }

        const auto i(scribble_groups_.find(id));
        if (i != scribble_groups_.end()) {
            BOOST_LOG_SEV(lg, debug) << "Found scribble group, adding labels.";
            i->second.parent().candidate_labels(e.stereotypes());
            return;
        }

        /*
         * Note that we are ignoring children here on purpose;
         * candidate labels are not used by children at present.
         */
        BOOST_LOG_SEV(lg, debug) << "Injecting new scribble group.";
        annotations::scribble_group sg;
        sg.parent().candidate_labels(e.stereotypes());

        using annotations::scope_types;
        sg.parent().scope(scope_types::entity);

        scribble_groups_[id] = sg;
    }

public:
    bool include_injected_elements() { return false; }
    void operator()(yarn::element&) { }
    void operator()(yarn::module& m) { update_scribble(m); }
    void operator()(yarn::concept& c) { update_scribble(c); }
    void operator()(yarn::builtin& b) { update_scribble(b); }
    void operator()(yarn::enumeration& e) { update_scribble(e); }
    void operator()(yarn::primitive& p) { update_scribble(p); }
    void operator()(yarn::object& o) { update_scribble(o); }
    void operator()(yarn::exception& e) { update_scribble(e); }
    void operator()(yarn::visitor& v) { update_scribble(v); }

private:
    std::unordered_map<std::string, annotations::scribble_group>&
    scribble_groups_;
};

class annotation_updater {
public:
    annotation_updater(const yarn::name& model_name,
        const std::unordered_map<std::string, annotations::annotation_group>&
        annotation_groups);

private:

    template<typename Extensible>
    void update_extensible(Extensible& e) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        const auto i(annotation_groups_.find(id));
        if (i == annotation_groups_.end()) {
            BOOST_LOG_SEV(lg, debug) << "No annotation group for element: "
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
            BOOST_LOG_SEV(lg, debug) << "No annotation group for element: "
                                     << id;
            return;
        }

        const auto& ag(i->second);
        eas.annotation(ag.parent());

        for (auto& attr : eas.local_attributes()) {
            /*
             * Bit of a hack here; we are using simple name because the
             * dia frontend is inserting by simple name and its
             * non-trivial to change it to insert by ID.
             */
            const auto sn(attr.name().simple());
            const auto j(ag.children().find(sn));
            if (j == ag.children().end()) {
                BOOST_LOG_SEV(lg, debug) << "Attribute has no annotation: " << sn
                                         << ". Element: " << eas.name().id();
                continue;
            }

            attr.annotation(j->second);
            BOOST_LOG_SEV(lg, debug) << "Created annotations for attribute: "
                                     << sn;
        }
        BOOST_LOG_SEV(lg, debug) << "Created annotations for element.";
    }

public:
    bool include_injected_elements() { return false; }
    void operator()(yarn::element&) { }
    void operator()(yarn::module& m) { update_extensible(m); }
    void operator()(yarn::concept& c) { update_extensible_and_stateful(c); }
    void operator()(yarn::builtin& b) { update_extensible(b); }
    void operator()(yarn::enumeration& e);
    void operator()(yarn::primitive& p) { update_extensible(p); }
    void operator()(yarn::object& o) { update_extensible_and_stateful(o); }
    void operator()(yarn::exception& e) { update_extensible(e); }
    void operator()(yarn::visitor& v) { update_extensible(v); }

private:
    const yarn::name model_name_;
    const std::unordered_map<std::string, annotations::annotation_group>&
    annotation_groups_;
};

void annotation_updater::operator()(yarn::enumeration& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

    const auto i(annotation_groups_.find(id));
    if (i == annotation_groups_.end()) {
        BOOST_LOG_SEV(lg, debug) << "No annotation group for element: " << id;
        return;
    }

    const auto& ag(i->second);
    e.annotation(ag.parent());

    for (auto& en : e.enumerators()) {
        /*
         * Bit of a hack here; we are using simple name because the
         * dia frontend is inserting by simple name and its
         * non-trivial to change it to insert by ID.
         */
        const auto sn(en.name().simple());
        const auto i(ag.children().find(sn));
        if (i == ag.children().end()) {
            BOOST_LOG_SEV(lg, debug) << "Enumerator has no annotation: " << sn
                                     << ". Element: " << e.name().id();
            continue;
        }

        en.annotation(i->second);
        BOOST_LOG_SEV(lg, debug) << "Created annotations for attribute: " << sn;
    }
}

annotation_updater::annotation_updater(const yarn::name& model_name,
    const std::unordered_map<std::string, annotations::annotation_group>&
    annotation_groups) : model_name_(model_name),
                         annotation_groups_(annotation_groups) {}

void annotations_expander::
update_scribble_groups(intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Updating scribble groups.";

    /*
     * Augment all scribbles with candidate labels, which are in
     * effect the stereotypes.
     */
    scribble_updater u(im.scribble_groups());
    yarn::elements_traversal(im, u);

    BOOST_LOG_SEV(lg, debug) << "Updated scribble groups. Result: "
                             << im.scribble_groups();
}

void annotations_expander::
update_annotations(const annotations::annotation_groups_factory& agf,
    intermediate_model& im) const {

    /*
     * We first call the annotations group factory to convert our
     * scribble groups into annotation groups.
     */
    const auto annotation_groups(agf.make(im.scribble_groups()));

    /*
     * Now we have to unpack all of the annotation groups and populate
     * the yarn elements that own them with their annotations.
     */
    annotation_updater u(im.name(), annotation_groups);
    yarn::elements_traversal(im, u);
}

void annotations_expander::
expand(const annotations::annotation_groups_factory& agf,
    intermediate_model& im) const {

    BOOST_LOG_SEV(lg, debug) << "Starting annotations expansion for model: "
                             << im.name().id();

    update_scribble_groups(im);
    update_annotations(agf, im);

    BOOST_LOG_SEV(lg, debug) << "Finished annotations expansion.";
}

} }
