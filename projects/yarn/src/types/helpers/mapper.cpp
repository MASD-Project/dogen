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
#include <boost/lexical_cast.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/helpers/mapping_error.hpp"
#include "dogen/yarn/io/helpers/mapping_context_io.hpp"
#include "dogen/yarn/types/helpers/mapper.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.mapper"));

const std::string lam_pointer("<lam><pointer>");

const std::string missing_mapping("Mapping not found for LAM ID: ");
const std::string unsupported_lanugage("Language is not supported: ");
const std::string unexpected_number_of__children("Expected exactly one child.");

}

namespace dogen {
namespace yarn {
namespace helpers {

mapper::mapper(const mapping_set_repository& msrp)
    : mapping_set_repository_(msrp) { }

meta_model::endomodel mapper::
clone(const meta_model::endomodel& im) const {
    auto r(im);
    r.modules(clone(im.modules()));
    r.object_templates(clone(im.object_templates()));
    r.builtins(clone(im.builtins()));
    r.enumerations(clone(im.enumerations()));
    r.primitives(clone(im.primitives()));
    r.objects(clone(im.objects()));
    r.exceptions(clone(im.exceptions()));
    r.visitors(clone(im.visitors()));
    return r;
}

const std::unordered_map<std::string, meta_model::name>&
mapper::translations_for_language(const mapping_set& ms,
    const meta_model::languages from, const meta_model::languages to) const {
    if (from == meta_model::languages::upsilon) {
        const auto i(ms.by_upsilon_id().find(to));
        if (i != ms.by_upsilon_id().end())
            return i->second;

        const auto s(boost::lexical_cast<std::string>(to));
        BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
    } else if (from == meta_model::languages::language_agnostic) {
        const auto i(ms.by_language_agnostic_id().find(to));
        if (i != ms.by_upsilon_id().end())
            return i->second;

        const auto s(boost::lexical_cast<std::string>(to));
        BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
    }

    const auto s(boost::lexical_cast<std::string>(from));
    BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
    BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
}

std::unordered_map<std::string, meta_model::name>
mapper::injections_for_language(const mapping_set& ms,
    const meta_model::languages l,
    const meta_model::endomodel& im) const {

    std::unordered_map<std::string, meta_model::name> r;
    const auto cpp(meta_model::languages::cpp);
    if (l != cpp)
        return r;

    const auto i(ms.by_language_agnostic_id().find(cpp));
    if (i == ms.by_upsilon_id().end()) {
        const auto s(boost::lexical_cast<std::string>(cpp));
        BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
        BOOST_THROW_EXCEPTION(mapping_error(unsupported_lanugage + s));
    }

    const auto& map(i->second);
    const auto j(map.find(lam_pointer));
    if (j == map.end()) {
        BOOST_LOG_SEV(lg, error) << missing_mapping << lam_pointer;
        BOOST_THROW_EXCEPTION(mapping_error(missing_mapping + lam_pointer));
    }
    const auto& n(j->second);
    for (const auto& pair : im.objects()) {
        const auto& o(pair.second);
        for (const auto& pn : o->parents()) {
            const auto pair(std::make_pair(pn.id(), n));
            r.insert(pair);
        }
    }

    return r;
}

mapping_context mapper::create_mapping_context(const mapping_set& ms,
    const meta_model::languages from, const meta_model::languages to,
    const meta_model::endomodel& im) const {
    mapping_context r;
    r.translations(translations_for_language(ms, from, to));
    r.injections(injections_for_language(ms, to, im));

    const auto i(ms.erasures_by_language().find(to));
    if (i != ms.erasures_by_language().end())
        r.erasures(i->second);

    return r;
}

meta_model::name_tree mapper::walk_name_tree(const mapping_context& mc,
    const meta_model::name_tree& nt, const bool skip_injection) const {
    const auto id(nt.current().id());
    if (mc.erasures().find(id) != mc.erasures().end()) {
        /*
         * We need to erase this type from the name tree. We do this
         * by skipping it. Note that, for erasures, only one child is
         * permitted. An erasure is required, for example, for
         * language agnostic pointers in languages where all objects
         * are pointers anyway (such as C#).
         */
        if (nt.children().size() != 1) {
            BOOST_LOG_SEV(lg, error) << unexpected_number_of__children
                                     << " Children: " << nt.children().size();
            BOOST_THROW_EXCEPTION(
                mapping_error(unexpected_number_of__children));
        }
        const auto& c(nt.children().front());
        return walk_name_tree(mc, c);
    }

    /*
     * Now we handle injections. This is the insertion of an
     * additional type above current. For example, we want to inject a
     * pointer element for all abstract classes in C++. Note that by
     * definitions, injections will always expect exactly one type
     * parameter. We do not attempt injections if we are already under
     * an injection or else we would create an infinite loop.
     */
    meta_model::name_tree r;
    if (!skip_injection) {
        const auto i(mc.injections().find(id));
        if (i != mc.injections().end()) {
            const auto& n(i->second);
            r.current(n);
            r.children().push_back(walk_name_tree(mc, nt, !skip_injection));
            return r;
        }
    }

    /*
     * Finally we handle translations. We locate a maping for the
     * current ID; if one is found, we replace the name with the
     * mapped name. Otherwise we copy across the original name.
     */
    const auto i(mc.translations().find(id));
    if (i != mc.translations().end()) {
        r.current(i->second);
        BOOST_LOG_SEV(lg, debug) << "Mapping from: " << id
                                 << " to: " << i->second.id();
    } else {
        BOOST_LOG_SEV(lg, debug) << "No translation for: " << id;
        r.current(nt.current());
    }

    /*
     * We now repeat the whole process for all our children.
     */
    for (const auto& c : nt.children())
        r.children().push_back(walk_name_tree(mc, c));

    return r;
}

void mapper::map_attributes(const mapping_context& mc,
    std::list<meta_model::attribute>& attrs) const {
    for (auto& attr : attrs)
        attr.parsed_type(walk_name_tree(mc, attr.parsed_type()));
}

bool mapper::
is_mappable(const meta_model::languages from, const meta_model::languages to) {
    return from == to ||
        from == meta_model::languages::upsilon ||
        from == meta_model::languages::language_agnostic;
}

meta_model::endomodel
mapper::map(const meta_model::languages from, const meta_model::languages to,
    const meta_model::endomodel& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started mapping. Model: " << im.name().id();
    BOOST_LOG_SEV(lg, debug) << "Mapping from: " << from << " to: " << to;
    if (from == to) {
        BOOST_LOG_SEV(lg, debug) << "No mapping required";
        return im;
    }

    /*
     * We make a clone of the original intermediate model, so that we
     * have our own set of elements. Otherwise, all mapped models
     * would be pointing to the same elements, causing confusion and
     * chaos.
     */
    auto r(clone(im));

    /*
     * For now we always use the default mapping set. In the future
     * this will be configurable via annotations.
     */
    const auto& ms(mapping_set_repository_.default_mapping_set());
    const auto mc(create_mapping_context(ms, from, to, im));
    BOOST_LOG_SEV(lg, debug) << "Mapping context: " << mc;

    for (auto& pair : r.objects())
        map_attributes(mc, pair.second->local_attributes());

    for (auto& pair : r.object_templates())
        map_attributes(mc, pair.second->local_attributes());

    r.input_language(to);
    r.output_languages().clear();
    r.output_languages().push_back(to);

    BOOST_LOG_SEV(lg, debug) << "Output language: " << r.output_languages();
    BOOST_LOG_SEV(lg, debug) << "Finished mapping.";

    return r;
}

} } }
