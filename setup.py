from distutils.core import setup, Extension

exif_py = Extension('exif_py',
                    libraries = ['exiv2'],
                    include_dirs = ['src'],
                    sources = ['src/exif_py.cc',
                               'src/metadata.cc'])

setup (name = 'ExifPy',
       version = '1.0',
       description = 'A very thin cross-platform wrapper around the exiv2 library',
       ext_modules = [exif_py])
