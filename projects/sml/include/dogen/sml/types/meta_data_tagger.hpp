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
#ifndef DOGEN_SML_TYPES_META_DATA_TAGGER_HPP
#define DOGEN_SML_TYPES_META_DATA_TAGGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <memory>
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml/types/meta_data_writer.hpp"
#include "dogen/sml/types/flat_name_builder.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/tags.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Generate all meta data tags across the model.
 */
class meta_data_tagger : private sml::type_visitor {
public:
    meta_data_tagger() = default;
    meta_data_tagger(const meta_data_tagger&) = default;
    meta_data_tagger(meta_data_tagger&&) = default;

public:
    virtual ~meta_data_tagger() noexcept { }

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
     * @brief Copies across all tags from the model into the taggable
     * using the writer.
     */
    void copy_model_tags(meta_data_writer& writer) const;

    /**
     * @brief Returns true if an explicit move constructor is
     * required, false otherwise.
     */
    bool generate_explicit_move_constructor(const nested_qname& nqn) const;

private:
    using sml::type_visitor::visit;
    void visit(sml::primitive& p) const override;
    void visit(sml::enumeration& e) const override;
    void visit(sml::object& vo) const override;

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
     * @brief Adds meta-data to the property supplied.
     */
    void tag(property& p) const;

    /**
     * @brief Adds meta-data to the object supplied.
     */
    void tag(object& o) const;

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
    flat_name_builder builder_;
};

} }

#endif
