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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_ABSTRACT_PROFILE_ENTRY_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_ABSTRACT_PROFILE_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.variability/types/meta_model/configuration_fwd.hpp"

namespace dogen::assets::meta_model::variability {

class abstract_profile_entry {
public:
    abstract_profile_entry() = default;
    abstract_profile_entry(const abstract_profile_entry&) = default;
    abstract_profile_entry(abstract_profile_entry&&) = default;

    virtual ~abstract_profile_entry() noexcept = 0;

public:
    abstract_profile_entry(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const dogen::assets::meta_model::name& name,
        const std::string& key,
        const std::list<std::string>& value);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the technical space in question, e.g. Doxygen for C++, JavaDoc for Java,
     * etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::assets::meta_model::name& name() const;
    dogen::assets::meta_model::name& name();
    void name(const dogen::assets::meta_model::name& v);
    void name(const dogen::assets::meta_model::name&& v);
    /**@}*/

    const std::string& key() const;
    std::string& key();
    void key(const std::string& v);
    void key(const std::string&& v);

    const std::list<std::string>& value() const;
    std::list<std::string>& value();
    void value(const std::list<std::string>& v);
    void value(const std::list<std::string>&& v);

protected:
    bool compare(const abstract_profile_entry& rhs) const;
public:
    virtual bool equals(const abstract_profile_entry& other) const = 0;

protected:
    void swap(abstract_profile_entry& other) noexcept;

private:
    std::string documentation_;
    boost::shared_ptr<dogen::variability::meta_model::configuration> configuration_;
    dogen::assets::meta_model::name name_;
    std::string key_;
    std::list<std::string> value_;
};

inline abstract_profile_entry::~abstract_profile_entry() noexcept { }

inline bool operator==(const abstract_profile_entry& lhs, const abstract_profile_entry& rhs) {
    return lhs.equals(rhs);
}

}

#endif
