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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/concept.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/expansion/building_error.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("cpp.expansion.inclusion_dependencies_factory"));

const std::string duplicate_qname("Duplicate qname: ");
const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string empty_include_directive("Include directive is empty.");

const char angle_bracket('<');
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

}

namespace dogen {
namespace cpp {
namespace expansion {

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {
    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_include_directive));
    }

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    return lhs < rhs;
}

/**
 * @brief Generates all inclusion dependencies.
 */
class inclusion_dependencies_generator {
public:
    inclusion_dependencies_generator(const dynamic::schema::repository& rp,
        const container& c, const inclusion_directives_repository& idrp)
        : schema_repository_(rp), container_(c),
          inclusion_directives_repository_(idrp) {}

private:
    /**
     * @brief Returns the map for the supplied qname.
     */
    std::unordered_map<std::string, std::list<std::string> >&
    create_map_for_qname(const sml::qname& qn);

    /**
     * @brief Generates all of the inclusion dependencies for the
     * formatters and qualified name.
     */
    template<typename SmlEntity>
    void generate(std::forward_list<
            boost::shared_ptr<
                inclusion_dependencies_provider_interface<SmlEntity>
                >
            > providers, const SmlEntity& e) {

        if (e.generation_type() == sml::generation_types::no_generation)
            return;

        auto& r(create_map_for_qname(e.name()));
        for (const auto p : providers) {
            BOOST_LOG_SEV(lg, debug) << "Providing for: "
                                     << p->formatter_name();

            const auto& idrp(inclusion_directives_repository_);
            auto id(p->provide(schema_repository_, idrp, e));

            if (!id)
                continue;

            id->sort(include_directive_comparer);
            const auto id_pair(std::make_pair(p->formatter_name(), *id));
            const bool inserted(r.insert(id_pair).second);
            if (!inserted) {
                const auto n(sml::string_converter::convert(e.name()));
                BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                         << p->formatter_name()
                                         << " for type: " << n;
                BOOST_THROW_EXCEPTION(building_error(duplicate_formatter_name +
                        p->formatter_name()));
            }
        }
    }

public:
    void operator()(const dogen::sml::object& o);
    void operator()(const dogen::sml::enumeration& /*e*/) {}
    void operator()(const dogen::sml::primitive& /*p*/) {}
    void operator()(const dogen::sml::module& /*m*/) {}
    void operator()(const dogen::sml::concept& /*c*/) {}

public:
    const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::list<std::string> >
    >& result() const;

private:
    const dynamic::schema::repository& schema_repository_;
    const container& container_;
    const inclusion_directives_repository& inclusion_directives_repository_;
    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, std::list<std::string> >
        > result_;
};

std::unordered_map<std::string, std::list<std::string> >&
inclusion_dependencies_generator::create_map_for_qname(const sml::qname& qn) {
    const auto i(result_.find(qn));
    if (i != result_.end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
        BOOST_THROW_EXCEPTION(building_error(duplicate_qname + n));
    }
    return result_[qn];
}

void inclusion_dependencies_generator::operator()(const dogen::sml::object& o) {
    generate(container_.object_providers(), o);
}

const std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, std::list<std::string> >
    >&
inclusion_dependencies_generator::result() const {
    return result_;
}

std::unordered_map<sml::qname,
                   std::unordered_map<std::string, std::list<std::string> >
                   >
inclusion_dependencies_factory::make(const dynamic::schema::repository& rp,
    const container& c, const inclusion_directives_repository& idrp,
    const sml::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating inclusion dependencies.";

    inclusion_dependencies_generator g(rp, c, idrp);
    sml::all_model_items_traversal(m, g);

    const auto& r(g.result());
    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies:"
                             << r;
    return r;
}

} } }
