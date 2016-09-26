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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.inclusion_dependencies_builder"));

const auto empty_list = std::list<std::string> {};
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");
const std::string pair_type("pair");
const std::string string_type("string");
const std::string variant_type("variant");
const std::string ptree_type("ptree");
const std::string path_type("path");
const std::string date_type("date");
const std::string ptime_type("ptime");

const std::string empty_directive("Cannot add empty include directive.");
const std::string name_not_found("Cannot find name: ");
const std::string formatter_name_not_found("Cannot find formatter name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class builder_impl {
public:
    virtual ~builder_impl() {}

public:
    virtual bool is_enabled(const yarn::name& n,
        const std::string& formatter_name) const = 0;
    virtual boost::optional<std::string> get_inclusion_directive(
        const yarn::name& n, const std::string& formatter_name) const = 0;
};

class legacy_builder_impl : public builder_impl {
public:
    legacy_builder_impl(const enablement_repository& erp,
        const inclusion_directives_repository& drp);

public:
    bool is_enabled(const yarn::name& n,
        const std::string& formatter_name) const override;
    boost::optional<std::string> get_inclusion_directive(
        const yarn::name& n, const std::string& formatter_name) const override;

private:
    const enablement_repository& enablement_repository_;
    const inclusion_directives_repository& directives_repository_;
};

legacy_builder_impl::legacy_builder_impl(const enablement_repository& erp,
    const inclusion_directives_repository& drp)
    : enablement_repository_(erp), directives_repository_(drp) {}

bool legacy_builder_impl::is_enabled(const yarn::name& n,
    const std::string& formatter_name) const {
    const auto& en(enablement_repository_.by_name());
    const auto i(en.find(n));
    if (i == en.end()) {
        BOOST_LOG_SEV(lg, error) << name_not_found << n.id();
        BOOST_THROW_EXCEPTION(building_error(name_not_found + n.id()));
    }

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end()) {
        BOOST_LOG_SEV(lg, debug) << formatter_name_not_found << formatter_name
                                 << " element id: " << n.id();

        // FIXME: hack
        BOOST_LOG_SEV(lg, debug) << "Trying by facet name.";

        for (const auto pair : i->second) {
            if (boost::starts_with(pair.first, formatter_name)) {
                BOOST_LOG_SEV(lg, debug) << "Using: " << pair.first
                                         << " status: " << pair.second;
                return pair.second;
            }
        }

        BOOST_LOG_SEV(lg, error) << formatter_name_not_found << formatter_name
                                 << " element id: " << n.id();
        BOOST_THROW_EXCEPTION(
            building_error(formatter_name_not_found + formatter_name));
    }

    const bool r(j->second);
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Formatter disabled. Formatter: "
                                 << formatter_name << " on type: "
                                 << n.id() << "'";
    }
    return r;
}

boost::optional<std::string> legacy_builder_impl::get_inclusion_directive(
    const yarn::name& n, const std::string& formatter_name) const {
    const auto& idn(directives_repository_.by_name());
    const auto i(idn.find(n.id()));
    if (i == idn.end())
        return boost::optional<std::string>();

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end())
        return boost::optional<std::string>();

    return j->second;
}

class new_builder_impl : public builder_impl {
public:
    new_builder_impl(const std::unordered_map<std::string,
        std::unordered_map<std::string, std::string>
        >& inclusion_directives,
        const std::unordered_map<std::string, formattable>& formattables);

public:
    bool is_enabled(const yarn::name& n,
        const std::string& formatter_name) const override;
    boost::optional<std::string> get_inclusion_directive(
        const yarn::name& n, const std::string& formatter_name) const override;

private:
    const std::unordered_map<
    std::string,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives_;
    const std::unordered_map<std::string, formattable>& formattables_;
};

new_builder_impl::new_builder_impl(const std::unordered_map<std::string,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives,
    const std::unordered_map<std::string, formattable>& formattables) :
    inclusion_directives_(inclusion_directives), formattables_(formattables) {}

bool new_builder_impl::is_enabled(const yarn::name& n,
    const std::string& formatter_name) const {

    const auto i(formattables_.find(n.id()));
    if (i == formattables_.end()) {
        BOOST_LOG_SEV(lg, error) << name_not_found << n.id();
        BOOST_THROW_EXCEPTION(building_error(name_not_found + n.id()));
    }

    const auto& formattable(i->second);
    const auto& fc(formattable.configuration().formatter_configuration());
    const auto j(fc.find(formatter_name));
    if (j == fc.end()) {
        BOOST_LOG_SEV(lg, debug) << formatter_name_not_found << formatter_name
                                 << " element id: " << n.id();

        // FIXME: hack to cope with canonical formatter.
        BOOST_LOG_SEV(lg, debug) << "Trying by facet name.";

        for (const auto pair : fc) {
            if (boost::starts_with(pair.first, formatter_name)) {
                BOOST_LOG_SEV(lg, debug) << "Using: " << pair.first
                                         << " status: "
                                         << pair.second.enabled();
                return pair.second.enabled();
            }
        }

        BOOST_LOG_SEV(lg, error) << formatter_name_not_found << formatter_name
                                 << " element id: " << n.id();
        BOOST_THROW_EXCEPTION(
            building_error(formatter_name_not_found + formatter_name));
    }

    const bool r(j->second.enabled());
    if (!r) {
        BOOST_LOG_SEV(lg, debug) << "Formatter disabled. Formatter: "
                                 << formatter_name << " on type: "
                                 << n.id() << "'";
    }
    return r;
}

boost::optional<std::string> new_builder_impl::get_inclusion_directive(
    const yarn::name& n, const std::string& formatter_name) const {

    const auto i(inclusion_directives_.find(n.id()));
    if (i == inclusion_directives_.end())
        return boost::optional<std::string>();

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end())
        return boost::optional<std::string>();

    return j->second;
}

inclusion_dependencies_builder::
inclusion_dependencies_builder(const enablement_repository& erp,
    const inclusion_directives_repository& idrp)
    : impl_(new legacy_builder_impl(erp, idrp)) {}

inclusion_dependencies_builder::inclusion_dependencies_builder(
    const std::unordered_map<std::string,
    std::unordered_map<std::string, std::string>
    >& inclusion_directives,
    const std::unordered_map<std::string, formattable>& formattables)
    : impl_(new new_builder_impl(inclusion_directives, formattables)) {}

boost::optional<std::string>
inclusion_dependencies_builder::get_inclusion_directive(
    const yarn::name& n, const std::string& formatter_name) const {
    return impl_->get_inclusion_directive(n, formatter_name);
}

inclusion_dependencies_builder::special_includes
inclusion_dependencies_builder::make_special_includes(
    const yarn::object& o) const {
    special_includes r;
    const auto lambda([&](const std::list<yarn::name> names) {
            if (names.empty())
                return;

            for (const auto& n : names) {
                const auto sn(n.simple());
                if (sn == bool_type || sn == double_type || sn == float_type)
                    r.requires_stream_manipulators = true;
                else if (sn == string_type)
                    r.has_std_string = true;
                else if (sn == variant_type)
                    r.has_variant = true;
                else if (sn == pair_type)
                    r.has_std_pair = true;
                else if (sn == ptree_type)
                    r.has_ptree = true;
                else if (sn == path_type)
                    r.has_path = true;
                else if (sn == date_type)
                    r.has_date = true;
                else if (sn == ptime_type)
                    r.has_ptime = true;
            }
        });

    lambda(o.opaque_associations());
    lambda(o.transparent_associations());

    return r;
}

bool inclusion_dependencies_builder::is_enabled(const yarn::name& n,
    const std::string& formatter_name) const {
    return impl_->is_enabled(n, formatter_name);
}

void inclusion_dependencies_builder::
add(const std::string& inclusion_directive) {
    if (inclusion_directive.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_directive));
    }
    inclusion_dependencies_.push_back(inclusion_directive);
}

void inclusion_dependencies_builder::
add(const yarn::name& n, const std::string& formatter_name) {
    if (!is_enabled(n, formatter_name))
        return;

    const auto id(get_inclusion_directive(n, formatter_name));
    if (id)
        add(*id);
}

void inclusion_dependencies_builder::add(const boost::optional<yarn::name>& n,
    const std::string& formatter_name) {

    if (!n)
        return;

    add(*n, formatter_name);
}

void inclusion_dependencies_builder::
add(const std::list<yarn::name>& names, const std::string& formatter_name) {
    for (const auto& n : names)
        add(n, formatter_name);
}

std::list<std::string> inclusion_dependencies_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Built inclusion dependencies for formatter.";
    BOOST_LOG_SEV(lg, debug) << "Result: " << inclusion_dependencies_;

    return inclusion_dependencies_;
}

} } } }
