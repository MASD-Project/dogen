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
#ifndef DOGEN_SML_TO_OM_TYPES_TRANSFORMER_HPP
#define DOGEN_SML_TO_OM_TYPES_TRANSFORMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <tuple>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/sml/types/type.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/module.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/nested_qname.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml_to_om/types/context.hpp"

namespace dogen {
namespace sml_to_om {

/**
 * @brief Transforms an SML type into its corresponding OM type.
 */
class transformer : public sml::type_visitor {
public:
    transformer() = delete;
    transformer(const transformer&) = default;
    transformer& operator=(const transformer&) = delete;
    transformer(transformer&& rhs) = default;

public:
    transformer(const sml::model& m, context& c);
    virtual ~transformer() noexcept { }

private:
    /**
     * @brief Collects all the properties associated with a concept,
     * and any otheer concepts it may refine.
     */
    void properties_for_concept(const sml::qname& qn,
        std::list<sml::property>& properties,
        std::unordered_set<sml::qname>& processed_qnames) const;

private:
    using type_visitor::visit;
    void visit(const dogen::sml::service& s) override;
    void visit(const dogen::sml::factory& f) override;
    void visit(const dogen::sml::repository& r) override;
    void visit(const dogen::sml::enumeration& e) override;
    void visit(const dogen::sml::value_object& vo) override;
    void visit(const dogen::sml::keyed_entity& ke) override;
    void visit(const dogen::sml::entity& e) override;

public:
    /**
     * @brief Transforms an SML type into the appropriate C++ object.
     */
    void from_type(const sml::type& t);

    /**
     * @brief Transforms a SML module.
     */
    void from_module(const sml::module& m);

private:
    const sml::model& model_;
    context& context_;
};

} }

#endif
