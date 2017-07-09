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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/io/location_io.hpp"
#include "dogen/yarn/types/languages.hpp"
#include "dogen/yarn/types/helpers/separators.hpp"
#include "dogen/yarn/types/helpers/building_error.hpp"
#include "dogen/yarn/types/helpers/string_processor.hpp"
#include "dogen/yarn/types/helpers/pretty_printer.hpp"
#include "dogen/yarn/types/helpers/identifiable_and_qualified_builder.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.name_builder"));

const std::string empty_type_name("Type name is empty.");
const std::string empty_model_name("Model name is empty.");
const std::string empty_model_modules("Model modules are empty.");
const std::string empty_internal_modules("Internal modules are empty.");
const std::string unexpected_simple_name("Simple name is not expected.");

}

namespace dogen {
namespace yarn {
namespace helpers {

name_builder::name_builder(const bool model_name_mode)
    : model_name_mode_(model_name_mode) { }

name_builder::name_builder(const name& n, const bool model_name_mode)
    : model_name_mode_(model_name_mode), name_(n) { }

std::string name_builder::compute_id() {
    helpers::pretty_printer pp;
    pp.add(name_, model_name_mode_);
    const auto r(pp.print());
    BOOST_LOG_SEV(lg, debug) << "Computed id: " << r;
    return r;
}

void name_builder::setup_computed_properties() {
    name_.id(compute_id());

    identifiable_and_qualified_builder iqb;
    const auto iq(iqb.build(name_, model_name_mode_));
    name_.identifiable(iq.first);
    name_.qualified(iq.second);
}

name_builder& name_builder::simple_name(const std::string& sn) {
    if (model_name_mode_) {
        BOOST_LOG_SEV(lg, error) << unexpected_simple_name;
        BOOST_THROW_EXCEPTION(building_error(unexpected_simple_name));
    }

    name_.simple(sn);
    BOOST_LOG_SEV(lg, debug) << "Added simple name: " << sn;
    return *this;
}

name_builder& name_builder::model_name(const std::string& mn) {
    if (mn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_name;
        BOOST_THROW_EXCEPTION(building_error(empty_model_name));
    }

    using utility::string::splitter;
    name_.location().model_modules(splitter::split_scoped(mn));

    if (model_name_mode_)
        name_.simple(*name_.location().model_modules().rbegin());

    BOOST_LOG_SEV(lg, debug) << "Added model name: " << mn;
    return *this;
}

name_builder& name_builder::model_name(const yarn::location& l) {
    name_.location().model_modules(l.model_modules());

    BOOST_LOG_SEV(lg, debug) << "Added model name from location: " << l;
    return *this;
}

name_builder& name_builder::model_modules(const std::string& mm) {
    if (mm.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_model_modules));
    }

    using utility::string::splitter;
    name_.location().model_modules(splitter::split_scoped(mm));
    BOOST_LOG_SEV(lg, debug) << "Added model modules: " << mm;
    return *this;
}

name_builder& name_builder::
model_modules(const std::list<std::string>& mm) {
    name_.location().model_modules(mm);
    BOOST_LOG_SEV(lg, debug) << "Added model modules: " << mm;
    return *this;
}

name_builder& name_builder::internal_modules(const std::string& im) {
    if (im.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_modules));
    }

    using utility::string::splitter;
    name_.location().internal_modules(splitter::split_scoped(im));
    BOOST_LOG_SEV(lg, debug) << "Added internal modules: " << im;
    return *this;
}

name_builder& name_builder::internal_modules(
    const std::list<std::string>& im) {
    name_.location().internal_modules(im);
    BOOST_LOG_SEV(lg, debug) << "Added external models: " << im;
    return *this;
}

name_builder& name_builder::external_modules(const std::string& em) {
    if (em.empty())
        return *this;

    using utility::string::splitter;
    name_.location().external_modules(splitter::split_scoped(em));
    BOOST_LOG_SEV(lg, debug) << "Added external models: " << em;
    return *this;
}

name_builder& name_builder::external_modules(const std::list<std::string>& em) {
    name_.location().external_modules(em);
    BOOST_LOG_SEV(lg, debug) << "Added external modules: " << em;
    return *this;
}

name_builder& name_builder::location(const yarn::location& l) {
    BOOST_LOG_SEV(lg, debug) << "Added location: " << l;
    name_.location(l);
    return *this;
}

name name_builder::build() {
    setup_computed_properties();
    return name_;
}

name name_builder::build(std::list<std::string> names) {
    name_builder b;

    /*
     * If we have a single name, we are either referencing a type
     * defined in the global namespace (possibly in a different
     * model), or a type defined at the top-level in this model. As we
     * cannot tell the difference, we must fill in just the simple
     * name and let the resolver handle it properly later on.
     */
    const auto front(names.front());
    if (names.size() == 1) {
        b.simple_name(front);
        BOOST_LOG_SEV(lg, debug) << "Simple name: " << front;
        return b.build();
    }

    /*
     * The back of the list must now be the type's simple name.
     */
    const auto back(names.back());
    b.simple_name(back);
    BOOST_LOG_SEV(lg, debug) << "Simple name: " << back;
    names.pop_back(); // consume the simple name

    if (!names.empty()) {
        /*
         * Whatever is left, if anything, must be a path to non-top-level
         * modules defined within the model.
         */
        b.internal_modules(names);
        BOOST_LOG_SEV(lg, debug) << "Internal modules: " << names;
        names.clear(); // consume internal modules
    }
    return b.build();
}

name name_builder::build(const std::string& names) {

    using utility::string::splitter;
    const auto names_as_list(splitter::split_scoped(names));
    return build(names_as_list);
}

} } }
