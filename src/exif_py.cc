#include <Python.h>
#include "metadata.h"

static PyObject*
exif_metadata(PyObject* self, PyObject* args) {
  const char* path;
  if (!PyArg_ParseTuple(args, "s", &path))
    return NULL;

  return GetMetadata(path);
}

static PyMethodDef ImageMethods[] = {
    {"Metadata",  exif_metadata, METH_VARARGS,
     "Extract exif metadata from an image."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initexif_py(void)
{
  (void) Py_InitModule("exif_py", ImageMethods);
}
