// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

namespace odb
{
  // transform_components_key
  //

  inline
  bool access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_pgsql >::
  get_null (const image_type& i)
  {
    bool r (true);
    r = r && composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::get_null (i.parent_id_value);
    r = r && composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::get_null (i.component_id_value);
    return r;
  }

  inline
  void access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_pgsql >::
  set_null (image_type& i,
            pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::set_null (i.parent_id_value, sk);
    composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::set_null (i.component_id_value, sk);
  }
}

