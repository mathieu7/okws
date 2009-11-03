// -*-c++-*-
/* $Id: parr.h 2784 2007-04-20 16:32:00Z max $ */

#pragma once

#include "pub3expr.h"

namespace pub3 {

  //-----------------------------------------------------------------------

  //-----------------------------------------------------------------------

  class env_t {
  public:

    enum { FRAME_UNIVERSALS = 0, FRAME_GLOBALS = 1 };

    env_t (ptr<bindtab_t> u);
    size_t push_locals (ptr<bind_interface_t> t);
    size_t push_universal_refs (ptr<bind_interface_t> t);
    void pop_to (size_t s);
    ptr<const expr_t> lookup_val (const str &nm) const;
    size_t stack_size () const;
    ptr<mref_t> lookup_ref (const str &nm) const;
    void add_global_binding (const str &nm, ptr<expr_t> v);

    typedef enum { LAYER_NONE = -1,
		   LAYER_UNIVERSALS = 0,
		   LAYER_GLOBALS = 1,
		   LAYER_LOCALS = 2,
		   LAYER_UNIREFS = 3 } layer_type_t;

    size_t push_bindings (ptr<bind_interface_t> t, layer_type_t lt);
    
    struct stack_layer_t {
      stack_layer_t (ptr<bind_interface_t> b, layer_type_t t) 
	: _bindings (b), _typ (t) {}
      stack_layer_t () : _typ (LAYER_NONE) {}
      ptr<bind_interface_t> _bindings;
      layer_type_t _typ;
    };

  protected:
    ptr<bindtab_t> _universals;
    ptr<bindtab_t> _globals;
    vec<stack_layer_t> _stack;
  };

  //-----------------------------------------------------------------------

  typedef event<xpub_status_t>::ref status_ev_t;

  //-----------------------------------------------------------------------

  class output_t {
  public:
    output_t () {}
    virtual ~output_t () {}
    virtual void output_err (location_t loc, str msg) = 0;
    static ptr<output_t> alloc (zbuf *z);
  };

  //-----------------------------------------------------------------------

  class eval_t {
  public:

    enum { EVAL_INIT = -2, EVAL_DONE = -1 };

    eval_t (ptr<env_t> e, ptr<output_t> o); 
    ~eval_t ();

    ptr<output_t> output () const { return _output; }
    ptr<env_t> env () { return _env; }
    ptr<const env_t> env () const { return _env; }

    bool set_loud (bool b);
    bool loud () const { return _loud && !_silent; }
    bool set_silent (bool b);

    ptr<const expr_t> lookup_val (const str &nm) const;
    ptr<mref_t> lookup_ref (const str &nm) const;

    location_t location (lineno_t l) const;
    void report_error (lineno_t l);
    void report_error (str e, location_t l);
    void report_error (str e, lineno_t l);

  private:

    ptr<env_t> _env;
    ptr<output_t> _output;
    bool _loud;
    bool _silent;
    ssize_t _stack_p;
  };

  //-----------------------------------------------------------------------
};