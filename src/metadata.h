#ifndef _IMAGES_METADATA_METADATA_H_
#define _IMAGES_METADATA_METADATA_H_

#include <Python.h>

PyObject* GetMetadata(const char* path);
PyObject* SetMetadata(const char* path, PyObject* metadata);

#endif // _IMAGES_METADATA_METADATA_H_
