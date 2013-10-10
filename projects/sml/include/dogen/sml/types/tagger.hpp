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
#ifndef DOGEN_SML_TYPES_TAGGER_HPP
#define DOGEN_SML_TYPES_TAGGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <memory>
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml/types/tag_adaptor.hpp"
#include "dogen/sml/types/tag_router.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/tags.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Generate all meta data tags across the model.
 */
class tagger : private sml::type_visitor {
public:
    tagger() = default;
    ~tagger() noexcept = default;
    tagger(const tagger&) = default;
    tagger(tagger&&) = default;

private:
    class context;

private:
    /**
     * @brief Tag the model with all the options chosen in the
     * application settings.
     *
     * This ensures backwards compatibility until we remove these
     * options from the configuration model.
     *
     * @deprecated Needed whilst settings contain options that should
     * really be in the meta-data.
     */
    void from_settings(const config::cpp_settings& s, model& m) const;

    /**
     * @brief Returns true if the facet is enabled in the settings,
     * false otherwise.
     *
     * @deprecated Needed whilst settings contain options that should
     * really be in the meta-data.
     */
    bool is_facet_enabled(
        const std::set<config::cpp_facet_types>& enabled_facets,
        const config::cpp_facet_types facet) const;

private:
    /**
     * @brief Returns a C++ qualified name for the SML qname.
     */
    std::string cpp_qualified_name(const sml::qname& qn) const;

    /**
     * @brief Returns the file name for the given qname and facet.
     */
    std::string filename_for_qname(const tag_adaptor& adaptor,
        const bool is_header, const qname& qn,
        const std::string& facet_directory,
        const std::string& facet_postfix,
        const std::string& additional_postfix) const;

    /**
     * @brief Copies across all tags from the model into the taggable
     * via the router.
     */
    void copy_model_tags(tag_router& router) const;

private:
    using sml::type_visitor::visit;
    void visit(sml::primitive& p) const override;
    void visit(sml::enumeration& e) const override;
    void visit(sml::service& s) const override;
    void visit(sml::factory& f) const override;
    void visit(sml::repository& r) const override;
    void visit(sml::value_object& vo) const override;
    void visit(sml::keyed_entity& ke) const override;
    void visit(sml::entity& e) const override;

public:
    /**
     * @brief Adds meta-data to the type supplied.
     */
    void operator()(type& t) const;

    /**
     * @brief Adds meta-data to the module supplied.
     */
    void operator()(module& m) const;

    /**
     * @brief Adds meta-data to the concept supplied.
     */
    void operator()(concept& c) const;

public:
    /**
     * @brief Adds meta-data to the abstract object supplied.
     */
    void tag(abstract_object& o) const;

    /**
     * @brief Adds meta-data to the model supplied.
     */
    void tag(model& m) const;

    /**
     * @brief Adds meta-data to the model supplied.
     *
     * @deprecated This method is only made available for backwards
     * compatibility.
     */
    void tag(const config::cpp_settings& s, model& m) const;

private:
    mutable std::shared_ptr<context> context_;
};

} }

#endif
