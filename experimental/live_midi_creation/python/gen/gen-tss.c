// this file is generated! do not modify
#include "aubio-types.h"

// tss structure
typedef struct{
    PyObject_HEAD
    // pointer to aubio object
    aubio_tss_t *o;
    // input parameters
    uint_t buf_size; uint_t hop_size;
    // do input vectors
    cvec_t  input;
    // output results
    PyObject *trans; cvec_t c_trans;
    PyObject *stead; cvec_t c_stead;
} Py_tss;

// TODO: add documentation
static char Py_tss_doc[] = "undefined";

// new tss
static PyObject *
Py_tss_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
    Py_tss *self;

    uint_t buf_size = 0;
    uint_t hop_size = 0;
    static char *kwlist[] = { "buf_size", "hop_size", NULL };
    if (!PyArg_ParseTupleAndKeywords (args, kwds, "|II", kwlist,
              &buf_size, &hop_size)) {
        return NULL;
    }

    self = (Py_tss *) pytype->tp_alloc (pytype, 0);
    if (self == NULL) {
        return NULL;
    }

    self->buf_size = Py_default_vector_length;
    if ((sint_t)buf_size > 0) {
        self->buf_size = buf_size;
    } else if ((sint_t)buf_size < 0) {
        PyErr_SetString (PyExc_ValueError, "can not use negative value for buf_size");
        return NULL;
    }

    self->hop_size = Py_default_vector_length / 2;
    if ((sint_t)hop_size > 0) {
        self->hop_size = hop_size;
    } else if ((sint_t)hop_size < 0) {
        PyErr_SetString (PyExc_ValueError, "can not use negative value for hop_size");
        return NULL;
    }

    return (PyObject *)self;
}

// init tss
static int
Py_tss_init (Py_tss * self, PyObject * args, PyObject * kwds)
{

  self->o = new_aubio_tss(self->buf_size, self->hop_size);

  // return -1 and set error string on failure
  if (self->o == NULL) {
    PyErr_Format (PyExc_RuntimeError, "failed creating tss");
    return -1;
  }

  // TODO get internal params after actual object creation?

  // create outputs
  self->trans = new_py_cvec(self->buf_size);
  self->stead = new_py_cvec(self->buf_size);

  return 0;
}

// del tss
static void
Py_tss_del  (Py_tss * self, PyObject * unused)
{
  if (self->trans) {
    Py_DECREF(self->trans);
  }
  if (self->stead) {
    Py_DECREF(self->stead);
  }
  if (self->o) {
    del_aubio_tss(self->o);
  }
  Py_TYPE(self)->tp_free((PyObject *) self);
}

// do tss
static PyObject*
Pyaubio_tss_do  (Py_tss * self, PyObject * args)
{
    PyObject *outputs;
    PyObject *py_input;
    if (!PyArg_ParseTuple (args, "O", &py_input)) {
        return NULL;
    }

    if (!PyAubio_PyCvecToCCvec(py_input, &(self->input))) {
        return NULL;
    }

    if (self->input.length != self->buf_size / 2 + 1) {
        PyErr_Format (PyExc_ValueError,
            "input size of tss should be %d, not %d",
            self->buf_size / 2 + 1, self->input.length);
        return NULL;
    }

    Py_INCREF(self->trans);
    if (!PyAubio_PyCvecToCCvec(self->trans, &(self->c_trans))) {
        return NULL;
    }

    Py_INCREF(self->stead);
    if (!PyAubio_PyCvecToCCvec(self->stead, &(self->c_stead))) {
        return NULL;
    }

    aubio_tss_do(self->o, &(self->input), &(self->c_trans), &(self->c_stead));

    outputs = PyTuple_New(2);
    PyTuple_SetItem( outputs, 0, self->trans);
    PyTuple_SetItem( outputs, 1, self->stead);

    return outputs;
}

static PyMemberDef Py_tss_members[] = {
  {"buf_size", T_INT, offsetof (Py_tss, buf_size), READONLY, "TODO documentation"},
  {"hop_size", T_INT, offsetof (Py_tss, hop_size), READONLY, "TODO documentation"},
  {NULL}, // sentinel
};

// tss setters

static PyObject *
Pyaubio_tss_set_threshold (Py_tss *self, PyObject *args)
{
  uint_t err = 0;
  smpl_t threshold;

  if (!PyArg_ParseTuple (args, "f", &threshold)) {
    return NULL;
  }
  err = aubio_tss_set_threshold (self->o, threshold);

  if (err > 0) {
    if (PyErr_Occurred() == NULL) {
      PyErr_SetString (PyExc_ValueError, "error running aubio_tss_set_threshold");
    } else {
      // change the RuntimeError into ValueError
      PyObject *type, *value, *traceback;
      PyErr_Fetch(&type, &value, &traceback);
      PyErr_Restore(PyExc_ValueError, value, traceback);
    }
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyObject *
Pyaubio_tss_set_alpha (Py_tss *self, PyObject *args)
{
  uint_t err = 0;
  smpl_t alpha;

  if (!PyArg_ParseTuple (args, "f", &alpha)) {
    return NULL;
  }
  err = aubio_tss_set_alpha (self->o, alpha);

  if (err > 0) {
    if (PyErr_Occurred() == NULL) {
      PyErr_SetString (PyExc_ValueError, "error running aubio_tss_set_alpha");
    } else {
      // change the RuntimeError into ValueError
      PyObject *type, *value, *traceback;
      PyErr_Fetch(&type, &value, &traceback);
      PyErr_Restore(PyExc_ValueError, value, traceback);
    }
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyObject *
Pyaubio_tss_set_beta (Py_tss *self, PyObject *args)
{
  uint_t err = 0;
  smpl_t beta;

  if (!PyArg_ParseTuple (args, "f", &beta)) {
    return NULL;
  }
  err = aubio_tss_set_beta (self->o, beta);

  if (err > 0) {
    if (PyErr_Occurred() == NULL) {
      PyErr_SetString (PyExc_ValueError, "error running aubio_tss_set_beta");
    } else {
      // change the RuntimeError into ValueError
      PyObject *type, *value, *traceback;
      PyErr_Fetch(&type, &value, &traceback);
      PyErr_Restore(PyExc_ValueError, value, traceback);
    }
    return NULL;
  }
  Py_RETURN_NONE;
}

// tss getters

static PyMethodDef Py_tss_methods[] = {
  {"set_threshold", (PyCFunction) Pyaubio_tss_set_threshold,
    METH_VARARGS, ""},
  {"set_alpha", (PyCFunction) Pyaubio_tss_set_alpha,
    METH_VARARGS, ""},
  {"set_beta", (PyCFunction) Pyaubio_tss_set_beta,
    METH_VARARGS, ""},
  {NULL} /* sentinel */
};

PyTypeObject Py_tssType = {
  //PyObject_HEAD_INIT (NULL)
  //0,
  PyVarObject_HEAD_INIT (NULL, 0)
  "aubio.tss",
  sizeof (Py_tss),
  0,
  (destructor) Py_tss_del,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (ternaryfunc)Pyaubio_tss_do,
  0,
  0,
  0,
  0,
  Py_TPFLAGS_DEFAULT,
  Py_tss_doc,
  0,
  0,
  0,
  0,
  0,
  0,
  Py_tss_methods,
  Py_tss_members,
  0,
  0,
  0,
  0,
  0,
  0,
  (initproc) Py_tss_init,
  0,
  Py_tss_new,
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
