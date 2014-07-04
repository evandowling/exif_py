#include <Python.h>
#include "metadata.h"

static PyObject*
set_exif_metadata(PyObject* self, PyObject* args) {
  const char* path;
  PyObject* exif_data;
  if (!PyArg_ParseTuple(args, "sO", &path, &exif_data)) {
    return NULL;
  }

  return SetMetadata(path, exif_data);
}

static PyObject*
exif_metadata(PyObject* self, PyObject* args) {
  const char* path;
  if (!PyArg_ParseTuple(args, "s", &path)) {
    return NULL;
  }

  return GetMetadata(path);
}

static PyMethodDef ImageMethods[] = {
    {"Metadata",  exif_metadata, METH_VARARGS,
     "Extract exif metadata from an image"},
    {"SetMetadata", set_exif_metadata, METH_VARARGS,
     "Write exif metadata to an image."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initexif_py(void)
{
  (void) Py_InitModule("exif_py", ImageMethods);
}
