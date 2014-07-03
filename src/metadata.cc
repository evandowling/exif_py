#include <Python.h>
#include <exiv2/exiv2.hpp>
#include <string>
#include <cassert>

PyObject* GetMetadata(const char* path) {
  /* 
    There are a few error modes that can occur here, for performance
    reasons we don't want to let the Exiv2 exceptions to propagate for
    expected outcomes such as: FileMissing and UnexpectedFileType.
    We do want to catch exceptions anyway to prevent crashes
  */
  try {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);

    if (!image.get()) {
      std::string message = std::string("Could not open path ") + path;
      PyErr_SetString(PyExc_IOError, message.c_str());
      return NULL;
    }

    image->readMetadata();
    PyObject* result = PyDict_New();

    Exiv2::ExifData &exifData = image->exifData();

    Exiv2::ExifData::const_iterator end = exifData.end();
    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
      PyObject* key = PyString_FromString(i->key().c_str());
      PyObject* value = PyString_FromString(i->value().toString().c_str());
      PyDict_SetItem(result, key, value);
    }

    return result;
  } catch (Exiv2::Error& e) {
    PyErr_SetString(PyExc_AssertionError, e.what());
    return NULL;
  }
}
