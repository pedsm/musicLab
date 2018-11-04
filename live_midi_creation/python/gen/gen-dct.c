// this file is generated! do not modify
#include "aubio-types.h"

// dct structure
typedef struct{
    PyObject_HEAD
    // pointer to aubio object
    aubio_dct_t *o;
    // input parameters
    uint_t size;
    // do input vectors
    fvec_t  input;
    // output results
    PyObject *dct_output; fvec_t c_dct_output;
    PyObject *idct_output; fvec_t c_idct_output;
} Py_dct;

// TODO: add documentation
static char Py_dct_doc[] = "undefined";

// new dct
static PyObject *
Py_dct_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
    Py_dct *self;

    uint_t size = 0;
    static char *kwlist[] = { "size", NULL };
    if (!PyArg_ParseTupleAndKeywords (args, kwds, "|I", kwlist,
              &size)) {
        return NULL;
    }

    self = (Py_dct *) pytype->tp_alloc (pytype, 0);
    if (self == NULL) {
        return NULL;
    }

    self->size = Py_default_vector_length;
    if ((sint_t)size > 0) {
        self->size = size;
    } else if ((sint_t)size < 0) {
        PyErr_SetString (PyExc_ValueError, "can not use negative value for size");
        return NULL;
    }

    return (PyObject *)self;
}

// init dct
static int
Py_dct_init (Py_dct * self, PyObject * args, PyObject * kwds)
{

  self->o = new_aubio_dct(self->size);

  // return -1 and set error string on failure
  if (self->o == NULL) {
    PyErr_Format (PyExc_RuntimeError, "failed creating dct");
    return -1;
  }

  // TODO get internal params after actual object creation?

  // create outputs
  self->dct_output = new_py_fvec(self->size);
  self->idct_output = new_py_fvec(self->size);

  return 0;
}

// del dct
static void
Py_dct_del  (Py_dct * self, PyObject * unused)
{
  if (self->dct_output) {
    Py_DECREF(self->dct_output);
  }
  if (self->idct_output) {
    Py_DECREF(self->idct_output);
  }
  if (self->o) {
    del_aubio_dct(self->o);
  }
  Py_TYPE(self)->tp_free((PyObject *) self);
}

// do dct
static PyObject*
Pyaubio_dct_do  (Py_dct * self, PyObject * args)
{
    PyObject *outputs;
    PyObject *py_input;
    if (!PyArg_ParseTuple (args, "O", &py_input)) {
        return NULL;
    }

    if (!PyAubio_ArrayToCFvec(py_input, &(self->input))) {
        return NULL;
    }

    // TODO: check input sizes

    Py_INCREF(self->dct_output);
    if (!PyAubio_ArrayToCFvec(self->dct_output, &(self->c_dct_output))) {
        return NULL;
    }

    aubio_dct_do(self->o, &(self->input), &(self->c_dct_output));

    outputs = self->dct_output;

    return outputs;
}

// do dct
static PyObject*
Pyaubio_dct_rdo  (Py_dct * self, PyObject * args)
{
    PyObject *outputs;
    PyObject *py_input;
    if (!PyArg_ParseTuple (args, "O", &py_input)) {
        return NULL;
    }

    if (!PyAubio_ArrayToCFvec(py_input, &(self->input))) {
        return NULL;
    }

    // TODO: check input sizes

    Py_INCREF(self->idct_output);
    if (!PyAubio_ArrayToCFvec(self->idct_output, &(self->c_idct_output))) {
        return NULL;
    }

    aubio_dct_rdo(self->o, &(self->input), &(self->c_idct_output));

    outputs = self->idct_output;

    return outputs;
}

static PyMemberDef Py_dct_members[] = {
  {"size", T_INT, offsetof (Py_dct, size), READONLY, "TODO documentation"},
  {NULL}, // sentinel
};

// dct setters

// dct getters

static PyMethodDef Py_dct_methods[] = {
  {"rdo", (PyCFunction) Pyaubio_dct_rdo,
    METH_VARARGS, ""},
  {NULL} /* sentinel */
};

PyTypeObject Py_dctType = {
  //PyObject_HEAD_INIT (NULL)
  //0,
  PyVarObject_HEAD_INIT (NULL, 0)
  "aubio.dct",
  sizeof (Py_dct),
  0,
  (destructor) Py_dct_del,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (ternaryfunc)Pyaubio_dct_do,
  0,
  0,
  0,
  0,
  Py_TPFLAGS_DEFAULT,
  Py_dct_doc,
  0,
  0,
  0,
  0,
  0,
  0,
  Py_dct_methods,
  Py_dct_members,
  0,
  0,
  0,
  0,
  0,
  0,
  (initproc) Py_dct_init,
  0,
  Py_dct_new,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
};
