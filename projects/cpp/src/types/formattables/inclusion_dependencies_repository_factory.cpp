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
#include "dogen/tack/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_factory.hpp"
#include "dogen/cpp/io/formattables/inclusion_dependencies_repository_io.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_dependencies_repository_factory"));

const std::string registrar_name("registrar");
const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates all inclusion dependencies.
 */
class generator final {
public:
    explicit generator(const inclusion_dependencies_factory& f) : factory_(f) {}

public:
    template<typename TackEntity>
    void generate(const TackEntity& e, const tack::name& n) {
        const auto id(factory_.make(e));

        // note: optional return may have be cleaner here, but however it
        // would complicate the logic in the factory.
        if (id.empty())
            return;

        const auto pair(std::make_pair(n, id));
        auto& deps(result_.inclusion_dependencies_by_name());
        const auto res(deps.insert(pair));
        if (!res.second) {
            const auto qn(n.qualified());
            BOOST_LOG_SEV(lg, error) << duplicate_name << qn;
            BOOST_THROW_EXCEPTION(building_error(duplicate_name + qn));
        }
    }

private:
    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename TackEntity>
    void generate(const TackEntity& e) {
        if (e.generation_type() == tack::generation_types::no_generation)
            return;

        generate(e, e.name());
    }

public:
    void operator()(const dogen::tack::object& o) { generate(o); }
    void operator()(const dogen::tack::enumeration& e) { generate(e); }
    void operator()(const dogen::tack::primitive& p) { generate(p); }
    void operator()(const dogen::tack::module& m) { generate(m); }
    void operator()(const dogen::tack::concept& c) { generate(c); }

public:
    const inclusion_dependencies_repository& result() const { return result_; }

private:
    const inclusion_dependencies_factory& factory_;
    inclusion_dependencies_repository result_;
};

}

inclusion_dependencies_repository inclusion_dependencies_repository_factory::
make(const inclusion_dependencies_builder_factory& bf, const container& c,
    const tack::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating inclusion dependencies.";

    const inclusion_dependencies_factory idf(bf, c);
    generator g(idf);
    tack::all_model_items_traversal(m, g);

    tack::name n;
    n.simple(registrar_name);
    n.location().original_model_name(m.name().location().original_model_name());
    n.location().external_module_path(
        m.name().location().external_module_path());
    g.generate(m, n);

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies:"
                             << g.result();
    return g.result();
}

} } }
