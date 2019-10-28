// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

namespace odb
{
  // run_id
  //

  inline
  bool access::composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::
  get_null (const image_type& i)
  {
    bool r (true);
    r = r && i.value_null;
    return r;
  }

  inline
  void access::composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::
  set_null (image_type& i,
            pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    i.value_null = true;
  }
}

