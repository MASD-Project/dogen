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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/helper_properties_repository_io.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_factory.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.helper_properties_repository_factory"));

const std::string duplicate_name("Duplicate name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

namespace {

class primitve_ids_generator : public yarn::element_visitor {
private:
    std::unordered_set<std::string> result_;

private:
    template<typename Nameable>
    void insert(const Nameable& n) {
        result_.insert(n.name().id());
    }

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::primitive& p) { insert(p); }
    void visit(const dogen::yarn::enumeration& e) { insert(e); }

public:
    const std::unordered_set<std::string>& result() const { return result_; }

public:
    void operator()(const std::pair<std::string,
        boost::shared_ptr<dogen::yarn::element> >& pair) {
        const auto& e(*pair.second);
        e.accept(*this);
    }
};

class generator final : public yarn::element_visitor {
public:
    explicit generator(const helper_properties_factory& f) : factory_(f) {}

public:
    using yarn::element_visitor::visit;
    void visit(const dogen::yarn::object& o);

public:
    const helper_properties_repository& result() const { return result_; }

private:
    const helper_properties_factory& factory_;
    helper_properties_repository result_;
};

void generator::visit(const dogen::yarn::object& o) {
    if (o.generation_type() == yarn::generation_types::no_generation)
        return;

    const auto id(o.name().id());
    BOOST_LOG_SEV(lg, debug) << "Creating helper instances for" << id;

    const auto iir(o.in_inheritance_relationship());
    const auto hp(factory_.make(iir, o.local_attributes()));
    const auto pair(std::make_pair(id, hp));
    auto& hpbn(result_.by_id());
    if (!hpbn.insert(pair).second) {
        BOOST_LOG_SEV(lg, error) << duplicate_name << id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_name + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating helper instances for" << id;
}

}

std::unordered_map<std::string, std::unordered_set<std::string>>
helper_properties_repository_factory::
facets_for_family(const formatters::container& fc) const {
    std::unordered_map<std::string, std::unordered_set<std::string>> r;

    /*
     * Unpack the helper formatter container to generate a mapping of
     * helper family to facet. The container has helpers by family, by
     * owning file formatter.
     */
    for (const auto& families_pair : fc.helper_formatters())
        for (const auto& file_formatter_pair : families_pair.second)
            for (const auto& hf : file_formatter_pair.second)
                for (const auto& f : hf->owning_facets())
                    r[hf->family()].insert(f);

    return r;
}

helper_properties_repository
helper_properties_repository_factory::make(
    const settings::helper_settings_repository& hsrp,
    const settings::streaming_settings_repository& ssrp,
    const formatters::container& fc,
    const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating helper repository.";

    primitve_ids_generator pig;
    for (const auto& pair : m.elements())
        pig(pair);

    BOOST_LOG_SEV(lg, debug) << "Primitive IDs: " << pig.result();

    const auto fff(facets_for_family(fc));
    BOOST_LOG_SEV(lg, debug) << "Facets for family: " << fff;

    const helper_properties_factory f(pig.result(), hsrp, ssrp);
    generator g(f);
    for (const auto& pair : m.elements()) {
        const auto& e(*pair.second);
        e.accept(g);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating helper repository:"
                             << g.result();
    return g.result();
}

} } } }
