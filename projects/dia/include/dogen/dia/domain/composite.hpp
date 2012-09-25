/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_COMPOSITE_HPP
#define DOGEN_DIA_DOMAIN_COMPOSITE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class composite_serializer; } }

class attribute;

/**
 * @brief Attribute value which is made up of other attributes.
 */
class composite {
public:
    composite() = default;
    composite(const composite&) = default;
    ~composite() = default;
    composite(composite&&) = default;
    composite& operator=(const composite&) = default;

private:
    friend class dogen::dia::serialization::detail::composite_serializer;

public:
    composite(std::string type,
        std::vector<boost::shared_ptr<attribute> > value,
        boost::shared_ptr<composite> inner_composite);

public:
    /**
     * @brief Type of the composite node
     */
    /**@{*/
    std::string type() const { return type_; }
    void type(std::string value) { type_ = value; }
    /**@}*/

    /**
     * @brief Underlying Dia attributes.
     */
    /**@{*/
    std::vector<boost::shared_ptr<attribute> > value() const;
    void value(std::vector<boost::shared_ptr<attribute> > value);
    /**@}*/

    /**
     * @brief Some composites contain an inner composite field.
     */
    /**@{*/
    boost::shared_ptr<composite> inner_composite() const;
    void inner_composite(boost::shared_ptr<composite> value);
    /**@}*/


public:
    bool operator==(const dogen::dia::composite& value) const;

    bool operator!=(const dogen::dia::composite& value) const {
        return(!this->operator==(value));
    }

private:
    std::string type_;
    std::vector<boost::shared_ptr<attribute> > value_;
    boost::shared_ptr<composite> inner_composite_;
};

} }

#endif
