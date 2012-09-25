/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DIA_DOMAIN_CHILD_NODE_HPP
#define DOGEN_DIA_DOMAIN_CHILD_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class child_node_serializer; } }

/**
 * @brief Represents a child_node in a diagram.
 */
class child_node {
public:
    child_node() = default;
    child_node(const child_node&) = default;
    ~child_node() = default;
    child_node(child_node&&) = default;
    child_node& operator=(const child_node&) = default;

private:
    friend class dogen::dia::serialization::detail::child_node_serializer;

public:
    explicit child_node(std::string parent) : parent_(parent) { }

public:
    /**
     * @brief
     */
    /**@{*/
    std::string parent() const { return(parent_); }
    void parent(std::string parent) { parent_ = parent; }
    /**@}*/

public:
    bool operator==(const dogen::dia::child_node& value) const {
        return(parent_ == value.parent());
    }

    bool operator!=(const dogen::dia::child_node& value) const {
        return(!this->operator==(value));
    }

private:
    std::string parent_;
};

} }

#endif
