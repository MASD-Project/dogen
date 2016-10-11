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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_INCLUSION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_configuration.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Generates all inclusion dependencies.
 *
 * In formattables we use two similar terms with very different
 * meanings: inclusion directive and inclusion dependency.
 *
 * An inclusion directive is a string with delimiters but without the
 * #include pragma. For example "a/b/c.hpp" and <a/b/c.hpp> are
 * inclusion directives; note that the quotes and angle brackets are
 * part of the directive. There should be an inclusion directive
 * associated with every pair (name, formatter name). The inclusion
 * directive repository contains the complete set of inclusion
 * directives - the inclusion directives universe if you'd like.
 *
 * Inclusion dependencies are a set of inclusion directives. They are
 * also associated with a pair (name, formatter). The inclusion
 * dependencies for each formatter are created by the formatter
 * themselves since they are relative to the formatter (i.e. for the
 * same element different formatters will generate different
 * dependencies). It uses the inclusion directives precomputed from
 * the model to assemble the inclusion dependencies that the formatter
 * needs in order to generate a compilable C++ file.
 *
 */
class inclusion_expander {
private:
    struct formattater_type_group {
        annotations::type inclusion_directive;
        annotations::type inclusion_required;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const formattater_type_group& v);

    struct type_group {
        annotations::type inclusion_required;
        std::unordered_map<std::string, formattater_type_group>
        formattaters_type_group;
    };
    friend std::ostream& operator<<(std::ostream& s,
        const type_group& v);


    type_group make_type_group(const annotations::repository& arp,
        const formatters::container& fc) const;

    bool make_top_level_inclusion_required(const type_group& tg,
        const annotations::annotation& o) const;

    inclusion_directive_configuration make_inclusion_directive_configuration(
        const type_group& tg,const std::string& formatter_name,
        const annotations::annotation& o) const;

private:
    typedef std::forward_list<
    std::shared_ptr<formatters::file_formatter_interface>
    > formatter_list_type;

    formatter_list_type remove_non_includible_formatters(
        const formatter_list_type& formatters) const;

    std::unordered_map<std::type_index, formatter_list_type>
    includible_formatters_by_type_index(const formatters::container& fc) const;

private:
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

private:
    typedef std::unordered_map<std::string,
                               std::unordered_map<std::string, std::string>
                               >
    inclusion_directives_container_type;

    void insert_inclusion_directive(
        const std::string& id, const std::string& formatter_name,
        const std::string& directive,
        inclusion_directives_container_type& idc) const;

    void compute_inclusion_directives(const type_group& tg,
        const yarn::element& e, const formatter_list_type& formatters,
        const locator& l, inclusion_directives_container_type& idc) const;

    inclusion_directives_container_type compute_inclusion_directives(
        const type_group& tg, const formatters::container& fc,
        const locator& l,
        const std::unordered_map<std::string, formattable>& formattables) const;

private:
    typedef std::unordered_map<std::string, std::list<std::string>>
        element_inclusion_dependencies_type;

    element_inclusion_dependencies_type compute_inclusion_dependencies(
        const formatters::container& fc,
        const inclusion_dependencies_builder_factory& f,
        const yarn::element& e) const;

    void populate_inclusion_dependencies(const formatters::container& fc,
        const inclusion_directives_container_type& idc,
        std::unordered_map<std::string, formattable>& formattables) const;

public:
    void expand(const annotations::repository& arp,
        const formatters::container& fc, const locator& l, model& fm) const;
};

} } } }

#endif
