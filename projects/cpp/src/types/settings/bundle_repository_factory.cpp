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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/io/settings/bundle_repository_io.hpp"
#include "dogen/cpp/types/settings/bundle_factory.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/bundle_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.bundle_repository_factory"));

const std::string duplicate_qname("Duplicate qname: ");

}

namespace dogen {
namespace cpp {
namespace settings {

namespace {

/**
 * @brief Generates all inclusion dependencies.
 */
class generator final {
public:
    explicit generator(const bundle_factory& f) : factory_(f) {}

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename SmlEntity>
    void generate(const SmlEntity& e) {
        if (e.generation_type() == sml::generation_types::no_generation)
            return;

        const auto b(factory_.make(e.extensions()));
        const auto pair(std::make_pair(e.name(), b));
        auto& deps(result_.bundles_by_qname());
        const auto res(deps.insert(pair));
        if (!res.second) {
            const auto n(sml::string_converter::convert(e.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_qname + n));
        }
    }

public:
    void operator()(const dogen::sml::object& o) { generate(o); }
    void operator()(const dogen::sml::enumeration& e) { generate(e); }
    void operator()(const dogen::sml::primitive& p) { generate(p); }
    void operator()(const dogen::sml::module& m) { generate(m); }
    void operator()(const dogen::sml::concept& c) { generate(c); }

public:
    const bundle_repository& result() const { return result_; }

private:
    const bundle_factory& factory_;
    bundle_repository result_;
};

}

bundle_repository bundle_repository_factory::
make(const dynamic::repository& rp, const dynamic::object& root_object,
    const opaque_settings_builder& osb, const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Creating settings bundle repository.";

    const bundle_factory f(rp, root_object, osb);
    generator g(f);
    sml::all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished creating settings bundle repository."
                             << g.result();
    return g.result();
}

} } }
